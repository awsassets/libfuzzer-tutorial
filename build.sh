#!/bin/sh
set -e
cd $(dirname $0)

if [ ! libpython3.9.a ]; then
	cd cpython
	./configure CC="clang -fsanitize-coverage=trace-pc-guard -fsanitize=address"
	make
	cp ./libpython3.9.a ..
	cd ..
fi
clang++ -o fuzzer -fsanitize=address,fuzzer -I./cpython -I./cpython/Include harness.c -lutil libpython3.9.a
