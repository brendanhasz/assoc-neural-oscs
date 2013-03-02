#!/bin/bash
cd ../../../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_rate.dat','Coupled PING oscillators w/ plasticity','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_w.dat','Coupled PING oscillators w/ plasticity','Time','Synaptic strength')" &
#python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticRateN/plasticRateN_recW_tester_np.dat','Coupled PING oscillators w/o plasticity','Time','Synaptic strength')" &

