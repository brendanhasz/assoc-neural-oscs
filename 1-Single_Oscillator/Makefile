objects = single_PING_group.o rateN.o fileIO.o
name = single_PING_group
	
$(name): $(objects)
	gcc -o $(name) $(objects)
	
$(name).o: $(name).c ../utils/neuro/rateN/rateN.h ../utils/fileIO/fileIO.h
	gcc -c $(name).c
	
rateN.o: ../utils/neuro/rateN/rateN.c
	gcc -c ../utils/neuro/rateN/rateN.c
	
fileIO.o: ../utils/fileIO/fileIO.c
	gcc -c ../utils/fileIO/fileIO.c

clean :
	rm $(name) $(objects) *.dat
