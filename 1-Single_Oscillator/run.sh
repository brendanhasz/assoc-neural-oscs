#!/bin/bash
make clean
make
./single_PING_group
python plotter.py

