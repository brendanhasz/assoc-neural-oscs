# Plotter for 2_2

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math
import matplotlib.pyplot as plt

# Phase Differences
# Init in
print "Plotting graph 1 of 9..."
fname = 'Phdiff_init_IN.dat'
tit = 'Phase Difference, Init-IN, X-Osc syn str param space'
xlab = 'II (IE) Synaptic Strength'
ylab = 'EE (EI) Synaptic Strength'
clab = eval("r'$\Delta\Phi_{SS}$'")
clims = [0, math.pi]
xran = None
yran = None 
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Init out 
print "Plotting graph 2 of 9..."
fname = 'Phdiff_init_OUT.dat'
tit = 'Phase Difference, Init-OUT, X-Osc syn str param space'
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Difference 
print "Plotting graph 3 of 9..."
fname = 'Phdiff_DIFF.dat'
tit = 'Difference in Phase Difference\nX-osc Syn. Weight Param Space'
clab = eval("r'$\Delta\Phi_{SS, \Delta\Phi_0=0}-\Delta\Phi_{SS, \Delta\Phi_0=\pi}$'")
clims = [-math.pi, math.pi]
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)



'''
# Frequencies
# Init in
print "Plotting graph 4 of 9..."
fname = 'Freq_init_IN.dat'
tit = 'Frequency, Init-IN, X-Osc syn str param space'
clab = eval("r'$f$ (Hz)'")
clims = None
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Init out 
print "Plotting graph 5 of 9..."
fname = 'Freq_init_OUT.dat'
tit = 'Frequency, Init-OUT, X-Osc syn str param space'
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Difference 
print "Plotting graph 6 of 9..."
fname = 'Freq_DIFF.dat'
tit = 'Frequency, DIFFERENCE, X-Osc syn str param space'
clab = eval("r'$f_{\Psi_0=0}-f_{\Psi_0=0}$ (Hz)'")
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)



# Amplitudes
# Init in
print "Plotting graph 7 of 9..."
fname = 'Amp_init_IN.dat'
tit = 'Amplitude, Init-IN, X-Osc syn str param space'
clab = "RMS Amplitude"
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Init out 
print "Plotting graph 8 of 9..."
fname = 'Amp_init_OUT.dat'
tit = 'Amplitude, Init-OUT, X-Osc syn str param space'
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

# Difference 
print "Plotting graph 9 of 9..."
fname = 'Amp_DIFF.dat'
tit = 'Amplitude, DIFFERENCE, X-Osc syn str param space'
clab = eval("r'$A_{\Psi_0=0}-A_{\Psi_0=0}$ (Hz)'")
plt.figure()
plot_tools.colorp_scaled(fname, tit, xlab, ylab, clab, clims, xran, yran)

'''

#SHOW THE PLOTS
plt.show()

