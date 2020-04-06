#include "Python.h"
#include "longintrepr.h"
#include "code.h"
#include "marshal.h"
	
char *read_file(const char *filename, size_t *filesize) {
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	*filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = (char *)calloc(1, *filesize);
	fread(buf, 1, *filesize, fp);
	return buf;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		return -1;
	}
 
	if (!Py_IsInitialized()) {
        Py_InitializeEx(0);
    }

	char *data;
	size_t dataSize;
	data = read_file(argv[1], &dataSize);
	PyObject *p = PyMarshal_ReadObjectFromString(data, dataSize);
	printf("object: %p\n", p);
	return 0;
}