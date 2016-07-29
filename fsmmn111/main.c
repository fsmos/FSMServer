#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include "FSM/FSMDevice/fcmprotocol.h"
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

int main(int argc, char **argv)
{
    if(argc>2)
    {
       unsigned short id=atoi(argv[1]);
       if(strcmp(argv[2], "reqest")==0)
       {
           if(strcmp(argv[3], "5v")==0) FSM_CCK_MN111_Reqest_Voltage(FSM_Get_MN111_Power_5V,id);
           if(strcmp(argv[3], "-5v")==0) FSM_CCK_MN111_Reqest_Voltage(FSM_Get_MN111_Power_n5V,id);
           if(strcmp(argv[3], "-60v")==0) FSM_CCK_MN111_Reqest_Voltage(FSM_Get_MN111_Power_n60V,id);
           if(strcmp(argv[3], "90v")==0) FSM_CCK_MN111_Reqest_Voltage(FSM_Get_MN111_Power_90V,id);
           if(strcmp(argv[3], "220v")==0) FSM_CCK_MN111_Reqest_Voltage(FSM_Get_MN111_Power_220V,id);
       }
       if(strcmp(argv[2], "read")==0)
       {
           if(argc==3)
           {
           printf("5 Voltage  %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_5V,id));
           printf("-5 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n5V,id));
           printf("-60 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n60V,id));
           printf("90 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_90V,id));
           printf("220 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_220V,id));
           return;
           }
           if(strcmp(argv[3], "5v")==0) printf("5 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_5V,id));
           if(strcmp(argv[3], "-5v")==0) printf("-5 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n5V,id));
           if(strcmp(argv[3], "-60v")==0) printf("-60 Voltage %f\n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n60V,id));
           if(strcmp(argv[3], "90v")==0) printf("90 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_90V,id));
           if(strcmp(argv[3], "220v")==0) printf("220 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_220V,id));
       }
       if(strcmp(argv[2], "auto")==0)
       {
           FSM_CCK_MN111_Reqest_Voltage(FSM_Read_MN111_AutoReqest,id);
           printf("AutoScan On \n");
       }
       if(strcmp(argv[2], "status")==0)
       {
           while(1)
           {
           printf("Scan\n");
           printf("5 Voltage  %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_5V,id));
           printf("-5 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n5V,id));
           printf("-60 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n60V,id));
           printf("90 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_90V,id));
           printf("220 Voltage %f \n",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_220V,id));
           sleep(1);
           }
       }
    }
	return 0;
}
