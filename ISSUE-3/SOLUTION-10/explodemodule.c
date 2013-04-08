#include <Python.h>

static PyObject *explode_explode(PyObject *self, PyObject *args)
{
	int start, end, length;
	const char *line;
	
	PyObject *list = PyList_New(0);  

	if (!PyArg_ParseTuple(args, "s", &line))
	  return NULL;
	  
	length = strlen(line);
	
	char *token = malloc(length+1);

	for (start = 0; start < length+1; start++)
	{
		for (end = start+1; end < length+1; end++)
		{
		    memcpy(token, line+start, end-start);		    		   
	            token[end-start] = '\0';
           
		    PyObject *tokenObject = Py_BuildValue("s", token);
		    PyList_Append(list, tokenObject);
		    Py_DECREF(tokenObject);
	        }
	}
            		
	free(token);
	return list;
}

static PyMethodDef ExplodeMethods[] = {
	{"explode", explode_explode, METH_VARARGS, "Explode string to all possible substrings."},
	{NULL, NULL, 0, NULL}
};

void initexplode(void){
	(void) Py_InitModule("explode", ExplodeMethods);
}
