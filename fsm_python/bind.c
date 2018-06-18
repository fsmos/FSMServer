#include "libfsmgetccklist.h"

char fsmgetccklistfunc_docs[] = "FSM Get CCK List.";

PyMethodDef fsmgetccklist_funcs[] = {
	{	"fsmgetccklist",
		(PyCFunction)getccklist,
		METH_NOARGS,
		fsmgetccklistfunc_docs},
	{	NULL}
};

char fsmgetccklist_docs[] = "This is FSM Get CCK List device module.";

PyModuleDef fsmgetccklist_mod = {
	PyModuleDef_HEAD_INIT,
	"fsmgetccklist",
	fsmgetccklist_docs,
	-1,
	fsmgetccklist_funcs,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_fsmgetccklist(void) {
	return PyModule_Create(&fsmgetccklist_mod);
}
