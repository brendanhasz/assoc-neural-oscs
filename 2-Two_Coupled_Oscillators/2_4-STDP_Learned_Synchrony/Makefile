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

name = STDP_Learned_Synchrony

objects =	STDP_Learned_Synchrony.o \
		rateN.o \
		rateSTDP.o \
		get_last_period.o \
                l2peaks.o \
                phdiff2.o \
                stderrvec.o \
                fileIO.o

$(name): $(objects)
	gcc $(OFLAGS) -o $(name) $(objects) -lm -lpthread

STDP_Learned_Synchrony.o: STDP_Learned_Synchrony.c
	gcc $(CFLAGS) STDP_Learned_Synchrony.c
		
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
		

clean:
	rm -f $(name) $(objects)

cleanest:
	rm -f $(name) $(objects) *.dat

