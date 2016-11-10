#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_ProgBuf fsmprg;
struct FSM_Filter_str FSM_ft;

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
    char Name[100];
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
/*
    char FSM_ID_Filter;
    struct FSM_Range FSM_ID;
    char FSM_Type_Filter;
    struct FSM_Range FSM_Type;
    char FSM_Vid_Filter;
    struct FSM_Range FSM_Vid;
    char FSM_PodVid_Filter;
    struct FSM_Range FSM_PodVid;
    char FSM_Kod_Filter;
    struct FSM_Range FSM_Kod;
*/
        if(strcmp(spt2.str[0],"fid")==0) 
        {
            FSM_ft.FSM_ID_Filter=1;
            FSM_ft.FSM_ID.StartAddress=atoi(spt2.str[1]);
            FSM_ft.FSM_ID.StopAddress=atoi(spt2.str[2]);
            printf("FSM_ID_Filter from %u to %u\n",FSM_ft.FSM_ID.StartAddress,FSM_ft.FSM_ID.StopAddress);
        }
        if(strcmp(spt2.str[0],"fk")==0) 
        {
            FSM_ft.FSM_Kod_Filter=1;
            FSM_ft.FSM_Kod.StartAddress=atoi(spt2.str[1]);
            FSM_ft.FSM_Kod.StopAddress=atoi(spt2.str[2]);
            printf("FSM_Kod_Filter from %u to %u\n",FSM_ft.FSM_Kod.StartAddress,FSM_ft.FSM_Kod.StopAddress);
        }
        if(strcmp(spt2.str[0],"fpv")==0) 
        {
            FSM_ft.FSM_PodVid_Filter=1;
            FSM_ft.FSM_PodVid.StartAddress=atoi(spt2.str[1]);
            FSM_ft.FSM_PodVid.StopAddress=atoi(spt2.str[2]);
            printf("FSM_PodVid_Filter from %u to %u\n",FSM_ft.FSM_PodVid.StartAddress,FSM_ft.FSM_PodVid.StopAddress);
        }
        if(strcmp(spt2.str[0],"fv")==0) 
        {
            FSM_ft.FSM_Vid_Filter=1;
            FSM_ft.FSM_Vid.StartAddress=atoi(spt2.str[1]);
            FSM_ft.FSM_Vid.StopAddress=atoi(spt2.str[2]);
            printf("FSM_Vid_Filter from %u to %u\n",FSM_ft.FSM_Vid.StartAddress,FSM_ft.FSM_Vid.StopAddress);
        }
        if(strcmp(spt2.str[0],"ft")==0) 
        {
            FSM_ft.FSM_Type_Filter=1;
            FSM_ft.FSM_Type.StartAddress=atoi(spt2.str[1]);
            FSM_ft.FSM_Type.StopAddress=atoi(spt2.str[2]);
            printf("FSM_Type_Filter from %u to %u\n",FSM_ft.FSM_Type.StartAddress,FSM_ft.FSM_Type.StopAddress);
        }
        
    }
    fsmprg.PrgSize=i;
    fsmprg.CRC=FSM_crc32NT(0,(unsigned char*)(&fsmprg.prg),fsmprg.PrgSize*8);
    printf("Programm count %u/%u CRC: 0x%08x \n",fsmprg.PrgSize,FSM_ProgrammSSSize,fsmprg.CRC);
    fclose(fo);
    strcpy(Name,argv[2]);
    strcat(Name,"index.fsmprg");
    fo = fopen(Name,"wb"); 
    fwrite(&fsmprg,sizeof(struct FSM_ProgBuf),1,fo);
    fclose(fo);
    strcpy(Name,argv[2]);
    strcat(Name,"filter.fsmprg");
    fo = fopen(Name,"wb"); 
    fwrite(&FSM_ft,sizeof(struct FSM_Filter_str),1,fo);
    fclose(fo);
	return 0;
}
