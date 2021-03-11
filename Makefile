CC=gcc
CFlAGS=-I.
CFILE = argsparcer.c easydice.c filter.c roller.c

make:
	$(CC) -o roll $(CFILE) $(CFlAGS)

clean:
	rm -f *.o *~ core