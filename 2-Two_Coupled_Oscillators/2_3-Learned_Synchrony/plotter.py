# Plotter for 2_3

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math

# Before plasticity
fname = 'Learned_Synchrony_pre_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n before plasticity, X-Oxc EE=0.2, EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylab = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
xran = [0, 2*math.pi]
smooth = 10
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran)

# Plasticity, started IN-phase
# Rate
fname = 'Learned_Synchrony_plas_IN_r.dat'
tit = 'Rates, during plasticity run - started IN phase'
xlab = eval("r'Time (100 $\mu$s)'")
ylab = 'Rate (Hz)'
plot_tools.linep(fname, tit, xlab, ylab)
# Weight
fname = 'Learned_Synchrony_plas_IN_w.dat'
tit = 'Synaptic Weight over time, during plasticity run - started IN phase'
xlab = eval("r'Time (100 $\mu$s)'")
ylab = 'Synaptic weight'
plot_tools.linep(fname, tit, xlab, ylab)

# After IN plasticity
fname = 'Learned_Synchrony_postIN_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n after plasticity, initIN, X-Oxc EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylab = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
xran = [0, 2*math.pi]
smooth = 10
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran)




# Plasticity, started OUT-of-phase
# Rate
fname = 'Learned_Synchrony_plas_OUT_r.dat'
tit = 'Rates, during plasticity run - Started out-of-phase'
xlab = eval("r'Time (100 $\mu$s)'")
ylab = 'Rate (Hz)'
plot_tools.linep(fname, tit, xlab, ylab)
# Weight
fname = 'Learned_Synchrony_plas_OUT_w.dat'
tit = 'Synaptic Weight over time, during plasticity run - Started out-of-phase'
xlab = eval("r'Time (100 $\mu$s)'")
ylab = 'Synaptic weight'
plot_tools.linep(fname, tit, xlab, ylab)

# After OUT plasticity
fname = 'Learned_Synchrony_postOUT_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n after plasticity, init OUT-of-phase, X-Oxc EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylab = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
xran = [0, 2*math.pi]
smooth = 10
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran)

