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

numtrials = 32


# Plot avg weights w/ errorbars for in
print "plotting..."
fname_avg = 'perccorr_avg.dat'
fname_stderr = 'perccorr_stderr.dat'
tit = 'Accuracy as a function of training time'
xlab = 'Training Time (10 500ms presentations)'
ylab = 'Average Accuracy'


data_avg_all = np.loadtxt(fname_avg)
data_avg = data_avg_all[0::10]
data_stderr_all = np.loadtxt(fname_stderr)
data_stderr = data_stderr_all[0::10]
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
y = data_avg
yerr = data_stderr*np.sqrt(numtrials) #use STD, not stderr
plt.figure()
plt.title(tit)
plt.xlabel(xlab)
plt.ylabel(ylab)
plt.errorbar(x, y, yerr=yerr, color='green')



#SHOW ALL THE PLOTS
plt.show()
