#include <stdio.h>
#include <string.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

unsigned int FSM_crc32NT(unsigned int crc, unsigned char *buf,unsigned int len) {
   unsigned int i,mask;

   crc = ~crc;
   while (len--) {
	  crc = crc ^ (*buf++); // process next byte
	  i=8;
	  while (i--) { // process 8 bits
		 mask = -(crc & 1);
		 crc = (crc >> 1) ^ (0xEDB88320 & mask);
	  }
   }
   return ~crc;
}

int main(int argc, char **argv)
{
     struct FSMFirmware firm;
     int size;
     int i,j,l;
     char Data[128*1024];
     l=0;
     memset(&firm,0,sizeof(struct FSMFirmware));
	 FILE* binfw,*fsmflash; 
     binfw= fopen(argv[1], "rb");
     fseek(binfw , 0 , SEEK_END); 
     size =ftell(binfw) ;
     rewind (binfw);
     printf("Size:%u\n",size);
     
     firm.svec.size=size;
     firm.evec.size=size;
    
     fread(Data, sizeof(char), size, binfw);  
     fclose(binfw);
     for(i=0;i<128;i++)
     {
         for(j=0;j<1024;j++)
         {
            if(l>=size) 
            {
                printf("Stop:%u\n",l);
                firm.svec.count=i;
                break;
            }
            firm.dvec[i].Data[j]=Data[l];
            l++;
         }
         firm.dvec[i].crc32=FSM_crc32NT(0,(unsigned char*)firm.dvec[i].Data,1024);
         firm.dvec[i].num=i;
     }
     firm.svec.crc32=FSM_crc32NT(0,(unsigned char*)Data,size);
     firm.evec.crc32=firm.svec.crc32;
     fsmflash = fopen(argv[2], "wb");
     fwrite(&firm,sizeof(struct FSMFirmware),1,fsmflash);
     fclose(fsmflash);
}
