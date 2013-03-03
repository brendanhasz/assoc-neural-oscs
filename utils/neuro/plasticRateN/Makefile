CFLAGS = -g -c
OFLAGS = -g -o

objects =   plasticRateN_recW_tester.o \
	    plasticRateN_recW.o \
	    fileIO.o

name = plasticRateN_recW_tester
	
$(name): $(objects)
	gcc $(OFLAGS) $(name) $(objects)
	
plasticRateN_recW_tester.o: plasticRateN_recW_tester.c plasticRateN_recW.h ../../fileIO/fileIO.h
	gcc $(CFLAGS) $(name).c
	
plasticRateN_recW.o: plasticRateN_recW.c
	gcc $(CFLAGS) plasticRateN_recW.c

fileIO.o: ../../fileIO/fileIO.c
	gcc $(CFLAGS) ../../fileIO/fileIO.c

cleanest :
	rm $(name) $(objects) *.dat

clean:
	rm $(name) $(objects)
