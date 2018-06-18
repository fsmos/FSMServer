#ifndef __LIBMYPY_H__
#define __LIBMYPY_H__

#include <Python.h>

PyObject * mn111_start_autoscan(PyObject * self);
PyObject * mn111_get_voltage(PyObject * self);

#endif
