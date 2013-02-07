#!/bin/bash
cd ../../../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../utils/neuro/pingRateN/pingRateN_tester_iIN_ssIN.dat','Two coupled PING oscillators - started IN-phase, SS IN','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/pingRateN/pingRateN_tester_iIN_ssOUT.dat','Two coupled PING oscillators - started IN-phase, SS OUT','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/pingRateN/pingRateN_tester_iOUT_ssIN.dat','Two coupled PING oscillators - started OUT-phase, SS IN','Time (100 us)','Rate (Hz)')" &
python -c "import plot_tools; plot_tools.linep('../utils/neuro/pingRateN/pingRateN_tester_iOUT_ssOUT.dat','Two coupled PING oscillators - started OUT-phase, SS OUT','Time (100 us)','Rate (Hz)')" &
