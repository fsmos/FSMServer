#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>  
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    int n;
    char buff[1024];
    int F_ID = -1;
    F_ID = open("/dev/ttyFSMAD", O_RDWR | O_NOCTTY);
    if(F_ID == -1)
    {
        return -1;
    }
    else
    { 
        struct termios options; /*структура для установки порта*/
         
         tcgetattr(F_ID, &options); /*читает пораметры порта*/
 
         cfsetispeed(&options, B57600); /*установка скорости порта*/
         cfsetospeed(&options, B57600); /*установка скорости порта*/
 
         options.c_cflag &= ~PARENB; /*выкл проверка четности*/
         options.c_cflag &= ~CSTOPB; /*выкл 2-х стобит, вкл 1 стопбит*/
         options.c_cflag &= ~CSIZE; /*выкл битовой маски*/
         options.c_cflag |= CS8; /*вкл 8бит*/
         tcsetattr(F_ID, TCSANOW, &options); /*сохронения параметров порта*/
         n = fcntl(F_ID, F_GETFL, 0);
         fcntl(F_ID, F_SETFL, n & ~O_NDELAY);

    }
    
    while(1)
    {
       n = read(F_ID,buff,1024); 
       if(n>0) 
       {
           printf("Read:%d",n);
           printf("%s",buff);
       }
    }
    
	close(F_ID);
	return 0;
}
