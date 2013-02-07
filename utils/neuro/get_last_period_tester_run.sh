#!/bin/bash
make -f get_last_period_tester.mak
./get_last_period_tester
./get_last_period_tester_plotter.sh
