#!/bin/bash
cd ../../../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../utils/neuro/rateN/rateN_tester.dat','Single PING oscillator','Time (100 us)','Rate (Hz)')" &
