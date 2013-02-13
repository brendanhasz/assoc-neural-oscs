#EE_Attractor
#	EE_Attractor_worker
#		multithreads
#		linspace
#		get_last_period
#			rateN
#			l2peaks
#		pingRateN
#			rateN
#		phdiff2
#			l2peaks
#	multithreads
#	asave

name = EE_Attractor

uts = ../../utils

objects =	EE_Attractor.o \
		EE_Attractor_worker.o \
		multithreads.o \
		linspace.o \
		get_last_period.o \
		rateN.o \
		l2peaks.o \
		pingRateN.o \
		phdiff2.o \
		fileIO.o
			
$(name): $(objects)
	gcc -o $(name) $(objects) -lm -lpthread
	
EE_Attractor.o: EE_Attractor.c \
		$(uts)/multithreads/multithreads.h \
		EE_Attractor_worker.h \
		$(uts)/fileIO/asave.h
	gcc -c EE_Attractor.c

EE_Attractor_worker.o:	EE_Attractor_worker.c \
			$(uts)/multithreads/multithreads.h \
			$(uts)/vectors/linspace.h \
			$(uts)/neuro/get_last_period/get_last_period.h \
			$(uts)/neuro/pingRateN/pingRateN.h \
			$(uts)/sig_proc/phdiff2.h
	gcc -c EE_Attractor_worker.c
	
multithreads.o:	$(uts)/multithreads/multithreads.c \
		$(uts)/multithreads/multithreads.h
	gcc -c $(uts)/multithreads/multithreads.c

linspace.o:	$(uts)/vectors/linspace.c
	gcc -c $(uts)/vectors/linspace.c
	
get_last_period.o:	$(uts)/neuro/get_last_period/get_last_period.c \
			$(uts)/neuro/rateN/rateN.h \
			$(uts)/sig_proc/l2peaks.h
	gcc -c $(uts)/neuro/get_last_period/get_last_period.c

rateN.o: $(uts)/neuro/rateN/rateN.c
	gcc -c $(uts)/neuro/rateN/rateN.c

l2peaks.o: $(uts)/sig_proc/l2peaks.c
	gcc -c $(uts)/sig_proc/l2peaks.c

pingRateN.o:	$(uts)/neuro/pingRateN/pingRateN.c \
		$(uts)/neuro/rateN/rateN.h
	gcc -c $(uts)/neuro/pingRateN/pingRateN.c

phdiff2.o:	$(uts)/sig_proc/phdiff2.c \
		$(uts)/sig_proc/l2peaks.h
	gcc -c $(uts)/sig_proc/phdiff2.c

fileIO.o: $(uts)/fileIO/fileIO.c
	gcc -c $(uts)/fileIO/fileIO.c


clean :
	rm -f $(name) $(objects)
