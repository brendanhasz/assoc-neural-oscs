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
plt.figure()
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran, yran, xlims, ylims)


# Plasticity, started IN-phase
# Rate
fnameINr = 'Learned_Synchrony_plas_IN_r.dat'
titINr = 'Plasticity run - started IN phase'
xlabINr = eval("r'Time (100 $\mu$s)'")
ylabINr = 'Rate (Hz)'
# Weight
fnameINw = 'Learned_Synchrony_plas_IN_w.dat'
xlabINw = eval("r'Time (ms)'")
ylabINw = 'Synaptic weight'
#Plot
plt.figure()
ax1=plt.subplot(2,1,1) #Rates over init-IN plasticity run
plot_tools.linep(fnameINr, titINr, xlabINr, ylabINr)
ax2=plt.subplot(2,1,2) #Weights over init-IN plasticity run
plot_tools.linep(fnameINw, ' ', xlabINw, ylabINw, 0, None, None, None, [0.19, 0.31])

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
fig = plt.figure()
plot_tools.linep(fnameINa, titINa, xlabINa, ylabINa, smooth, xranINa, yranINa, xlimsINa, ylimsINa)



# Plasticity, started OUT-of-phase
# Rate
fnameOUTr = 'Learned_Synchrony_plas_OUT_r.dat'
titOUTr = 'Plasticity run - Started out-of-phase'
xlabOUTr = eval("r'Time (100 $\mu$s)'")
ylabOUTr = 'Rate (Hz)'
# Weight
fnameOUTw = 'Learned_Synchrony_plas_OUT_w.dat'
titOUTw = ' ' 
xlabOUTw = eval("r'Time (100 $\mu$s)'")
ylabOUTw = 'Synaptic weight'
plt.figure()
plt.subplot(2,1,1) #Rates over init-OUT plasticity run
plot_tools.linep(fnameOUTr, titOUTr, xlabOUTr, ylabOUTr)
plt.subplot(2,1,2) #Weights over init_IN plasticity run
plot_tools.linep(fnameOUTw, titOUTw, xlabOUTw, ylabOUTw, 0, None, None, None, [0,0.3])

# After OUT plasticity
fname = 'Learned_Synchrony_postOUT_pdvpd.dat'
tit = 'Steady-state Phase Difference as a function of Initial Phase Difference\n after plasticity, init OUT-of-phase, X-Oxc EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Psi_0 $ (Initial Phase diff)'")
ylab = eval("r'$\langle \Psi_{SS} \\rangle$ (Avg. Steady-state Phase diff)'")
plt.figure()
plot_tools.linep(fname, tit, xlab, ylab, smooth, xran, yran, xlims, ylims)

#SHOW ALL THE PLOTS
plt.show()
