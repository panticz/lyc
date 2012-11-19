all:
	gcc $(FLAGS) $(INCLUDEDIR) lyc.c -o lyc

mips:
	gcc $(FLAGS) $(INCLUDEDIR) embedded TARGET=ar9132 lyc.c -o lyc

clean:
	rm -f *~ *.o *.cgi

