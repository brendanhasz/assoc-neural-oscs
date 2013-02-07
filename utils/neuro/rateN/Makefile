objects = 	rateN_tester.o \
			rateN.o \
			fileIO.o
name = rateN_tester
	
$(name): $(objects)
	gcc -o $(name) $(objects)
	
$(name).o: $(name).c rateN.h ../../fileIO/fileIO.h
	gcc -c $(name).c
	
rateN.o: rateN.c
	gcc -c rateN.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc -c ../../fileIO/fileIO.c

clean :
	rm $(name) $(objects) *.dat
