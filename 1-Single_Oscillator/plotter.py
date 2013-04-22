# Plotter for 1.1

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import matplotlib.pyplot as plt
import numpy as np

fname = 'single_PING_group.dat'
tit = 'Single PING Oscillator'
xlab = eval("r'Time ($100 \mu$s)'")
ylab = 'Rate (Hz)'
s = 0
xran = None
yran = None
xlims = [5000, 8000]


plt.figure()
lines = plot_tools.linep(fname,tit,xlab,ylab,s,xran,yran,xlims)
plt.setp(lines[0], color='g')
plt.setp(lines[1], color='r')
plt.legend(('Excitatory','Inhibitory'))
plt.show()

