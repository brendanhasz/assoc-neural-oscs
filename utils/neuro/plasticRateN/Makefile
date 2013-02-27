objects =   plasticRateN_recW_tester.o \
	    plasticRateN_recW.o \
	    fileIO.o

name = plasticRateN_recW_tester
	
$(name): $(objects)
	gcc -g -o $(name) $(objects)
	
plasticRateN_recW_tester.o: plasticRateN_recW_tester.c plasticRateN_recW.h ../../fileIO/fileIO.h
	gcc -g -c $(name).c
	
plasticRateN_recW.o: plasticRateN_recW.c
	gcc -g -c plasticRateN_recW.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc -g -c ../../fileIO/fileIO.c

cleanest :
	rm $(name) $(objects) *.dat

clean:
	rm $(name) $(objects)
