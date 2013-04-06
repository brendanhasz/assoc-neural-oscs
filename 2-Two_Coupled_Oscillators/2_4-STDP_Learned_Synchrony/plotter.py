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

#Plot STDP kernel
print "plotting fig 1 of 3"
fname = 'rateSTDP_STDPkernel.dat'
tit = 'STDP kernel'
xlab = 'Tau'
ylab = 'Synaptic weight change'
plt.figure()
plt.title(tit)
plt.xlabel(xlab)
plt.ylabel(ylab)
data = np.loadtxt(fname)
x = np.linspace(-100,100,data.size)
plt.plot(x, data, color='black', linewidth=2.0)
ax = plt.gca()
ax.fill_between(x, data, 0, where=data>0, facecolor='blue', interpolate=True)
ax.fill_between(x, data, 0, where=data<0, facecolor='red', interpolate=True)
plt.xlim([-100, 100])


# Plot cumulative weight
print "plotting fig 2 of 3"
fname = 'cum_weight.dat'
tit = 'Cross-oscillator E->E weights over time\nTwo coupled oscillators'
xlab = 'Time (ms)'
ylab = eval("r'$W_{Xee}$'")
plt.figure()
plot_tools.linep(fname, tit, xlab, ylab) 


'''
# Plot cumulative rate
fname = 'cum_rate.dat'
#tit = 'Rate over time\nTwo coupled oscillators'
tit = ''
xlab = 'Time (ms)'
ylab = 'Rate (Hz)'
ax2=plt.subplot(2,1,2)
plot_tools.linep(fname, tit, xlab, ylab) 
'''

#plot cumulative phdiffs
print "plotting fig 3 of 3"
fname = 'cum_phdiffs.dat'
tit = 'Phase Differences over time'
xlab = 'Init phase diff'
ylab = 'Time (step)'
clab = 'SS phdiff'
clims = [0, 2*math.pi]
plt.figure()
plot_tools.colorp(fname, tit, xlab, ylab, clab, clims)


'''
# Plot init pdvec
fname = 'pdvec.dat'
tit = 'Initial phdiff vs SS phdiff w/ init weights'
xlab = 'Init phdiff'
ylab = 'SS phdiff'
plt.figure()
plot_tools.linep(fname, tit, xlab, ylab) 
'''

# Plot avg weights w/ errorbars
fname_avg = 'Wxee_avg.dat'
fname_stderr = 'Wxee_stderr.dat'
tit = 'X-osc E->E weights over time'
xlab = 'Time (step)'
ylab = 'X-osc E->E weight'
data_avg = np.loadtxt(fname_avg)
data_stderr= np.loadtxt(fname_stderr)
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
y1 = data_avg[:,0]
y2 = data_avg[:,1]
yerr1 = data_stderr[:,0]
yerr2 = data_stderr[:,1]
plt.figure()
plt.title(tit)
plt.xlabel(xlab)
plt.ylabel(ylab)
plt.errorbar(x, y1, yerr=yerr1, color='blue', linewidth=2.0)
plt.errorbar(x, y2, yerr=yerr2, color='green', linewidth=2.0)


# Plot average phdiffs
print "plotting fig "
fname = 'phdiff_avg.dat'
tit = 'Phase Differences over time'
xlab = 'Time (step)'
ylab = 'Init phdiff'
clab = 'SS phdiff'
clims = [0, 2*math.pi]
plt.figure()
plot_tools.colorp(fname, tit, xlab, ylab, clab, clims)


#SHOW ALL THE PLOTS
plt.show()
