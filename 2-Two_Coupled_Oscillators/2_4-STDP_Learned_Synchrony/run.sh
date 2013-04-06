#!/bin/bash
make cleanest
make
./STDP_Learned_Synchrony
python plotter.py


