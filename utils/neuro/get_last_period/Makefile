objects =	get_last_period_tester.o \
			get_last_period.o \
			rateN.o \
			fileIO.o \
			l2peaks.o
			
name = get_last_period_tester
	
$(name): $(objects)
	gcc -o $(name) $(objects)
	
$(name).o: $(name).c get_last_period.h ../rateN/rateN.h ../../fileIO/fileIO.h
	gcc -c $(name).c
	
get_last_period.o: get_last_period.c ../rateN/rateN.h ../../sig_proc/l2peaks.h
	gcc -c get_last_period.c
	
l2peaks.o: ../../sig_proc/l2peaks.c
	gcc -c ../../sig_proc/l2peaks.c
	
rateN.o: ../rateN/rateN.c
	gcc -c ../rateN/rateN.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc -c ../../fileIO/fileIO.c

clean :
	rm $(name) $(objects) *.dat
