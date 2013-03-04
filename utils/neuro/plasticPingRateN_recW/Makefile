CFLAGS = -g -c
OFLAGS = -g -o

objects = 	plasticPingRateN_recW_tester.o \
		plasticPingRateN_recW.o \
		plasticRateN_recW.o \
		get_last_period.o \
                rateN.o \
		fileIO.o \
		l2peaks.o

name = plasticPingRateN_recW_tester
	
$(name): $(objects)
	gcc $(OFLAGS) $(name) $(objects) -lm
	
$(name).o: $(name).c plasticPingRateN_recW.h ../../fileIO/fileIO.h ../get_last_period/get_last_period.h
	gcc $(CFLAGS) $(name).c
	
plasticPingRateN_recW.o: plasticPingRateN_recW.c ../rateN/rateN.h ../../basic_math/basic_math.h
	gcc $(CFLAGS) plasticPingRateN_recW.c

plasticRateN_recW.o: ../plasticRateN_recW/plasticRateN_recW.c
	gcc $(CFLAGS) ../plasticRateN_recW/plasticRateN_recW.c
	
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
