# Learned_Synchrony.c
#   ../../utils/multithreads/multithreads.c
#   Learned_Synchrony_worker.c
#       ../../utils/multithreads/multithreads.c
#       ../../utils/neuro/pingRateN/pingRateN.c
#           ../../utils/neuro/rateN/rateN.c
#       ../../utils/neuro/get_last_period/get_last_period.c
#           ../../utils/neuro/rateN/rateN.c
#           ../../utils/sig_proc/l2peaks.c
#       ../../utils/sig_proc/phdiff2.c
#           ../../utils/sig_proc/l2peaks.c
#   ../../utils/neuro/get_last_period/get_last_period.c
#   ../../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW.c
#       ../../utils/neuro/plasticRateN_recW/plasticRateN_recW.c
#   ../../utils/fileIO/fileIO.c

CFLAGS = -g -c
OFLAGS = -g

uts = ../../utils
nro = $(uts)/neuro

name = Learned_Synchrony

objects =	Learned_Synchrony.o \
                multithreads.o \
		Learned_Synchrony_worker.o \
		pingRateN.o \
		rateN.o \
		get_last_period.o \
		l2peaks.o \
		phdiff2.o \
                fileIO.o \
                plasticPingRateN_recW.o \
                plasticRateN_recW.o
		#.o
		#.o
		#.o

$(name): $(objects)
	gcc $(OFLAGS) -o $(name) $(objects) -lm -lpthread

Learned_Synchrony.o: Learned_Synchrony.c
	gcc $(CFLAGS) Learned_Synchrony.c
		
multithreads.o: $(uts)/multithreads/multithreads.c
	gcc $(CFLAGS) $(uts)/multithreads/multithreads.c
		
Learned_Synchrony_worker.o: Learned_Synchrony_worker.c
	gcc $(CFLAGS) Learned_Synchrony_worker.c
		
pingRateN.o: $(nro)/pingRateN/pingRateN.c
	gcc $(CFLAGS) $(nro)/pingRateN/pingRateN.c
		
pingRateN.o: $(nro)/pingRateN/pingRateN.c
	gcc $(CFLAGS) $(nro)/pingRateN/pingRateN.c
		
rateN.o: $(nro)/rateN/rateN.c
	gcc $(CFLAGS) $(nro)/rateN/rateN.c
		
get_last_period.o: $(nro)/get_last_period/get_last_period.c
	gcc $(CFLAGS) $(nro)/get_last_period/get_last_period.c
		
l2peaks.o: $(uts)/sig_proc/l2peaks.c
	gcc $(CFLAGS) $(uts)/sig_proc/l2peaks.c

phdiff2.o: $(uts)/sig_proc/phdiff2.c
	gcc $(CFLAGS) $(uts)/sig_proc/phdiff2.c

fileIO.o: $(uts)/fileIO/fileIO.c
	gcc $(CFLAGS) $(uts)/fileIO/fileIO.c

plasticPingRateN_recW.o: $(nro)/plasticPingRateN_recW/plasticPingRateN_recW.c
	gcc $(CFLAGS) $(nro)/plasticPingRateN_recW/plasticPingRateN_recW.c

plasticRateN_recW.o: $(nro)/plasticRateN_recW/plasticRateN_recW.c
	gcc $(CFLAGS) $(nro)/plasticRateN_recW/plasticRateN_recW.c


clean:
	rm -f $(name) $(objects)

cleanest:
	rm -f $(name) $(objects) *.dat

