/*!
\file
\brief Модуль взаимодествия с пультом ПО-06
\authors Гусенков.С.В
\version 0.0.1_rc1
\date 30.12.2015
*/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct CCKDeviceInfo FSMMN825_CCKDevE;
struct FSM_DeviceFunctionTree FSMMN825_dft;
struct FSM_MN825Device FSMMN825Dev[FSM_MN825DeviceTreeSize];
struct FSM_SendCmd FSMMN825_sendcmd;
struct FSM_AudioStream FSMMN825_fsmas;

void FSM_MN825SendStreaminfo(unsigned short id, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    short plen;

    memset(&FSMMN825_sendcmd, 0, sizeof(struct FSM_SendCmd));
    FSMMN825_sendcmd.opcode = SendCmdToDevice;
    FSMMN825_sendcmd.IDDevice = from_dt->IDDevice;
    FSMMN825_sendcmd.cmd = FSMPO06SendStream;
    FSMMN825_sendcmd.countparam = 1;
    ((unsigned short*)FSMMN825_sendcmd.Data)[0] = id;
    if(to_dt->debug)
        printk(KERN_INFO "FSM Send %u ,%u \n", FSMMN825_sendcmd.Data[0], FSMMN825_sendcmd.Data[1]);
    FSMMN825_sendcmd.CRC = 0;
    plen = sizeof(struct FSM_SendCmd) - sizeof(FSMMN825_sendcmd.Data) + 2;
    if(to_dt != 0)
        to_dt->dt->Proc((char*)&FSMMN825_sendcmd, plen, to_dt, from_dt);
}

void FSM_MN825Recive(char* data, short len, struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{
    int i;
      unsigned char fsm_mn825_crc32[4];
    unsigned char fsm_mn825_ramst[2];
    unsigned char fsm_mn825_build[4];
    struct FSM_DeviceTree* fsmdv;
    struct FSM_SendCmdTS* scmd = (struct FSM_SendCmdTS*)data;
// char datas[2];

    switch(data[0]) {

    case RegDevice: ///< Регистрация устройства
        FSM_Statstic_SetStatus(to_dt, "ok");
        to_dt->pingon = true;
        for(i = 0; i < FSM_MN825DeviceTreeSize; i++) {
            if(FSMMN825Dev[i].iddev == to_dt->IDDevice) {
                FSM_MN825SendStreaminfo(FSMMN825Dev[i].idstream, from_dt, to_dt);
                return;
            }
        }
        for(i = 0; i < FSM_MN825DeviceTreeSize; i++) {
            if(FSMMN825Dev[i].reg == 0) {
                FSMMN825Dev[i].reg = 1;
                FSMMN825Dev[i].ethdev = FSM_FindEthernetDevice(to_dt->IDDevice);
                FSMMN825_fsmas.iddev = to_dt->IDDevice;
                // fsmas.ToProcess=FSM_PO06RecivePacket;
                // fsmas.ToUser=FSM_E1SendPacket;
                FSMMN825_fsmas.TransportDevice = FSMMN825Dev[i].ethdev->numdev;
                FSMMN825_fsmas.TransportDeviceType = FSM_EthernetID2;
                FSMMN825_fsmas.Data = &FSMMN825Dev[i];
                FSMMN825Dev[i].idstream = FSM_AudioStreamRegistr(FSMMN825_fsmas);
                FSMMN825Dev[i].iddev = to_dt->IDDevice;
                FSMMN825Dev[i].rwbuf.free=92;
                FSMMN825Dev[i].rwbuf.rd_ptr=0;
                FSMMN825Dev[i].rwbuf.wr_ptr=0;
                FSMMN825Dev[i].r168kb100client=0;
                FSMMN825Dev[i].r168kb100client_cmd=0;
                to_dt->data = &FSMMN825Dev[i];
                to_dt->config = &FSMMN825Dev[i].mn825set;
                FSM_MN825SendStreaminfo(FSMMN825Dev[i].idstream, from_dt, to_dt);
                if(to_dt->debug)
                    printk(KERN_INFO "FSM MN825 Device Added %u \n", to_dt->IDDevice);
                ;

                // datas[0]=0xd0;
                // datas[1]=0xd1;
                // FSM_AudioStreamToUser(0,datas,2);
                break;
            }
        }
        break;
    case DelLisr:
        for(i = 0; i < FSM_MN825DeviceTreeSize; i++) {
            if((FSMMN825Dev[i].reg == 1) && (FSMMN825Dev[i].iddev == to_dt->IDDevice)) {
                FSMCCK_RemoveDeviceInfo(to_dt->IDDevice);
                FSM_AudioStreamUnRegistr(FSMMN825Dev[i].idstream);
                FSMMN825Dev[i].reg = 0;
                if(to_dt->debug)
                    printk(KERN_INFO "FSM MN825 Device Deleted %u \n", to_dt->IDDevice);
                break;
            }
        }
        break;
    case AnsPing: ///< Пинг
        break;
    case SendCmdToServer: ///< Отправка команды серверу
        switch(scmd->cmd) {
        case FSMMN825ConnectToDevE1:
            // ((struct FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idcon=FSM_P2P_Connect(((struct
            // FSM_PO06Device*)((FSM_FindDevice(scmd->IDDevice))->data))->idstream, ((struct
            // FSM_E1Device*)(FSM_FindDevice(((struct FSMPO06CommCons*)scmd->Data)->id)->data))->streams_id[((struct
            // FSMPO06CommCons*)scmd->Data)->channel]);
            break;
        case FSMMN825DisConnectToDevE1:
            FSM_P2P_Disconnect(((struct FSM_PO06Device*)(to_dt->data))->idcon);
            break;
        case AnsGetSettingClientMN825:
            if(to_dt->debug)
                printk(KERN_INFO "FSM_Set Recv %i\n", scmd->IDDevice);
            memcpy(&((struct fsm_po06_setting*)(to_dt->config))->fsm_p006_su_s, scmd->Data, to_dt->dt->config_len);
            break;
        case FSMMN825SendIP:
            memset(&FSMMN825_CCKDevE,0,sizeof(struct CCKDeviceInfo));
            FSMMN825_CCKDevE.id = scmd->IDDevice;
            FSMMN825_CCKDevE.ip[0] = scmd->Data[0];
            FSMMN825_CCKDevE.ip[1] = scmd->Data[1];
            FSMMN825_CCKDevE.ip[2] = scmd->Data[2];
            FSMMN825_CCKDevE.ip[3] = scmd->Data[3];
            FSMMN825_CCKDevE.type = MN825;
            FSMMN825_CCKDevE.Position = scmd->Data[4];
            fsm_mn825_crc32[0] = scmd->Data[5];
            fsm_mn825_crc32[1] = scmd->Data[6];
            fsm_mn825_crc32[2] = scmd->Data[7];
            fsm_mn825_crc32[3] = scmd->Data[8];
            FSMMN825_CCKDevE.crc32=((unsigned int*)fsm_mn825_crc32)[0];
            fsm_mn825_ramst[0] = scmd->Data[9];
            fsm_mn825_ramst[1] = scmd->Data[10];
            FSMMN825_CCKDevE.dstlen=((unsigned short*)fsm_mn825_ramst)[0];
            FSMMN825_CCKDevE.dstlen=scmd->Data[11];
            FSMMN825_CCKDevE.channel=scmd->Data[12];
            FSMMN825_CCKDevE.ver1=scmd->Data[13];
            FSMMN825_CCKDevE.ver2=scmd->Data[14];
            FSMMN825_CCKDevE.ver3=scmd->Data[15];
            FSMMN825_CCKDevE.crcerror=0;
            if(to_dt->data!=0) 
            {
                    FSMMN825_CCKDevE.audiostreamid= ((struct FSM_MN825Device*)to_dt->data)->idstream;
                    ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_type = scmd->Data[20];
                    ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_port[0] = scmd->Data[21];
                    ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_port[1] = scmd->Data[22];
                    
            }
            if(FSMMN825_CCKDevE.channel==0) 
            {
            if(to_dt->dt->crcfw==0) printk( KERN_ERR "Firmware CRC Not Check\n");
            else if(to_dt->dt->crcfw!=FSMMN825_CCKDevE.crc32)
            {     
                printk( KERN_ERR "Firmware CRC Error Please Enter \"fsmflash %u\" \n",to_dt->IDDevice ); 
                FSMMN825_CCKDevE.crcerror=1;
                //FSM_FlashStart(to_dt);
            }
            
            }
            else
            {
                if(to_dt->dt->crcfw==0) printk( KERN_ERR "Firmware CRC Not Check\n");
                else if(to_dt->dt->crcfw!=FSMMN825_CCKDevE.crc32)
                {     
                    FSMMN825_CCKDevE.crcerror=2;
                //FSM_FlashStart(to_dt);
                }
            }
            fsm_mn825_build[0] = scmd->Data[16];
            fsm_mn825_build[1] = scmd->Data[17];
            fsm_mn825_build[2] = scmd->Data[18];
            fsm_mn825_build[3] = scmd->Data[19];
            FSMMN825_CCKDevE.id_build=((unsigned int*)fsm_mn825_build)[0];
            FSMCCK_AddDeviceInfo(&FSMMN825_CCKDevE);
            if(to_dt->debug)
                printk(KERN_INFO "FSM ID%i Asterisk IP %i.%i.%i.%i\n ",
                       scmd->IDDevice,
                       scmd->Data[0],
                       scmd->Data[1],
                       scmd->Data[2],
                       scmd->Data[3]);
            break;
        case FSMMN825R168100KB_Packet:
            if(((struct FSM_MN825Device*)(to_dt->data))->r168kb100client != 0 )
            {
                scmd->IDDevice = ((struct FSM_MN825Device*)(to_dt->data))->r168kb100client->IDDevice;
                scmd->opcode = PacketToDevice; 
                scmd->cmd = ((struct FSM_MN825Device*)(to_dt->data))->r168kb100client_cmd;
                ((struct FSM_MN825Device*)(to_dt->data))->r168kb100client->dt->Proc(data,len,to_dt,((struct FSM_MN825Device*)(to_dt->data))->r168kb100client);
                printk(KERN_INFO "FSM NPP 0x%02x,0x%02x ",scmd->Data[0],scmd->Data[1] );
                return;
            } 
            scmd->IDDevice = to_dt->IDDevice;
            scmd->opcode = SendCmdToDevice;
            if(((struct FSM_MN825Device*)to_dt->data)->rwbuf.free>0) 
            {
            memcpy(((struct FSM_MN825Device*)to_dt->data)->rwbuf.bfel[((struct FSM_MN825Device*)to_dt->data)->rwbuf.wr_ptr].Dates,scmd->Data,  scmd->countparam);
            ((struct FSM_MN825Device*)to_dt->data)->rwbuf.bfel[((struct FSM_MN825Device*)to_dt->data)->rwbuf.wr_ptr].len = scmd->countparam;
            ((struct FSM_MN825Device*)to_dt->data)->rwbuf.free --;
            ((struct FSM_MN825Device*)to_dt->data)->rwbuf.wr_ptr++;
            if(((struct FSM_MN825Device*)to_dt->data)->rwbuf.wr_ptr>91) ((struct FSM_MN825Device*)to_dt->data)->rwbuf.wr_ptr=0;
            for(i=0; i<scmd->countparam/2;i++)
            {
                printk(KERN_INFO "FSM NRP 0x%02x,0x%02x ",scmd->Data[i*2],scmd->Data[i*2 
                +1] );
            }
            }
            else
            {
                
            printk(KERN_INFO "FSM Buffer Full");
            }
            
            break;
        }

        break;
    case SendTxtMassage: ///< Отправка текстового сообщения
        break;
    case Alern: ///<Тревога
        switch(((struct FSM_AlernSignal*)data)->ID) {
        }
        break;
    case Warning: ///<Предупреждение
        switch(((struct FSM_WarningSignal*)data)->ID) {
        case FSM_CCK_Server_Connect_Error:
            printk(KERN_WARNING "MN825 %u: Server Not Connect \n", ((struct FSM_Header*)(data))->IDDevice);
            break;
        }
        break;
    case Trouble: ///<Сбой
        switch(((struct FSM_TroubleSignal*)data)->ID) {
        case FSM_CCK_Memory_Test_Filed:
            printk(KERN_ERR "MN825 %u: Memory Error \n", ((struct FSM_Header*)(data))->IDDevice);
            break;
        }
        break;
    case Beep: ///<Звук
        break;
    case PacketFromUserSpace:
        switch(scmd->cmd) {
        case FSMMN825AudioRun:
        case FSMMN825Reset:
        case FSMMN825Reregister:
        case FSMMN825SetTangenta:
        case FSMMN825SendClearConfig:
            scmd->IDDevice = to_dt->IDDevice;
            scmd->opcode = SendCmdToDevice;
            to_dt->TrDev->dt->Proc((char*)scmd, FSMH_Header_Size_SendCmd, to_dt->TrDev, to_dt);
            break;
        case FSMMN825GetCRC:

            break;
        case FSMMN825R168100KB_Packet:
            scmd->IDDevice = to_dt->IDDevice;
            scmd->opcode = SendCmdToDevice;
            to_dt->TrDev->dt->Proc((char*)scmd, FSMH_Header_Size_SendCmd + scmd->countparam, to_dt->TrDev, to_dt);
            scmd->opcode = PacketToUserSpace;
            scmd->countparam =0;
            break;
            
        case FSMMN825R168100KB_PacketUDP:
            scmd->opcode = PacketToUserSpace;
            scmd->countparam = 0;
            while(((struct FSM_MN825Device*)to_dt->data)->rwbuf.free<92) 
            {
                scmd->opcode = PacketToUserSpace;
                memcpy(scmd->Data+scmd->countparam,((struct FSM_MN825Device*)to_dt->data)->rwbuf.bfel[((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr].Dates,((struct FSM_MN825Device*)to_dt->data)->rwbuf.bfel[((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr].len  );
                scmd->countparam += ((struct FSM_MN825Device*)to_dt->data)->rwbuf.bfel[((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr].len;
                ((struct FSM_MN825Device*)to_dt->data)->rwbuf.free ++;
                ((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr++;
                if(((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr>91) ((struct FSM_MN825Device*)to_dt->data)->rwbuf.rd_ptr=0;
                
            }
        break;
        }
    case PacketToDevice:
        switch(scmd->cmd) {
        case FSMMN825R168100KB_Packet:
            scmd->opcode = SendCmdToDevice;
            to_dt->TrDev->dt->Proc((char*)scmd, FSMH_Header_Size_SendCmd + scmd->countparam, to_dt->TrDev, to_dt);
            break;
        case FSMMN825R168_GetDats:
            fsmdv = FSM_FindDevice(((unsigned short*)scmd->Data)[0]);
            printk(KERN_INFO "MN825 Reuest Dats Start");
            if(fsmdv == 0) 
            {
                FSM_Start_Discovery(((unsigned short*)scmd->Data)[0]);
                return;
            }
            
            FSM_CCKGetInfoR168((unsigned short*)&FSMMN825_CCKDevE,to_dt->IDDevice);
            scmd->IDDevice = ((unsigned short*)(scmd->Data))[0];
            scmd->cmd = ((unsigned short*)(scmd->Data))[1];
            scmd->Data[0] = ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_type;
            scmd->Data[1] = FSMMN825_CCKDevE.ip[0];
            scmd->Data[2] = FSMMN825_CCKDevE.ip[1];
            scmd->Data[3] = FSMMN825_CCKDevE.ip[2];
            scmd->Data[4] = FSMMN825_CCKDevE.ip[3];
            scmd->Data[5] = ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_port[0];
            scmd->Data[6] = ((struct FSM_MN825Device*)to_dt->data)->r168kb100client_port[1];
            scmd->Data[7] = FSMMN825_CCKDevE.channel;
            scmd->countparam = 9;
            fsmdv->dt->Proc(data,FSMH_Header_Size_SendCmd + scmd->countparam,to_dt,fsmdv);
            printk(KERN_INFO "MN825 Reuest Dats");
            break;
            
        case FSMMN825R168_SetCP:
            fsmdv = FSM_FindDevice(((unsigned short*)scmd->Data)[0]);
            if(fsmdv == 0) 
            {
                FSM_Start_Discovery(((unsigned short*)scmd->Data)[0]);
                return;
            }
            ((struct FSM_MN825Device*)(to_dt->data))->r168kb100client = fsmdv;
            ((struct FSM_MN825Device*)(to_dt->data))->r168kb100client_cmd = ((unsigned short*)scmd->Data)[1];
            printk(KERN_INFO "MN825 Set CP");
            break;
        }
        break;
    default:
        break;
    }

    if(to_dt->debug)
        printk(KERN_INFO "RPack %u \n", len);
}
EXPORT_SYMBOL(FSM_MN825Recive);
void ApplaySettingMN825(struct FSM_DeviceTree* to_dt, struct FSM_DeviceTree* from_dt)
{

    memset(&FSMMN825_sendcmd, 0, sizeof(FSMMN825_sendcmd));
    if(to_dt->debug)
        printk(KERN_INFO "FSM_Set\n");
    FSMMN825_sendcmd.cmd = SetSettingClientMN825;
    FSMMN825_sendcmd.countparam = 1;
    FSMMN825_sendcmd.IDDevice = to_dt->IDDevice;
    FSMMN825_sendcmd.CRC = 0;
    FSMMN825_sendcmd.opcode = SendCmdToDevice;
    memcpy(&FSMMN825_sendcmd.Data,
           &(((struct FSM_MN825Device*)to_dt->data)->mn825set.fsm_mn825_su_s),
           sizeof(struct fsm_mn825_subscriber));
    from_dt->dt->Proc((char*)&FSMMN825_sendcmd,
                      sizeof(struct FSM_SendCmd) - sizeof(FSMMN825_sendcmd.Data) + sizeof(struct fsm_mn825_subscriber),
                      from_dt,
                      to_dt);
}

static int __init FSM_MN825_init(void)
{


    FSMMN825_dft.aplayp = ApplaySettingMN825;
    FSMMN825_dft.type = (unsigned char)AudioDevice;
    FSMMN825_dft.VidDevice = (unsigned char)CommunicationDevice;
    FSMMN825_dft.PodVidDevice = (unsigned char)CCK;
    FSMMN825_dft.KodDevice = (unsigned char)MN825;
    FSMMN825_dft.Proc = FSM_MN825Recive;
    FSMMN825_dft.config_len = sizeof(struct fsm_mn825_setting);
    FSM_FlashFirmwareCheck(&FSMMN825_dft);
    FSM_DeviceClassRegister(FSMMN825_dft);
    printk(KERN_INFO "FSM MN825 Module loaded\n");
    FSM_SendEventToAllDev(FSM_CCK_MN845_Started);

    return 0;
}

static void __exit FSM_MN825_exit(void)
{
    FSM_ClassDeRegister(FSMMN825_dft);
    
    printk(KERN_INFO "FSM MN825 Module unloaded\n");
}

module_init(FSM_MN825_init);
module_exit(FSM_MN825_exit);

MODULE_AUTHOR("Gusenkov S.V FSM");
MODULE_DESCRIPTION("FSM MN825 Module");
MODULE_LICENSE("GPL");