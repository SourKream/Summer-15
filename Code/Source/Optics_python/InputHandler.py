import Optics as Op
import numpy as np
x = np.ones((1500,951));
y = Op.optics()
y.setMatrix(x)