# Plotter for 1.1

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import matplotlib.pyplot as plt

fname = 'pingRateN_tester_iIN_ssIN.dat'
tit = eval("r'Two coupled PING Oscillator, $\Delta\Psi_0=0$, $\Delta\Psi_{SS}=0$'")
xlab = eval("r'Time ($100 \mu$s'")
ylab = 'Rate (Hz)'
plt.figure()
plot_tools.linep(fname,tit,xlab,ylab)

#I IN, SS OUT
fname = 'pingRateN_tester_iIN_ssOUT.dat'
tit = eval("r'Two coupled PING Oscillator, $\Delta\Psi_0=0$, $\Delta\Psi_{SS}=\pi$'")
xlab = eval("r'Time ($100 \mu$s'")
ylab = 'Rate (Hz)'
plt.figure()
plot_tools.linep(fname,tit,xlab,ylab)

#I OUT, SS IN 
fname = 'pingRateN_tester_iOUT_ssIN.dat'
tit = eval("r'Two coupled PING Oscillator, $\Delta\Psi_0=\pi$, $\Delta\Psi_{SS}=0$'")
xlab = eval("r'Time ($100 \mu$s'")
ylab = 'Rate (Hz)'
plt.figure()
plot_tools.linep(fname,tit,xlab,ylab)

#I OUT, SS OUT
fname = 'pingRateN_tester_iOUT_ssOUT.dat'
tit = eval("r'Two coupled PING Oscillator, $\Delta\Psi_0=\pi$, $\Delta\Psi_{SS}=\pi$'")
xlab = eval("r'Time ($100 \mu$s'")
ylab = 'Rate (Hz)'
plt.figure()
plot_tools.linep(fname,tit,xlab,ylab)

plt.show()

