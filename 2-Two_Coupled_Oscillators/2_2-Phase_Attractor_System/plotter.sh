#!/bin/bash
cd ../../graphing
echo "Plotting..."
#Phase Differences
python -c "import plot_tools; plot_tools.colorp('../2-Two_Coupled_Oscillators/2_2-Phase_Attractor_System/EE_Attractor.dat'\
,'Steady-State Phase Difference, X-Osc EE=0-0.2 EI=0.3 IE=-.5 II=0','Init phase difference','EE X-osc syn str (0 to 0.333333333333333333333333333333333')" &

