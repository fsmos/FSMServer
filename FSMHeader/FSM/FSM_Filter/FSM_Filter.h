#ifndef _FSM_FILTER_H
#define _FSM_FILTER_H

struct FSM_Range
{
    unsigned short StartAddress;
    unsigned short StopAddress;
};

struct FSM_Filter_str
{
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
};
unsigned int FSM_Filter(struct FSM_DeviceRegistr dt) ;
#endif