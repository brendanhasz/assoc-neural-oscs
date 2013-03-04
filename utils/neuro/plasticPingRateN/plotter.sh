#!/bin/bash
cd ../../../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN/plasticPingRateN_tester_iIN.dat','Two coupled PING oscillators w/ plasticity - started IN-phase','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN/plasticPingRateN_tester_iOUT.dat','Two coupled PING oscillators w/ plasticity - started OUT-of-phase','Time (100 us)','Rate (Hz)')" &
