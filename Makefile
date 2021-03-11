CC=gcc
WINCC=x86_64-w64-mingw32-gcc
CFlAGS=-I.
CFILE = argsparcer.c easydice.c filter.c roller.c

make:
	$(CC) -o roll $(CFILE) $(CFlAGS)

windows:
	$(WINCC) -o roll.exe $(CFILE) $(CFlAGS)

clean:
	rm -f *.o *~ core