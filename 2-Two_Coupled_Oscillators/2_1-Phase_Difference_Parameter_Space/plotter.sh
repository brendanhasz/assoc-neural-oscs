#!/bin/bash
cd ../../graphing
echo "Plotting..."
#Phase Differences
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Phdiff_init_IN.dat'\
,'Phase Difference, Init-IN, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Phdiff_init_OUT.dat'\
,'Phase Difference, Init-OUT, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Phdiff_DIFF.dat'\
,'Phase Difference, DIFFERENCE, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &

#Frequencies
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Freq_init_IN.dat'\
,'Frequency, Init-IN, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Freq_init_OUT.dat'\
,'Frequency, Init-OUT, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Freq_DIFF.dat'\
,'Frequency, DIFFERENCE, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &

#Amplitude
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Amp_init_IN.dat'\
,'Amplitude, Init-IN, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Amp_init_OUT.dat'\
,'Amplitude, Init-OUT, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &
python -c "import plot_tools; plot_tools.colorp_scaled('../2-Two_Coupled_Oscillators/2_1-Phase_Difference_Parameter_Space/Amp_DIFF.dat'\
,'Amplitude, DIFFERENCE, X-Osc Syn. str. param space','II (IE)','EE (EI)')" &

