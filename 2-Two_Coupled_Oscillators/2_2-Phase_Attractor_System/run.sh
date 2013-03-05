#!/bin/bash
make clean
make
./EE_Attractor
python plotter.py &

