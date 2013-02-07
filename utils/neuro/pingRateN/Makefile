objects = 	pingRateN_tester.o \
			pingRateN.o \
			rateN.o \
			get_last_period.o \
			fileIO.o \
			l2peaks.o
name = pingRateN_tester
	
$(name): $(objects)
	gcc -o $(name) $(objects)
	
$(name).o: $(name).c pingRateN.h ../../fileIO/fileIO.h ../get_last_period/get_last_period.h
	gcc -c $(name).c
	
pingRateN.o: pingRateN.c ../rateN/rateN.h ../../basic_math/basic_math.h
	gcc -c pingRateN.c

rateN.o: ../rateN/rateN.c
	gcc -c ../rateN/rateN.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc -c ../../fileIO/fileIO.c

get_last_period.o: ../get_last_period/get_last_period.c
	gcc -c ../get_last_period/get_last_period.c
	
l2peaks.o: ../../sig_proc/l2peaks.c
	gcc -c ../../sig_proc/l2peaks.c

clean :
	rm $(name) $(objects) *.dat
