#include<stdlib.h>
#include"help.h"
void imprimeInstrucciones(){
printf("usage: pakal [-wl wavelength / -nu frecuency] [-h high]\n");
printf(" [-f floor] [-detail nDetail] [-big nStep] \n");
printf(" [-r resolution]\n");
printf(" [-o output_file] [-t temperature_file]\n");
printf(" [-d density_file] [-xy x y] [-l line] [-v]\n");
printf(" [-min min_intensity] [-detail detail_is] [-? help]\n");
}
void imprimeAyuda(){
imprimeInstrucciones();
printf("Where: \n");
printf(" wavelenght Wavelength (mm). \n");
printf(" frecuency Frecuency (Hz) [43e9].\n");
printf(" high Cut High (solar radii) [2].\n");
printf(" floor Cut floor (solar radii) [-2].\n");
printf(" nDetail Length of integration step (km) [1].\n");
printf(" nStep Big integration step = nStep*nDetail [100] .\n");
printf(" resolution Image resolution (px) [5].\n");
printf(" output_file Output file [sun.dat].\n");
printf(" temperature_file Input temperature file [data/temperature.dat].\n");
printf(" density_file Input density file [data/density.dat].\n");
printf(" x y x,y image coordinate to calculate only.\n");
printf(" line The image line for integration.\n");
printf(" min_intensity The local minimal intensity to stop the detail"
"integration [1e-25].\n");
printf(" -v Verbose mode (file)\n");
}