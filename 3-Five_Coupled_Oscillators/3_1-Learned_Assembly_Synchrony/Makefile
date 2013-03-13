# Learned_group_synchrony.c
#   ../../utils/multithreads/multithreads.c
#   ../../utils/stats/stats.c
#   Learned_group_synchrony_worker.c
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

DFLAGS = -g
CFLAGS = $(DFLAGS) -c
OFLAGS = $(DFLAGS)

uts = ../../utils
nro = $(uts)/neuro

name = Learned_group_synchrony

objects =	Learned_group_synchrony.o \
                multithreads.o \
                stats.o \
		Learned_group_synchrony_worker.o \
		pingRateN.o \
		rateN.o \
		get_last_period.o \
		l2peaks.o \
		phdiff2.o \
                fileIO.o \
                plasticPingRateN_recW.o \
                plasticRateN_recW.o

$(name): $(objects)
	gcc $(OFLAGS) -o $(name) $(objects) -lm -lpthread

Learned_group_synchrony.o: Learned_group_synchrony.c
	gcc $(CFLAGS) Learned_group_synchrony.c
		
multithreads.o: $(uts)/multithreads/multithreads.c
	gcc $(CFLAGS) $(uts)/multithreads/multithreads.c

stats.o: $(uts)/stats/stats.c
	gcc $(CFLAGS) $(uts)/stats/stats.c
		
Learned_group_synchrony_worker.o: Learned_group_synchrony_worker.c
	gcc $(CFLAGS) Learned_group_synchrony_worker.c
		
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

