# Plotter for 2_2

import sys
import os
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../graphing/'))
if path not in sys.path:
    sys.path.insert(1,path)
import plot_tools
import math
import numpy as np
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

fname = 'EE_Attractor.dat'
tit = 'Steady-state Phase Difference\nX-Oxc EI=0.3, IE= -0.5, II=0'
xlab = eval("r'$\Delta\Phi_{0}$'")
ylab = eval("r'$W_{Xee}$'")
clab = eval("r'$\langle \Delta\Phi_{SS} \\rangle$'")
clims = [0, math.pi]
xran = [0, 2*math.pi]
yran = [0.1, 0.3]
plt.figure()
plot_tools.colorp(fname, tit, xlab, ylab, clab, clims, xran, yran)

# 3D plot
#data = np.loadtxt(fname)
#d1 = data.shape[0]
#d2 = data.shape[1]
#x = np.tile(np.linspace(0,2*math.pi, d1), (d2,1)).flatten()
#y = np.tile(np.linspace(0,2*math.pi, d2), (d1,1)).flatten()
#z = data.flatten()
#now plot it!
#f2 = plt.figure()
#ax2 = f2.gca(projection='3d')
#ax2 = f2.add_subplot(111, projection='3d')
#ax2.plot_trisurf(x, y, z, cmap=cm.jet, linewidth=0.2)
#ax2.plot_wireframe(x,y,z, rstride=1, cstride=1)

plt.show()

