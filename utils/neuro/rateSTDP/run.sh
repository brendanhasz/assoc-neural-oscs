#! /bin/bash
# Compile, run, and plot rateSTDP_tester

make clean
make
./rateSTDP_tester
python plotter.py &

