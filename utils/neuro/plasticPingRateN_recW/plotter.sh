#!/bin/bash
cd ../../../graphing
echo "Plotting..."

# Initially in-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW_tester_iIN.dat','Two coupled PING oscillators w/ plasticity - started IN-phase','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW_tester_w_iIN.dat','Two coupled PING oscillators w/ plasticity - started IN-phase','Time (100 us)','Synaptic strength')" &

# Initially out-of-phase
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW_tester_iOUT.dat','Two coupled PING oscillators w/ plasticity - started OUT-of-phase','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW_tester_w_iOUT.dat','Two coupled PING oscillators w/ plasticity - started OUT-of-phase','Time (100 us)','Synaptic strength')" &
