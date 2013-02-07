objects = rateN_tester.o rateN.o fileIO.o
name = rateN_tester
	
$(name): $(objects)
	gcc -o $(name) $(objects)
	
$(name).o: $(name).c ../utils.h
	gcc -c $(name).c
	
rateN.o: ../neuro/rateN.c
	gcc -c ../neuro/rateN.c
	
fileIO.o: ../fileIO/fileIO.c
	gcc -c ../fileIO/fileIO.c

clean :
	rm $(name) $(objects) *.dat
