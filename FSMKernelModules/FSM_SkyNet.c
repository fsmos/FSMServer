/*!
\file
\brief Модуль взаимодествия с пультом ПО-06
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/
#include <linux/init.h>
#include <linux/module.h>


#include "FSM/FSMDevice/FSM_DeviceProcess.h"



struct FSM_DeviceFunctionTree dft;
struct FSM_SkyNetDevice FSMSkyNetDev[FSM_SkyNetDeviceTreeSize];
struct FSM_SendCmd sendcmd;



void FSM_SkyNetRecive(char* data,short len, struct FSM_DeviceTree* to_dt,struct FSM_DeviceTree* from_dt)
{
    int i;
   
    struct FSM_SendCmdTS* scmd=(struct FSM_SendCmdTS*)data;
        // char datas[2];
         
    switch(data[0])
      {
                        
        case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt,"ok");
        for(i=0;i<FSM_SkyNetDeviceTreeSize;i++)
          {
              if(FSMSkyNetDev[i].iddev==to_dt->IDDevice)
              {
                 return; 
              }
          }
          for(i=0;i<FSM_PO06DeviceTreeSize;i++)
          {
          if(FSMSkyNetDev[i].reg==0)
          {
             FSMSkyNetDev[i].reg=1;
             FSMSkyNetDev[i].ethdev=FSM_FindEthernetDevice(to_dt->IDDevice);
             FSMSkyNetDev[i].iddev=to_dt->IDDevice;
             to_dt->data=&FSMSkyNetDev[i];
            // fsmdt->config=&FSMSkyNetDev[i].po06set;
             printk( KERN_INFO "FSMSkyNET Device Added %u \n",to_dt->IDDevice); 
             break;
          }
           
          
          }
          break;
          case DelLisr:
          for(i=0;i<FSM_E1DeviceTreeSize;i++)
          {
          if((FSMSkyNetDev[i].reg==1)&&( FSMSkyNetDev[i].iddev==to_dt->IDDevice))
          {
             FSMSkyNetDev[i].reg=0;
             printk( KERN_INFO "FSMPO06 Device Deleted %u \n",to_dt->IDDevice); 
             break;
          }
          }
          break;
          case AnsPing:///< Пинг
          break;
          case SendCmdToServer: ///< Отправка команды серверу
          switch(scmd->cmd)
          {
              case AnsGetSettingSwitch:
              printk( KERN_INFO "FSM_Set Recv %i\n",scmd->IDDevice);
              //memcpy(&((struct fsm_po06_setting*)(FSM_FindDevice(scmd->IDDevice)->config))->fsm_p006_su_s,scmd->Data,FSM_FindDevice(scmd->IDDevice)->dt->config_len);
              break;
          }
           break;
          case SendTxtMassage: ///< Отправка текстового сообщения
           break;
          case Alern: ///<Тревога
          break;
          case Warning: ///<Предупреждение
          break;
          case Trouble: ///<Сбой
          break;
          case Beep: ///<Звук
          break;
          default:
          break;
      }                 
    
    
    printk( KERN_INFO "RPack %u \n" ,len); 
}
EXPORT_SYMBOL(FSM_SkyNetRecive);
void ApplaySettingSkyNet(struct FSM_DeviceTree* df)
{
    memset(&sendcmd,0,sizeof(sendcmd));
    printk( KERN_INFO "FSM_Set\n" ); 
    sendcmd.cmd=SetSettingSwitch;
    sendcmd.countparam=1;
    sendcmd.IDDevice=df->IDDevice;
    sendcmd.CRC=0;
    sendcmd.opcode=SendCmdToDevice;
    //memcpy(&sendcmd.Data,&(((struct FSM_PO06Device*)df->data)->po06set.fsm_p006_su_s),sizeof(struct fsm_po06_subscriber));
    //(FSM_FindDevice(FSM_EthernetID))->dt->Proc((char*)&sendcmd,sizeof(struct FSM_SendCmd)-sizeof(sendcmd.Data)+sizeof(struct fsm_po06_subscriber),df);
}

static int __init FSM_SkyNet_init(void)
{
   dft.aplayp=(ApplayProcess)ApplaySettingSkyNet;
   dft.type=(unsigned char)Switch;
   dft.VidDevice=(unsigned char)SkyNet;
   dft.PodVidDevice=(unsigned char)K1986BE1T;
   dft.KodDevice=(unsigned char)BLE_nRFC_RS485_Ethernet;
   dft.Proc=FSM_SkyNetRecive;
  // dft.config_len=sizeof(struct fsm_po06_setting);
   FSM_DeviceClassRegister(dft);
   printk( KERN_INFO "FSM SkyNet Module loaded\n" ); 
   return 0;  
}

static void __exit FSM_SkyNet_exit(void)
{
   printk( KERN_INFO "FSM SkyNet Module unloaded\n" );  
}

module_init(FSM_SkyNet_init);
module_exit(FSM_SkyNet_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM SkyNet Module");
MODULE_LICENSE("GPL");