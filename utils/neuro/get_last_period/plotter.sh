#!/bin/bash
cd ../../../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../utils/neuro/get_last_period/get_last_period_tester.dat','Single PING oscillator - last period','Time (100 us)','Rate (Hz)')" &
