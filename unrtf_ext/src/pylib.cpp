#include <python3.5/Python.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

#include "lib.h"

namespace {
const size_t MAX_INPUT_LENGTH = 1024 * 1024 * 256;
}

static PyObject * unrtf_(PyObject * self, PyObject * args) {
    char * input;
    int nopict_mode;
    if (!PyArg_ParseTuple(args, "si", &input, &nopict_mode)) {
        return NULL;
    }

    FILE * mfd_in = fmemopen(input, strnlen(input, MAX_INPUT_LENGTH), "r");
    int return_value = unrtf(mfd_in, !!nopict_mode);
    fflush(stdout);
    fclose(mfd_in);

    return Py_BuildValue("i", return_value);
}

static PyMethodDef unrtf_methods[] = {
    { "unrtf", (PyCFunction)unrtf_, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef unrtf_module = {
   PyModuleDef_HEAD_INIT,
   "_unrtf",
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   unrtf_methods
};


PyMODINIT_FUNC PyInit__unrtf()
{
    return PyModule_Create(&unrtf_module);
}
