all:
	gcc $(FLAGS) $(INCLUDEDIR) lyc.c -o lyc

clean:
	rm -f *~ *.o *.cgi

