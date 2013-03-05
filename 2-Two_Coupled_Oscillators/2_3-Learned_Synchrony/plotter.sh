#!/bin/bash
cd ../../graphing
echo "Plotting..."
#Phase Differences
python -c "import plot_tools; plot_tools.linep('../2-Two_Coupled_Oscillators/2_3-Learned_Synchrony/Learned_Synchrony_pre_pdvpd.dat'\
,'Steady-state phase difference as a function of initial phase difference,\n before plasticity, X-Osc EE=0-0.3 EI=0.3 IE=-.5 II=0','Init phase difference','Steady-state phase difference')" &

