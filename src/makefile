test: test.o
	cc -o test test.o

test.o:	test.c
	cc -g -c test.c

array.o: array.c
	cc -c array.c

libarray.a: array.o
	ar rs libarray.a array.o

clean:
	rm test *.o
