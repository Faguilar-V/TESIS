#ifndef MODELONUMERICO_H
#define MODELONUMERICO_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "functions.h"
#include "geometry.h"
typedef struct{
double perfil[10]; //T, ne, h, hi, hii,he, hei, heii, heiii,n_i
double Il; //Emision local en xb
double tau; //tau_xb - tau_xa
double kappa; //kappa_xb
double n0; //Frecuencia critica en xb
}estadoFisico;
estadoFisico modeloFisico(lineal T , lineal Ne , lineal NH , lineal NHI,
lineal NHII, lineal NHeI, lineal NHeII,
lineal NHeIII, microMalla posicion,double nu);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
#endif