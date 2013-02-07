#TwoOsc_explorer
#	linspace
#	get_last_period
#		rateN
#		l2peaks
#	pingRateN
#		rateN
#	phdiff2
#		l2peaks
#	l2peaks
#	amp
#		math lib
#	matix4dTo2d
#	fileIO

name = TwoOsc_explorer

objects =	TwoOsc_explorer.o \
		linspace.o \
		get_last_period.o \
		rateN.o \
		l2peaks.o \
		pingRateN.o \
		phdiff2.o \
		amp.o \
		matrix4dTo2d.o \
		fileIO.o
			
headers =	../../utils/vectors/linspace.h \
		../../utils/neuro/get_last_period/get_last_period.h \
		../../utils/neuro/pingRateN/pingRateN.h \
		../../utils/sig_proc/phdiff2.h \
		../../utils/sig_proc/l2peaks.h \
		../../utils/sig_proc/amp.h \
		../../utils/graphing/matrix4dTo2d.h \
		../../utils/fileIO/fileIO.h

	
$(name): $(objects)
	gcc -o $(name) $(objects) -lm
	
$(name).o: $(name).c $(headers)
	gcc -c $(name).c

linspace.o:	../../utils/vectors/linspace.c
	gcc -c ../../utils/vectors/linspace.c
	
get_last_period.o:	../../utils/neuro/get_last_period/get_last_period.c \
					../../utils/neuro/rateN/rateN.h \
					../../utils/sig_proc/l2peaks.h
	gcc -c ../../utils/neuro/get_last_period/get_last_period.c

rateN.o: ../../utils/neuro/rateN/rateN.c
	gcc -c ../../utils/neuro/rateN/rateN.c

l2peaks.o: ../../utils/sig_proc/l2peaks.c
	gcc -c ../../utils/sig_proc/l2peaks.c

pingRateN.o:	../../utils/neuro/pingRateN/pingRateN.c \
				../../utils/neuro/rateN/rateN.h
	gcc -c ../../utils/neuro/pingRateN/pingRateN.c

phdiff2.o:	../../utils/sig_proc/phdiff2.c \
			../../utils/sig_proc/l2peaks.h
	gcc -c ../../utils/sig_proc/phdiff2.c

amp.o: ../../utils/sig_proc/amp.c
	gcc -c ../../utils/sig_proc/amp.c

matrix4dTo2d.o: ../../utils/graphing/matrix4dTo2d.c
	gcc -c ../../utils/graphing/matrix4dTo2d.c

fileIO.o: ../../utils/fileIO/fileIO.c
	gcc -c ../../utils/fileIO/fileIO.c


clean :
	rm -f $(name) $(objects) *.dat
