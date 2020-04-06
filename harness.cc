extern "C" {
	#include "Python.h"
	#include "longintrepr.h"
	#include "code.h"
	#include "marshal.h"
	int LLVMFuzzerTestOneInput(char *data, size_t dataSize) {
		if (!Py_IsInitialized()) {
        	Py_InitializeEx(0);
    	}
		PyMarshal_ReadObjectFromString(data, dataSize);
		return 0;
	}
}


