#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/tty.h>
#include <linux/tty_driver.h>
#include <linux/tty_flip.h>
#include <linux/serial.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>

struct fsmad_port {
	struct tty_port port;
	struct mutex port_write_mutex;
};

static struct fsmad_port fsmadc_port;
static int fsmad_curr;

#define fsmad_STR_SIZE 508 /* should be bigger then max expected line length */
#define fsmad_MAX_ROOM 4096 /* we could assume 4K for instance */

#define fsmad_TTY_MAJOR		240	/* experimental range */
#define fsmad_TTY_MINORS	4	/* only have 4 devices */

static int fsmad_curr;

static char fsmad_buffer[fsmad_STR_SIZE + 4];

void fsmad_flush(void)
{
	if (fsmad_curr > 0) {
		fsmad_buffer[fsmad_curr] = '\0';
		pr_info("[U] %s\n", fsmad_buffer);
		fsmad_curr = 0;
	}
}
void fsmad_prints(const unsigned char *string)
{
    
    if (!tty_buffer_request_room(&fsmadc_port.port, 1))
        tty_flip_buffer_push(&fsmadc_port.port);
    tty_insert_flip_string(&fsmadc_port.port,string,strlen(string));
    tty_flip_buffer_push(&fsmadc_port.port);
}
EXPORT_SYMBOL(fsmad_prints);

int fsmad_printk(const unsigned char *buf, int count)
{
	int i = fsmad_curr;

	if (buf == NULL) {
		fsmad_flush();
		return i;
	}

	for (i = 0; i < count; i++) {
		if (fsmad_curr >= fsmad_STR_SIZE) {
			/* end of tmp buffer reached: cut the message in two */
			fsmad_buffer[fsmad_curr++] = '\\';
			fsmad_flush();
		}

		switch (buf[i]) {
		case '\r':
			fsmad_flush();
			if ((i + 1) < count && buf[i + 1] == '\n')
				i++;
			break;
		case '\n':
			fsmad_flush();
			break;
		default:
			fsmad_buffer[fsmad_curr++] = buf[i];
			break;
		}
	}

	return count;
}
EXPORT_SYMBOL(fsmad_printk);

static int fsmad_open(struct tty_struct *tty, struct file *filp)
{
	tty->driver_data = &fsmadc_port;

	return tty_port_open(&fsmadc_port.port, tty, filp);
}

static void fsmad_close(struct tty_struct *tty, struct file *filp)
{
	struct fsmad_port *tpkp = tty->driver_data;

	mutex_lock(&tpkp->port_write_mutex);
	/* flush tpk_printk buffer */
	fsmad_printk(NULL, 0);
	mutex_unlock(&tpkp->port_write_mutex);

	tty_port_close(&tpkp->port, tty, filp);
}

static int fsmad_write(struct tty_struct *tty,const unsigned char *buf, int count)
{
	struct fsmad_port *tpkp = tty->driver_data;
	int ret;


	/* exclusive use of tpk_printk within this tty */
	mutex_lock(&tpkp->port_write_mutex);
	ret = fsmad_printk(buf, count);
	mutex_unlock(&tpkp->port_write_mutex);

	return ret;
}

static int fsmad_write_room(struct tty_struct *tty)
{
	return fsmad_MAX_ROOM;
}

static int fsmad_ioctl(struct tty_struct *tty,
			unsigned int cmd, unsigned long arg)
{
	struct fsmad_port *tpkp = tty->driver_data;

	if (!tpkp)
		return -EINVAL;

	switch (cmd) {
	/* Stop TIOCCONS */
	case TIOCCONS:
		return -EOPNOTSUPP;
	default:
		return -ENOIOCTLCMD;
	}
	return 0;
}

static const struct tty_operations fsmad_ops = {
	.open = fsmad_open,
	.close = fsmad_close,
	.write = fsmad_write,
	.write_room = fsmad_write_room,
	.ioctl = fsmad_ioctl,
};

static const struct tty_port_operations null_ops = { };

static struct tty_driver *fsmad_driver;

static int __init FSMAD_console_init(void)
{
    int ret = -ENOMEM;
	mutex_init(&fsmadc_port.port_write_mutex);

	fsmad_driver = tty_alloc_driver(1,
			TTY_DRIVER_RESET_TERMIOS |
			TTY_DRIVER_REAL_RAW |
			TTY_DRIVER_UNNUMBERED_NODE);
	if (IS_ERR(fsmad_driver))
		return PTR_ERR(fsmad_driver);

	tty_port_init(&fsmadc_port.port);
	fsmadc_port.port.ops = &null_ops;

	fsmad_driver->driver_name = "ttyFSMAD";
	fsmad_driver->name = "ttyFSMAD";
	fsmad_driver->major = fsmad_TTY_MAJOR;
	fsmad_driver->minor_start = 0;
	fsmad_driver->type = TTY_DRIVER_TYPE_CONSOLE;
	fsmad_driver->init_termios = tty_std_termios;
	fsmad_driver->init_termios.c_oflag = OPOST | OCRNL | ONOCR | ONLRET;
	tty_set_operations(fsmad_driver, &fsmad_ops);
	tty_port_link_device(&fsmadc_port.port, fsmad_driver, 0);

	ret = tty_register_driver(fsmad_driver);
	if (ret < 0) {
		printk(KERN_ERR "Couldn't register ttyprintk driver\n");
		goto error;
	}

	return 0;

error:
	put_tty_driver(fsmad_driver);
	tty_port_destroy(&fsmadc_port.port);
return ret;
}

static void __exit FSMAD_console_exit(void)
{
   tty_unregister_driver(fsmad_driver);
   put_tty_driver(fsmad_driver);
   tty_port_destroy(&fsmadc_port.port);
}


module_init(FSMAD_console_init);
module_exit(FSMAD_console_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM AD Module");
MODULE_LICENSE("GPL");