#!/bin/bash
make cleanest
make
./plasticPingRateN_tester
./plotter.sh
