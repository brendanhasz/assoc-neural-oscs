#!/bin/bash
cd ../../../graphing
echo "Plotting..."
#initially in-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_tester.dat','Coupled PING oscillators w/ plasticity - init IN','Time (100 us)','Rate (Hz)')" &

# Initially out-of-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_tester_iOUT.dat','Coupled PING oscillators w/ plasticity - init OUT','Time (100 us)','Rate (Hz)')" &

