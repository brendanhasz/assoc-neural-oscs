import numpy as np
import matplotlib.pyplot as plt


def open_array(filename):
    f = open(filename, 'r')
    l = [[float(i) for i in l.split()] for l in f] #create list of vals
    a = [[e if e==e else 0 for e in r] for r in l] #check for nans
    f.close()
    return a


def linep(filename, tit=' ', xlab=' ', ylab=' '):
    '''
    Plots a line or set of lines
    http://matplotlib.org/users/pyplot_tutorial.html
    '''
    data = np.loadtxt(filename)
    fig = plt.figure()
    lines=plt.plot(data)
    plt.setp(lines, linewidth=2.0)
    plt.title(tit)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    plt.show()
    '''
    plt.axis([xmin, xmax, ymin, ymax])
    plt.grid(False)
    plt.figure(1)
    plt.subplot(211)
    plt.plot(~)
    plt.subplot(212)
    plt.plot(~)
    '''
    return fig


def colorp(filename, tit=' ', xlab=' ', ylab=' ', clims=0):
    '''
    Plots an image w/ a colormap
    http://matplotlib.org/users/image_tutorial.html
    '''
    data = np.loadtxt(filename)
    plt.figure()
    imgplot = plt.imshow(data)
    #plt.pcolor(data, cmap='spectral')
    imgplot.set_cmap('spectral') #also 'jet', 'binary' (b&w)\
    plt.colorbar()
    #imgplot.set_interpolation('nearest') #pixelated
    imgplot.set_interpolation('bicubic') #blurry but smooth
    plt.title(tit)
    plt.xlabel(xlab)
    plt.ylabel(ylab)
    if clims != 0:
        imgplot.set_clim(clims[0],clims[1]) #set color limits
    #plt.colorbar()
    plt.show()

def colorp_scaled(filename, tit=' ', xlab=' ', ylab=' '):
	'''
	Plots an image w/ a colormap, and adjusts the dynamic range such
	that the upper and lower 5% of data are cropped out
	'''

	data = np.loadtxt(filename)
	themean = np.mean(data)
	thestd = np.std(data)
	stds = 3
	maxel = themean+stds*thestd
	minel = themean-stds*thestd
	data = [[minel if e<minel else maxel if e>maxel else e for e in r] for r in data]
	plt.figure()
	imgplot = plt.imshow(data)
	imgplot.set_cmap('spectral') #also 'jet', 'binary' (b&w)\
	plt.colorbar()
	imgplot.set_interpolation('nearest') #pixelated
	#imgplot.set_interpolation('bicubic') #blurry but smooth
	plt.title(tit)
	plt.xlabel(xlab)
	plt.ylabel(ylab)
	plt.show()
