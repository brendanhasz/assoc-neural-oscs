#!/bin/bash
cd ../graphing
echo "Plotting..."
python -c "import plot_tools; plot_tools.linep('../1-Single_Oscillator/single_PING_group.dat','Single PING oscillator','Time (100 us)','Rate (Hz)')" &
