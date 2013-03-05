# Plotter for 2_3

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math

fname = 'Learned_Synchrony_pre_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n before plasticity, X-Oxc EE=0.2, EI=0.3, IE= -0.5, II=0'
xlab = 'Init phase difference'
ylab = 'Steady-state phase difference'
xran = [0, 2*math.pi]
smooth = 10
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran)

