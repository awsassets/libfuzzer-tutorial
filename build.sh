#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

set -e
cd $(dirname $0)
LIBPYTHON_PATH=cpython/libpython3.9.a
export ASAN_OPTIONS='detect_leaks=0'
if [ ! -f $LIBPYTHON_PATH ]; then
	pushd cpython
	./configure CC="clang -g -fsanitize-coverage=trace-pc-guard -fsanitize=address"
	make; make install
	popd
fi

clang++ -o fuzzer -g -fsanitize=address,fuzzer -I./cpython -I./cpython/Include -lutil harness.cc $LIBPYTHON_PATH
clang -o tester -g -fsanitize=address -I./cpython -I./cpython/Include -lutil tester.c $LIBPYTHON_PATH
