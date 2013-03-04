CFLAGS = -g -c
OFLAGS = -g -o

objects =   plasticRateN_tester.o \
	    plasticRateN.o \
	    fileIO.o

name = plasticRateN_tester
	
$(name): $(objects)
	gcc $(OFLAGS) $(name) $(objects)
	
plasticRateN_tester.o: plasticRateN_tester.c plasticRateN.h ../../fileIO/fileIO.h
	gcc $(CFLAGS) $(name).c
	
plasticRateN.o: plasticRateN.c
	gcc $(CFLAGS) plasticRateN.c

fileIO.o: ../../fileIO/fileIO.c
	gcc $(CFLAGS) ../../fileIO/fileIO.c

cleanest :
	rm $(name) $(objects) *.dat

clean:
	rm $(name) $(objects)
