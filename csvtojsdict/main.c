#include <stdio.h>
#include <string.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
void str_delete(char* text,char* out,char one)
{
    int j=0;
    for(int i=0;i<strlen(text);i++)
    {
        if(text[i]!=one) 
        {
            out[j]=text[i];
            j++;
        }
        
    }
}
void str_replace(char* text,char zn,char one)
{
    for(int i=0;i<strlen(text);i++)
    {
        if(text[i]==zn) 
        {
            text[i]=one;
        }
        
    }
}
int main(int argc, char **argv)
{
    FILE *pf, *pr;
    char str[100];
    char filed[100];
    char nums[100];
    strcpy(filed,argv[1]);
    strcat(filed,".js");
    pf=fopen(filed,"w");
    pr=fopen(argv[1],"r");
    fprintf(pf,"var mass =[");
    while(fgets(str,100,pr))
    {
    char** strspl= str_split(str,';');
    memset(nums,0,sizeof(nums));
    str_delete(strspl[1],nums,'\"');
    str_replace(nums,',','.');
    if(nums[0]!='0') fprintf(pf,"\n{name:%s,value:%s},",strspl[0],nums);
    }
    fprintf(pf,"\n{name:\"0\",value:0} ]");
    fclose(pf);
    fclose(pr);
	return 0;
}
