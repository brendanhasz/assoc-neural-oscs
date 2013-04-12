# STDP_Learned_Synchrony
#   rateN
#   get_last_period
#       l2peaks
#   rateSTDP
#   phdiff

DFLAGS = -g
CFLAGS = $(DFLAGS) -c
OFLAGS = $(DFLAGS)

uts = ../../utils
nro = $(uts)/neuro

name = Pattern_Separation

objects =	Pattern_Separation.o \
		Pattern_Separation_worker.o \
		rateN.o \
		rateSTDP.o \
		get_last_period.o \
                l2peaks.o \
                phdiff2.o \
                stderrvec.o \
                multithreads.o \
                fileIO.o

$(name): $(objects)
	gcc $(OFLAGS) -o $(name) $(objects) -lm -lpthread

Pattern_Separation.o: Pattern_Separation.c
	gcc $(CFLAGS) Pattern_Separation.c
		
Pattern_Separation_worker.o: Pattern_Separation_worker.c
	gcc $(CFLAGS) Pattern_Separation_worker.c
		
rateN.o: $(nro)/rateN/rateN.c
	gcc $(CFLAGS) $(nro)/rateN/rateN.c
		
rateSTDP.o: $(nro)/rateSTDP/rateSTDP.c
	gcc $(CFLAGS) $(nro)/rateSTDP/rateSTDP.c
		
get_last_period.o: $(nro)/get_last_period/get_last_period.c
	gcc $(CFLAGS) $(nro)/get_last_period/get_last_period.c
		
l2peaks.o: $(uts)/sig_proc/l2peaks.c
	gcc $(CFLAGS) $(uts)/sig_proc/l2peaks.c
		
phdiff2.o: $(uts)/sig_proc/phdiff2.c
	gcc $(CFLAGS) $(uts)/sig_proc/phdiff2.c
		
fileIO.o: $(uts)/fileIO/fileIO.c
	gcc $(CFLAGS) $(uts)/fileIO/fileIO.c
		
stderrvec.o: $(uts)/stats/stderrvec.c
	gcc $(CFLAGS) $(uts)/stats/stderrvec.c
		
multithreads.o: $(uts)/multithreads/multithreads.c
	gcc $(CFLAGS) $(uts)/multithreads/multithreads.c
		

clean:
	rm -f $(name) $(objects)

cleanest:
	rm -f $(name) $(objects) *.dat

