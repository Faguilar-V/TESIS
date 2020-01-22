#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lineal.h"
lineal ilineal(char *file){
lineal pol;
FILE *f;
int n;
int i=0;
if ((f = fopen(file, "rw")) > 0){
n=0;
while (fscanf(f,"%Le %Le",&(pol.x[n]),&(pol.y[n])) > 0) n++;
n--;
for (i=0; i < n; i++){
pol.m[i] = (pol.y[i+1]- pol.y[i]) / (pol.x[i+1]- pol.x[i]);
//printf("m_%i=%le\n",i,pol.m[i]);
}
pol.n = n;
fclose(f);
}else{
printf("Error en el archivo %s.\n",file);
}
printf(".");
return pol;
}
long double S(long double x1,long double y1,long double m,long double x){
return m*(x-x1)+y1; //m*x+(y1-m*x1); //m*(x-x1) + y1;
}
double f(lineal pol,double xa){
int n = pol.n;
int i;
long double x = (long double)xa;
if (x < pol.x[0]){
//printf("%le Es menor\n",x);
return (double)S(pol.x[0] ,pol.y[0], pol.m[0], x);
}
if (x >= pol.x[n-1]){
//printf("%le Es mayor\n",x);
return (double)S(pol.x[n-1] ,pol.y[n-1], pol.m[n-1], x);
}
for (i=0; i < n; i++){
if ( pol.x[i] <= x && x < pol.x[i+1]){
//printf("%le Esta en %i\n",x,i);
return (double)S(pol.x[i] ,pol.y[i], pol.m[i], x);
}
}
return 0.0;
}