objects = 	plasticPingRateN_tester.o \
		plasticPingRateN.o \
		plasticRateN.o \
		get_last_period.o \
		fileIO.o \
		l2peaks.o

name = plasticPingRateN_tester
	
$(name): $(objects)
	gcc -o $(name) $(objects) -lm
	
$(name).o: $(name).c plasticPingRateN.h ../../fileIO/fileIO.h ../get_last_period/get_last_period.h
	gcc -c $(name).c
	
plasticPingRateN.o: plasticPingRateN.c ../rateN/rateN.h ../../basic_math/basic_math.h
	gcc -c plasticPingRateN.c

plasticRateN.o: ../plasticRateN/plasticRateN.c
	gcc -c ../plasticRateN/plasticRateN.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc -c ../../fileIO/fileIO.c

get_last_period.o: ../get_last_period/get_last_period.c
	gcc -c ../get_last_period/get_last_period.c
	
l2peaks.o: ../../sig_proc/l2peaks.c
	gcc -c ../../sig_proc/l2peaks.c

clean :
	rm $(name) $(objects)

cleanest :
	rm $(name) $(objects) *.dat
