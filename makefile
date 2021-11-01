target:test

test: main.c header.c header.h
	gcc main.c header.c -lm -o test
	./test