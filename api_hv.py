# -*- coding: utf-8 -*-
"""
Created on Fri Dec 20 18:22:54 2019

@author: ventas
"""

import unirest
import numpy as np
import matplotlib.pyplot as plt

r = unirest.get("https://api.helioviewer.org/v2/getJP2Image/",
            #headers = {"id":" 7654321"},
            params = {"date":"2014-01-01T23:59:59Z", "sourceId":14, "jpip":False},
#            auth = (),
            callback = None)
im = np.array(r.body)#,  dtype=np.bool_)
plt.imshow(im)
#plt.show()