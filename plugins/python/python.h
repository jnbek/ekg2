/* $Id$ */

/*
 *  (C) Copyright 2004-2005 Leszek Krupi�ski <leafnode@pld-linux.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License Version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __PYTHON_H_
#define __PYTHON_H_

#include <Python.h>

#ifndef Py_RETURN_TRUE
#define Py_RETURN_TRUE Py_INCREF(Py_True); return Py_True;
#define Py_RETURN_FALSE Py_INCREF(Py_False); return Py_False;
#endif

#include <ekg/dynstuff.h>
#include <ekg/scripts.h>

extern scriptlang_t python_lang;

#define python_module(s) ((PyObject *) script_private_get(s)) /* obiekt modu�u */

#define PYTHON_HANDLE_HEADER(event, arg) \
{ \
	PyObject *__py_r; \
	PyObject *pArgs = arg;\
	python_handle_result = -1;\
	\
	__py_r = PyObject_Call(event, pArgs, NULL);\
	\
	if (__py_r && PyInt_Check(__py_r)) { \
		int tmp = PyInt_AsLong(__py_r); \
		\
		if (/* python_handle_result != 2 && here -1 leafnode, check it. */ tmp != 1) \
			python_handle_result = tmp; \
	} else if (!__py_r) {\
		char *buffer = python_geterror(scr);\
                print("script_error", buffer);\
		xfree(buffer);\
	}


#define PYTHON_HANDLE_RESULT(args...) \
		if (!PyArg_ParseTuple(__py_r, args)) \
			PyErr_Print(); \
		else

#define PYTHON_HANDLE_FOOTER(x) \
/*	if (__py_r && PyTuple_Check(__py_r)) ; */\
	Py_XDECREF(__py_r); \
	Py_DECREF(pArgs);\
	\
}

int python_run(const char *filename);
int python_exec(const char *command);
int python_run(const char *filename);
int python_autorun();
int python_initialize();
int python_finalize();
int python_plugin_init();
script_t *python_find_script(PyObject *module);

#endif

/*
 * Local Variables:
 * mode: c
 * c-file-style: "k&r"
 * c-basic-offset: 8
 * indent-tabs-mode: t
 * End:
 * vim: sts=8 sw=8
 */
