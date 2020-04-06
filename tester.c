#include "Python.h"
#include "longintrepr.h"
#include "code.h"
#include "marshal.h"
	
	void* my_malloc(void *ctx, size_t size) {
		return malloc(size);
	}

	void* my_calloc(void *ctx, size_t nelem, size_t elsize) {
		return calloc(nelem, elsize);
	}

	void* my_realloc(void *ctx, void *ptr, size_t new_size) {
		return realloc(ptr, new_size);
	}

	void my_free(void *ctx, void *ptr) {
		free(ptr);
	}

	void* my_alloc_arena(void *ctx, size_t size) {
		return malloc(size);
	}

	void my_free_arena(void *ctx, void *ptr, size_t size) {
		free(ptr);
	}

void init_allocator() {
	PyMemAllocatorEx alloc;
	PyObjectArenaAllocator arena;

	alloc.ctx = NULL;
	alloc.malloc = my_malloc;
	alloc.calloc = my_calloc;
	alloc.realloc = my_realloc;
	alloc.free = my_free;

	PyMem_SetAllocator(PYMEM_DOMAIN_RAW, &alloc);
	PyMem_SetAllocator(PYMEM_DOMAIN_MEM, &alloc);
	PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, &alloc);

	arena.ctx = NULL;
	arena.alloc = my_alloc_arena;
	arena.free = my_free_arena;
	PyObject_SetArenaAllocator(&arena);
}

char *read_file(const char *filename, size_t *filesize) {
	FILE *fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	*filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if ((ssize_t)*filesize == -1) {
		return NULL;
	}
	char *buf = (char *)calloc(1, *filesize);
	if (!buf) {
		return NULL;
	}
	fread(buf, 1, *filesize, fp);
	return buf;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		return -1;
	}
	if (!Py_IsInitialized()) {
		Py_Initialize();
	}
	init_allocator();
	char *data;
	size_t dataSize;
	data = read_file(argv[1], &dataSize);
	if (!data) {
		return -1;
	}
	PyObject *p = PyMarshal_ReadObjectFromString(data, dataSize);
	printf("serialized object type: %s\n", Py_TYPE(p)->tp_name);
	return 0;
}
