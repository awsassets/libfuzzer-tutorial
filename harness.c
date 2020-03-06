extern "C" {
	#include "Python.h"
	#include "longintrepr.h"
	#include "code.h"
	#include "marshal.h"
	int LLVMFuzzerTestOneInput(char *Data, size_t dataSize) {
		PyMarshal_ReadObjectFromString(Data, dataSize);
		return 0;
	}
}