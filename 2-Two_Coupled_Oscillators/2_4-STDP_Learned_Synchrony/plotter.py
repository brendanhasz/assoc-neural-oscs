# Plotter for 2_4

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math
import numpy as np
import matplotlib.pyplot as plt

numtrials = 24

#Plot STDP kernel
print "plotting fig 1 of 5"
fname = 'rateSTDP_STDPkernel.dat'
tit = 'STDP kernel'
xlab = eval("r'$t_{post}-t_{pre}$ (ms)'")
ylab = 'Synaptic weight change'
plt.figure()
plt.title(tit)
plt.xlabel(xlab)
plt.ylabel(ylab)
data = np.loadtxt(fname)
print "Sum of kernel values is "+str(np.sum(data))
x = np.linspace(-100,100,data.size)
plt.plot(x, data, color='black', linewidth=2.0)
ax = plt.gca()
ax.fill_between(x, data, 0, where=data>0, facecolor='blue', interpolate=True)
ax.fill_between(x, data, 0, where=data<0, facecolor='red', interpolate=True)
plt.xlim([-100, 100])

# Plot avg weights w/ errorbars for in
print "plotting fig 2 of 5"
fname_avg = 'Wxee_avg.dat'
fname_stderr = 'Wxee_stderr.dat'
tit = 'X-osc E->E weights as a function of training time'
xlab = 'Time (10 500ms presentations)'
ylab = eval("r'$W_{Xee}$ (synchronized)'")
data_avg_all = np.loadtxt(fname_avg)
data_avg = data_avg_all[0::10]
data_stderr_all = np.loadtxt(fname_stderr)
data_stderr = data_stderr_all[0::10]
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
y1 = data_avg[:,0]
y2 = data_avg[:,1]
y = np.mean(data_avg, axis=1)
yerr1 = data_stderr[:,0]
yerr2 = data_stderr[:,1]
yerr = np.mean(data_stderr, axis=1)
yerr = yerr*np.sqrt(numtrials) #use STD, not stderr
plt.figure()
plt.subplot(2,1,1)
plt.title(tit)
#plt.xlabel(xlab)
plt.xlabel('')
plt.ylabel(ylab)
#plt.errorbar(x, y1, yerr=yerr1, color='blue')
#plt.errorbar(x, y2, yerr=yerr2, color='green')
plt.errorbar(x, y, yerr=yerr, color='green')


# Plot avg weights w/ errorbars for out
print "plotting fig 4 of 5"
fname_avg = 'Wxee_avg_out.dat'
fname_stderr = 'Wxee_stderr_out.dat'
tit = 'X-osc E->E weights over time'
xlab = 'Training time (10 500ms presentations)'
ylab = eval("r'$W_{Xee}$ (DEsynchronized)'")
data_avg_all = np.loadtxt(fname_avg)
data_avg = data_avg_all[0::10]
data_stderr_all = np.loadtxt(fname_stderr)
data_stderr = data_stderr_all[0::10]
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
y1 = data_avg[:,0]
y2 = data_avg[:,1]
y = np.mean(data_avg, axis=1)
yerr1 = data_stderr[:,0]
yerr2 = data_stderr[:,1]
yerr = np.mean(data_stderr, axis=1)
yerr = yerr*np.sqrt(numtrials)
#plt.figure()
plt.subplot(2,1,2)
#plt.title(tit)
plt.title('')
plt.xlabel(xlab)
plt.ylabel(ylab)
#plt.errorbar(x, y1, yerr=yerr1, color='blue')
#plt.errorbar(x, y2, yerr=yerr2, color='green')
plt.errorbar(x, y, yerr=yerr, color='blue')

# Plot average phdiffs for in
print "plotting fig 3 of 5"
fname = 'phdiff_avg.dat'
tit = 'S.S. Phase Differences \n as a function of training time \n for synchronized and DE-synchronized oscillators'
xlab = 'Training Time (500ms presentations)'
ylab = eval("r'$\Delta\Phi_0$ (synchronized)'")
clab = eval("r'$\langle \Delta\Phi_{SS} \\rangle$'")
clims = [0, math.pi]
xran = None
yran = [0, 2*math.pi]
plt.figure()
plot_tools.colorp(fname, tit, xlab, ylab, clab, clims, xran, yran)


# Plot average phdiffs for out
print "plotting fig 5 of 5"
fname = 'phdiff_avg_out.dat'
tit = 'S.S. Phase Differences \n as a function of training time \n for synchronized and DE-synchronized oscillators'
xlab = 'Training Time (500ms presentations)'
ylab = eval("r'$\Delta\Phi_0$ (DEsynchronized)'")
clab = eval("r'$\langle \Delta\Phi_{SS} \\rangle$'")
clims = [0, math.pi]
xran = None
yran = [0, 2*math.pi]
plt.figure()
plot_tools.colorp(fname, tit, xlab, ylab, clab, clims, xran, yran)

#SHOW ALL THE PLOTS
plt.show()
