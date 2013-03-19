# Plotter for 2_3

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools as pt
import math
import numpy as np
import matplotlib.pyplot as plt

# STDP Kernel
fname_k = 'rateSTDP_STDPkernel.dat'
tit_k = 'Spike-time Dependent Plasticity Kernel'
xlab_k = 'Time (ms)'
ylab_k = 'Synaptic change'
smooth_w = 0
xran_k = [-100, 100]
plt.figure()
pt.linep(fname_k, tit_k, xlab_k, ylab_k, smooth_w, xran_k)


# Plasticity, started IN-phase
# Rate
fname_rI = 'rateSTDP_tester_rI.dat'
tit_rI = 'Plasticity run - started IN phase'
xlab_rI = ' '
ylab_rI = 'Rate (Hz)'
# Weight
fname_wI = 'rateSTDP_tester_wI.dat'
tit_wI = ' '
xlab_wI = eval("r'Time (100 $\mu$s)'")
ylab_wI = 'Synaptic Weight'
#Plot
plt.figure()
ax1=plt.subplot(2,1,1) #Rates over init-IN plasticity run
pt.linep(fname_rI, tit_rI, xlab_rI, ylab_rI)
ax2=plt.subplot(2,1,2) #Weights over init-IN plasticity run
pt.linep(fname_wI, tit_wI, xlab_wI, ylab_wI)


# Plasticity, started OUT-of-phase
# Rate
fname_rO = 'rateSTDP_tester_rO.dat'
tit_rO = 'Plasticity run - started OUT of phase'
xlab_rO = ' '
ylab_rO = 'Rate (Hz)'
# Weight
fname_wO = 'rateSTDP_tester_wO.dat'
tit_wO = ' '
xlab_wO = eval("r'Time (100 $\mu$s)'")
ylab_wO = 'Synaptic Weight'
#Plot
plt.figure()
ax3=plt.subplot(2,1,1) #Rates over init-OUT plasticity run
pt.linep(fname_rO, tit_rO, xlab_rO, ylab_rO)
ax4=plt.subplot(2,1,2) #Weights over init-OUT plasticity run
pt.linep(fname_wO, tit_wO, xlab_wO, ylab_wO)


#SHOW ALL THE PLOTS
plt.show()

