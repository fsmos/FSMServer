#include "libfsmgetmn111.h"

char fsmgetmn111_docs[] = "FSM Get MN111.";

PyMethodDef fsmgetmn111_funcs[] = {
	{	"fsm_mn111_start_autoscan",
		(PyCFunction)mn111_start_autoscan,
		METH_NOARGS,
		fsmgetmn111_docs
       },
        {	"fsm_mn111_get_voltage",
		(PyCFunction)mn111_get_voltage,
		METH_NOARGS,
		fsmgetmn111_docs
        },
	{	NULL}
};

char fsmgetccklist_docs[] = "This is FSM Get MN111 device module.";

PyModuleDef fsmgetmn111_mod = {
	PyModuleDef_HEAD_INIT,
	"fsmgetmn111",
	fsmgetmn111_docs,
	-1,
	fsmgetmn111_funcs,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_fsmgetmn111(void) {
	return PyModule_Create(&fsmgetmn111_mod);
}
