# Makefile for rateSTDP_tester
#
# DEPENDENCIES:
# rateSTDP_tester
#   rateSTDP.c
#       ../../fileIO/fileIO.c
#   ../rateN/rateN.c
#   ../get_last_period/get_last_period.c
#       ../rateN/rateN.c
#       ../../sig_proc/l2peaks.c

DFLAGS = -g
OFLAGS = $(DFLAGS) 
CFLAGS = $(DFLAGS) -c

uts = ../..
nro = ..

name = rateSTDP_tester

objects = 	rateSTDP_tester.o \
		rateSTDP.o \
		rateN.o \
		fileIO.o \
		get_last_period.o \
		l2peaks.o

	
$(name): $(objects)
	gcc $(OFLAGS) -o $(name) $(objects) -lm
	
rateSTDP_tester.o: rateSTDP_tester.c
	gcc $(CFLAGS) rateSTDP_tester.c
	
rateSTDP.o: rateSTDP.c
	gcc $(CFLAGS) rateSTDP.c

rateN.o: $(nro)/rateN/rateN.c
	gcc $(CFLAGS) $(nro)/rateN/rateN.c

fileIO.o: $(uts)/fileIO/fileIO.c
	gcc $(CFLAGS) $(uts)/fileIO/fileIO.c

get_last_period.o: $(nro)/get_last_period/get_last_period.c
	gcc $(CFLAGS) $(nro)/get_last_period/get_last_period.c

l2peaks.o: $(uts)/sig_proc/l2peaks.c
	gcc $(CFLAGS) $(uts)/sig_proc/l2peaks.c


clean :
	rm $(name) $(objects)

cleanest :
	rm $(name) $(objects) *.dat
