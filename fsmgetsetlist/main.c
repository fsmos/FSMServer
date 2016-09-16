#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

int main(int argc, char **argv)
{
    unsigned short id=atoi(argv[1]);
       struct FSM_SetTreeGetListCount fsmdc;
       struct FSM_SetTreeGetList fsmd;
       struct FSM_SetTreeElementFS fsmte;
       struct FSM_SetTreeReadElement fsmrte;
        struct FSM_SetTreeWriteElement fsmwte;
	char Datas[100];
    int n;
    if(argc>2)
    {
       
       int i;
       if(strcmp(argv[2], "list")==0)
       {
        FSM_Get_Setting_List_Count(id,&fsmdc);
        printf("%u %u\n",fsmdc.count,fsmdc.IDDevice);
        fsmd.IDDevice=fsmdc.IDDevice;
        for(i=0;i<fsmdc.count;i++)
        {
            fsmd.iid=i;
            FSM_Get_Setting_List_Item(&fsmd,&fsmte);
            printf("%u.%s \n",i,fsmte.id);
        }
        
       }
       if(strcmp(argv[2], "readr")==0)
       {
       
                fsmrte.id=id;
                strcpy((char*)fsmrte.name,argv[3]);
                FSM_Get_Item_Rq(&fsmrte);
            //printf("%u.%s \n",i,fsmte.id);
      }
      if(strcmp(argv[2], "readd")==0)
      {
       
        n=FSM_Get_Item_Read(id,Datas);
        for(i=0;i<n;i++)
        {
            printf("%u.%u \n",i,Datas[i]);
        }
            
      }
      if(strcmp(argv[2], "write")==0)
      {
        fsmwte.id=id;
        fsmwte.len=0;
        strcpy((char*)fsmwte.name,argv[3]);
        for(i=4;i<argc;i++)
        {
            fsmwte.Data[fsmwte.len]=atoi(argv[i]);
            fsmwte.len++;
        }
        
        FSM_Set_Item(&fsmwte);
      }
        
    }
	return 0;
}
