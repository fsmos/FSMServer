#ifndef FSM_crypt
#define FSM_crypt

typedef void (*FunctionEncDec)(char*, char*,short);

struct FSM_cryptalg
{
    char reg;
    FunctionEncDec Encode;
    FunctionEncDec Decode;
};


int FSMCrypt_Register(FunctionEncDec Encode,FunctionEncDec Decode,char id);
int FSMCrypt_UnRegister(FunctionEncDec Encode,FunctionEncDec Decode,char id);
void FSMEncrypt(char id,char* dst,char * src,short len);
void FSMDecrypt(char id,char* dst,char * src,short len);

enum FSMEncAlgList
{
    GNM=1,
    
};
#endif