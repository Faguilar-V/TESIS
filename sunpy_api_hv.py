##!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Copyright (C) Enero 2020
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
#
#Author: Fernando Rodrigo Aguilar Javier
#Author email: fermatsavant@☻gmail.com
#
#Detalles del codigo --------------------------------------------------------------------
#Solo es necesario cambiar el campo de la variable path para que pandas encuentre el archivo
#
#
##################################%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%################################

"""
Created on Mon Dec 30 19:46:27 2019

@author: fermat
"""

import glob
import pandas as pd
from sunpy.net.helioviewer import HelioviewerClient
import sunpy
from astropy.units import Quantity
from sunpy.map import Map
from matplotlib.image import imread
import matplotlib.pyplot as plt
from PIL import Image

def get_images(path):
    #constantes
    for file in glob.glob('%s/*.dat' % (path)):
        df_solarflayers = pd.read_csv(file, sep='\t', header=None)#, usecols=[0, 1, 2], names=['STARTT', 'MAXFlux', 'ENDT'])#, index=None)
        for index, event in df_solarflayers.iterrows():   
            for c in range(2):
                year, month, day, hour, minute, second = event[c][:4], event[c][5:7], event[c][8:10], event[c][11:13], event[c][14:16], event[c][17:19]
                print('La imagen con fecha %s se esta descargando ...' % (year + '/' + month + '/' + day + ':' + hour + ':' + minute + ':' + second + '\n'))
                hv = HelioviewerClient() 
                
#                data_sources = hv.get_data_sources()
                filepath = hv.download_jp2('%s/%s/%s %s:%s:%s' % (year, month, day, hour, minute, second), observatory='SDO', instrument='HMI', measurement='magnetogram')

if __name__ == '__main__':
    #sunpy.config.set('downloads', 'c:\\Users\\ventas\\Downloads\\ENES\\pruebas')
    path = 'c:\\Users\\ventas\\Downloads\\ENES\\pruebas\\data\\sun_Data\\database-rev5\\database\\2017\\'
    get = get_images(path)
    
    
    #Ejemplo obtencion de región activa  
    #hv = HelioviewerClient() 
    #data_sources = hv.get_data_sources() 
    #filepath = hv.download_jp2('2012/07/05 00:30:00', observatory='SDO', instrument='HMI', measurement='magnetogram')
    #hmi = Map(filepath)
    #xrange = Quantity([200, 550], 'arcsec')  
    #yrange = Quantity([400, 200], 'arcsec')  
    #hmi.submap(xrange, yrange).peek()
   