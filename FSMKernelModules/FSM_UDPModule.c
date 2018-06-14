#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>

/* Структура для регистрации функции перехватчика входящих ip пакетов */
struct nf_hook_ops fsm_udp_bundle;
unsigned int FSM_Server_Listener(uint hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *)  )
{
    /* Указатель на структуру заголовка протокола ip в пакете */
    struct iphdr *ip;
    /* Указатель на структуру заголовка протокола tcp в пакете */
    struct udphdr *udp;

    /* Проверяем что это IP пакет */
    if (skb->protocol == htons(ETH_P_IP))
    {
	/* Сохраняем указатель на структуру заголовка IP */
	ip = (struct iphdr *)skb_network_header(skb);
	/* Проверяем что это IP версии 4 и внутри TCP пакет */
	if (ip->version == 4 && ip->protocol == IPPROTO_UDP)
	{
	    /* Задаем смещение в байтах для указателя на TCP заголовок */
	    /* ip->ihl - длина IP заголовка в 32-битных словах */
	    skb_set_transport_header(skb, ip->ihl * 4);
	    /* Сохраняем указатель на структуру заголовка TCP */
	    udp = (struct udphdr *)skb_transport_header(skb);
	    /* Если пакет идет на 443 порт (HTTPS) */
	    if (udp->dest == htons(1996))
	    {
            printk(KERN_INFO "Recived");
            return NF_DROP;
	    }
	}
    }
    /* Пропускаем дальше все пакеты */
    return NF_ACCEPT;
}


int FSM_UDP_Server_Init(void)
{
    printk(KERN_INFO "Start FSM UDP Server");

    /* Заполняем структуру для регистрации hook функции */
    /* Указываем имя функции, которая будет обрабатывать пакеты */
    fsm_udp_bundle.hook = FSM_Server_Listener;
    /* Устанавливаем указатель на модуль, создавший hook */
    fsm_udp_bundle.owner = THIS_MODULE;
    /* Указываем семейство протоколов */
    fsm_udp_bundle.pf = PF_INET;
    /* Указываем, в каком месте будет срабатывать функция */
    fsm_udp_bundle.hooknum = NF_INET_LOCAL_IN;
    /* Выставляем самый высокий приоритет для функции */
    fsm_udp_bundle.priority = NF_IP_PRI_FIRST;
    /* Регистрируем */
    nf_register_hook(&fsm_udp_bundle);
    return 0;
}

void FSM_UDP_Server_Exit(void)
{
    /* Удаляем из цепочки hook функцию */
    nf_unregister_hook(&fsm_udp_bundle);
    printk(KERN_INFO "Stop FSM UDP Server");
}

module_init(FSM_UDP_Server_Init);
module_exit(FSM_UDP_Server_Exit);
