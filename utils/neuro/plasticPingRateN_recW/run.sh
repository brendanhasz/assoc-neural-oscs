#!/bin/bash
make cleanest
make
./plasticPingRateN_recW_tester
./plotter.sh
