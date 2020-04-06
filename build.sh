#!/bin/sh
set -e
LIBPYTHON_PATH=cpython/libpython3.9.a
cd $(dirname $0)
export ASAN_OPTIONS='detect_leaks=0'
if [ ! -f $LIBPYTHON_PATH ]; then
	pushd cpython
	./configure CC="clang -fsanitize-coverage=trace-pc-guard -fsanitize=address"
	make
	make install
	popd
fi
clang++ -o fuzzer -fsanitize=address,fuzzer -I./cpython -I./cpython/Include -lutil harness.cc $LIBPYTHON_PATH
clang -o tester -fsanitize=address -I./cpython -I./cpython/Include -lutil tester.c $LIBPYTHON_PATH
