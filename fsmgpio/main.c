#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

int main(int argc, char **argv)
{
    enum FSM_GPIO_Bit_Enum pinn;
	printf("Gpio Controller Started\n");
    if(argc>1)
    {
        if(strcmp(argv[1], "reset") == 0) 
        {
            FSM_GPIO_Ctl_Reset();
            printf("Gpio Reseted\n");
        }
       
        else if(strcmp(argv[1], "eror_imp") == 0) 
        {
            FSM_GPIO_Ctl_Eror();
             printf("Gpio Eror impulse\n");
        }
        else if(strcmp(argv[1], "eror_on") == 0) 
        {
            FSM_GPIO_Ctl_Error_ON();
            printf("Gpio Eror On\n");
        }
        else if(strcmp(argv[1], "eror_off") == 0) 
        {
            FSM_GPIO_Ctl_Error_OFF();
            printf("Gpio Eror Off\n");
        } 
        else if(strcmp(argv[1], "pin_on") == 0) 
        {
            
            if(argc<=2)
            {
                printf("Pleas Enter number of Pin\n");
                return 0;
            }
            printf("Gpio Pin On %u \n ",atoi(argv[2]));
            switch(atoi(argv[2]))
            {
                case 1:
                pinn=FSM_GPIO_Bit_0;
                break;
                case 2:
                pinn=FSM_GPIO_Bit_1;
                break;
                case 3:   
                pinn=FSM_GPIO_Bit_2;
                break;
                case 4:
                pinn=FSM_GPIO_Bit_3;
                break;
                case 5:
                pinn=FSM_GPIO_Bit_4;
                break;
                case 6:
                pinn=FSM_GPIO_Bit_5;
                break;
                case 7:
                pinn=FSM_GPIO_Bit_6;
                break;
                case 8:
                pinn=FSM_GPIO_Bit_7;
                break;
                default:
                printf("Eror Pin %u \n",atoi(argv[2]));
                return 0;
                break;
            }
            FSM_GPIO_Ctl_SetBit(pinn);
        }
        else if(strcmp(argv[1], "pin_off") == 0) 
        {
            if(argc<=2)
            {
                printf("Pleas Enter number of Pin\n");
                return 0;
            }
            printf("Gpio Pin Off %u \n",atoi(argv[2]));
            switch(atoi(argv[2]))
            {
                case 1:
                pinn=FSM_GPIO_Bit_0;
                break;
                case 2:
                pinn=FSM_GPIO_Bit_1;
                break;
                case 3:   
                pinn=FSM_GPIO_Bit_2;
                break;
                case 4:
                pinn=FSM_GPIO_Bit_3;
                break;
                case 5:
                pinn=FSM_GPIO_Bit_4;
                break;
                case 6:
                pinn=FSM_GPIO_Bit_5;
                break;
                case 7:
                pinn=FSM_GPIO_Bit_6;
                break;
                case 8:
                pinn=FSM_GPIO_Bit_7;
                break;
                default:
                printf("Eror Pin %u \n",atoi(argv[2]));
                return 0;
                break;
            }
            FSM_GPIO_Ctl_ReSetBit(pinn);
        }
        else 
        {
        printf("Invalid CMD\n"); 
        }
    }
    else
    {
        printf("Invalid Count Parametr\n"); 
    }
	return 0;
}
