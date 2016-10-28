#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_ProgBuf fsmprg;

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

struct split_t
{
    char str[100][100];
};

struct split_t split(char* Data,char simbol)
{
    struct split_t spt;
    unsigned short n,m;
    n=0;
    m=0;
    for(int i=0;i<strlen(Data);i++)
    {
        if(Data[i]==simbol)
        {
            spt.str[n][m]=0;
            n++;
            m=0;
        }
        else
        {
            spt.str[n][m]=Data[i];
            m++;
        }
    }
    return spt;
}
int main(int argc, char **argv)
{
    struct split_t spt2;
    char Data[1000];
    int i;
    FILE * fo; 
    i=0;
    fo = fopen(argv[1],"rt"); 
    if(fo==0) return 0;
    while( fgets(Data, 100, fo) != NULL )
    {
        spt2=split(Data,' ');
        if(strcmp(spt2.str[0],"ss")==0) 
        {
            fsmprg.prg[i].DeviceSignal=atoi(spt2.str[1]);
            fsmprg.prg[i].IDSignal=atoi(spt2.str[2]);
            fsmprg.prg[i].DeviceSlot=atoi(spt2.str[3]);
            fsmprg.prg[i].IDSlot=atoi(spt2.str[4]);
            printf("Device %u Signal %u -> Device %u Slot %u\n",fsmprg.prg[i].DeviceSignal,fsmprg.prg[i].IDSignal,fsmprg.prg[i].DeviceSlot,fsmprg.prg[i].IDSlot);
            i++;
        }
        
    }
    fsmprg.PrgSize=i;
    fsmprg.CRC=FSM_crc32NT(0,(unsigned char*)(&fsmprg.prg),fsmprg.PrgSize*8);
    printf("Programm count %u/%u CRC: 0x%08x \n",fsmprg.PrgSize,FSM_ProgrammSSSize,fsmprg.CRC);
    fclose(fo);
    fo = fopen(argv[2],"wb"); 
    fwrite(&fsmprg,sizeof(struct FSM_ProgBuf),1,fo);
    fclose(fo);
	return 0;
}
