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

numtrials = 40

# Plot accuracy for first pattern
print "plotting plot 1 of 2..."
fname_all = 'perccorr_all.dat'
tit = 'Pattern Separation Accuracy as a function of training time'
xlab = 'Training Time (500ms presentations)'
ylab = 'Average Accuracy\n1st Training Pattern'
data_all = np.loadtxt(fname_all).transpose()
#data_all = data_all.transpose()
data_avg = np.mean(data_all, axis=1)
data_stderr = np.std(data_all, axis=1)/np.sqrt(numtrials)
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
plt.figure()
plt.subplot(2,1,1)
plt.title(tit)
#plt.xlabel(xlab)
plt.ylabel(ylab)
plt.errorbar(x, data_avg, yerr=data_stderr, color='green')


# Plot accuracy for second pattern
print "plotting plot 2 of 2..."
fname_all2 = 'perccorr2_all.dat'
tit = 'Accuracy as a function of training time for second pattern'
xlab = 'Training Time (500ms presentations)'
ylab = 'Average Accuracy\n2nd Training Pattern'
data_all = np.loadtxt(fname_all2).transpose()
#data_all = data_all.transpose()
data_avg = np.mean(data_all, axis=1)
data_stderr = np.std(data_all, axis=1)/np.sqrt(numtrials)
x = np.linspace(0,data_avg.shape[0],data_avg.shape[0])
#plt.figure()
plt.subplot(2,1,2)
#plt.title(tit)
plt.xlabel(xlab)
plt.ylabel(ylab)
plt.errorbar(x, data_avg, yerr=data_stderr, color='blue')


#SHOW ALL THE PLOTS
plt.show()
