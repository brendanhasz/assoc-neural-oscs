CFLAGS = -g -c
OFLAGS = -g -o

objects = 	plasticPingRateN_tester.o \
		plasticPingRateN.o \
		plasticRateN.o \
		get_last_period.o \
                rateN.o \
		fileIO.o \
		l2peaks.o

name = plasticPingRateN_tester
	
$(name): $(objects)
	gcc $(OFLAGS) $(name) $(objects) -lm
	
$(name).o: $(name).c plasticPingRateN.h ../../fileIO/fileIO.h ../get_last_period/get_last_period.h
	gcc $(CFLAGS) $(name).c
	
plasticPingRateN.o: plasticPingRateN.c ../rateN/rateN.h ../../basic_math/basic_math.h
	gcc $(CFLAGS) plasticPingRateN.c

plasticRateN.o: ../plasticRateN/plasticRateN.c
	gcc $(CFLAGS) ../plasticRateN/plasticRateN.c
	
fileIO.o: ../../fileIO/fileIO.c
	gcc $(CFLAGS) ../../fileIO/fileIO.c

get_last_period.o: ../get_last_period/get_last_period.c
	gcc $(CFLAGS) ../get_last_period/get_last_period.c

rateN.o: ../rateN/rateN.c
	gcc $(CFLAGS) ../rateN/rateN.c
	
l2peaks.o: ../../sig_proc/l2peaks.c
	gcc $(CFLAGS) ../../sig_proc/l2peaks.c

clean :
	rm $(name) $(objects)

cleanest :
	rm $(name) $(objects) *.dat
