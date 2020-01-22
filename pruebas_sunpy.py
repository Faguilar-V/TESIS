# -*- coding: utf-8 -*-
"""
Created on Tue Jan 21 11:05:34 2020

@author: ventas

from sunpy.net.helioviewer import HelioviewerClient
from sunpy.map import Map

import matplotlib.pyplot as plt

hv = HelioviewerClient()
file = hv.download_jp2('2012/01/01', observatory="SDO", instrument="HMI",
                       measurement="304", Source_id=19) 
#('SDO', 'HMI', None, 'magnetogram'): 19

aia = Map(file)  
aia.peek() 
"""

from sunpy.net.helioviewer import HelioviewerClient
#from astropy.units import Quantity
#from sunpy.map import Map
hv = HelioviewerClient()  
data_sources = hv.get_data_sources()  
filepath = hv.download_jp2('2012/07/05 00:30:00', observatory='SDO',
                           instrument='HMI', measurement='magnetogram')  
#hmi = Map(filepath)  
#xrange = Quantity([200, 550], 'arcsec')  
#yrange = Quantity([-400, 200], 'arcsec')  
#hmi.submap(xrange, yrange).peek()  