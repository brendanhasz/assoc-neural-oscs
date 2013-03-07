# Plotter for 2_3

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math
import numpy as np
import matplotlib.pyplot as plt



# Before plasticity
fname = 'Learned_Synchrony_pre_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n before plasticity, X-Oxc EE=0.2, EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylab = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
xran = [0, 2*math.pi]
smooth = 10
yran = None
xlims = None
ylims = [-0.1, math.pi+0.1]
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran, yran, xlims, ylims)

# Plasticity, started IN-phase
# Rate
fnameINr = 'Learned_Synchrony_plas_IN_r.dat'
titINr = 'Plasticity run - started IN phase'
#titINr = 'Rates, during plasticity run - started IN phase'
xlabINr = eval("r'Time (100 $\mu$s)'")
ylabINr = 'Rate (Hz)'
#plot_tools.linep(fnameINr, titINr, xlabINr, ylabINr)
# Weight
fnameINw = 'Learned_Synchrony_plas_IN_w.dat'
#titINw = 'Synaptic Weight over time, during plasticity run - started IN phase'
xlabINw = eval("r'Time (ms)'")
ylabINw = 'Synaptic weight'
#plot_tools.linep(fnameINw, titINw, xlabINw, ylabINw)

dataINr = np.loadtxt(fnameINr)
dataINw = np.loadtxt(fnameINw)
fig = plt.figure()
ax1 = plt.subplot(2,1,1)
linesINr = plt.plot(dataINr)
plt.setp(linesINr, linewidth=2.0)
plt.title(titINr)
plt.xlabel(xlabINr)
plt.ylabel(ylabINr)
ax2 = plt.subplot(2,1,2)
linesINw = plt.plot(dataINw)
plt.setp(linesINw, linewidth=2.0)
plt.xlabel(xlabINw)
plt.ylabel(ylabINw)
plt.show()
    


# After IN plasticity
fnameINa = 'Learned_Synchrony_postIN_pdvpd.dat'
titINa = 'Steady-state Phase Difference as a function of Initial Phase Difference\n after plasticity, initIN, X-Oxc EI=0.3, IE= -0.5, II=0'
xlabINa = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylabINa = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
xranINa = [0, 2*math.pi]
yranINa = None
xlimsINa = None
ylimsINa = [-0.1, math.pi+0.1]
smooth_w = 10
#plot_tools.linep(fname, tit, xlab, ylab, smooth, xran, yran, xlims, ylims)
dataINa = np.loadtxt(fnameINa)
fig = plt.figure()
linesINa = plt.plot(dataINa)
plt.setp(linesINa, linewidth=2.0)
plt.title(titINa)
plt.xlabel(xlabINa)
plt.ylabel(ylabINa)
plt.xlim(xlimsINa)
plt.ylim(ylimsINa)
plt.show()


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
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran, yran, xlims, ylims)

