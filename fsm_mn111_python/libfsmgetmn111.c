#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Python.h>
#include "libfsmgetmn111.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"
char Packet[1000];
const char* fsm_dev_types[]=
{
    "n",
    "MN921",
    "MN825",
    "PO07",
    "PO08",
    "PO06",
    "MN524",
    "MN111",
    "MN401"
};
const char* fsm_firmware_state[]=
{
    "Ok",
    "Error",
    "Error",
};
PyObject * mn111_get_voltage(PyObject * self)
{
   unsigned short id = 44;
   sprintf(Packet , "{\"5V\":\"%f\",\"-5V\":\"%f\",\"-60\":\"%f\",\"90\":\"%f\",\"220\":\"%f\"}",FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_5V,id),FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n5V,id),FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_n60V,id),FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_90V,id),FSM_CCK_MN111_Read_Voltage(FSM_Read_MN111_Power_220V,id));  
   return PyUnicode_FromFormat(Packet);
}

PyObject * mn111_start_autoscan(PyObject * self)
{
    unsigned short id = 44;
   FSM_CCK_MN111_Reqest_Voltage(FSM_Read_MN111_AutoReqest,id);
   return PyUnicode_FromFormat("1");
}
