# -*- coding: utf-8 -*-
"""
Created on Tue Jan 21 18:48:31 2020

@author: ventas
"""
import numpy as np


from PIL import Image

if __name__ == '__main__':
    path = 'c:\\Users\\ventas\\Downloads\\ENES\\pruebas\\hmi\\prueba\\'
    img = Image.open(path + '2010_12_06__06_53_41_305__SDO_HMI_HMI_magnetogram.jp2')
    arr_jp2 = np.array(img)
    print(arr_jp2)
    #im2 = Image.fromarray(ar, "CMYK").convert("RGB")
    #print(file_typer.from_buffer(bts))
        
    #plt.figure()
    #plt.imshow(im2)
    #plt.show()