import Optics as Op
import numpy as np
import scipy.io as sio

tempData = sio.loadmat('DataToPython.mat');

ind = tempData['ind'];
dist = tempData['dist'];

x = np.ones((1500,951));
y = Op.optics()
y.setMatrix(x)