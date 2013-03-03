#!/bin/bash
cd ../../../graphing
echo "Plotting..."
#initially in-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_rate.dat','Coupled PING oscillators w/ plasticity - init IN','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_w.dat','Coupled PING oscillators w/ plasticity - init IN','Time','Synaptic strength')" &

# Initially out-of-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_rate_iOUT.dat','Coupled PING oscillators w/ plasticity - init OUT','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_w_iOUT.dat','Coupled PING oscillators w/ plasticity - init OUT','Time','Synaptic strength')" &

