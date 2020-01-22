#ifndef GEOMETRY_H
#define GEOMETRY_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <math.h>
#include "physics.h"
typedef struct{
double r;
double theta;
double phi;
double z;
}punto;
typedef struct{
double alpha;
double beta;
int cuadrante;
double dzBIG;
double dzDETAIL;
double dlBIG;
double dlDETAIL;
}pixel;
typedef struct{
pixel pix;
punto xa;
punto xb;
int step;
}microMalla;
//Le pasamos el punto del pixel y su posicion en z
punto calculaPunto(pixel p, double z);
double Alpha(double x,int n);
double Beta(double x, double y,int n);
double R(double alpha, double beta, double z);
double Theta(double alpha,double beta, double z);
double Phi(double alpha, double beta, double z);
double Z_A(double alpha, double beta);
double Z_0(double alpha, double beta, double F);
double Dz(double alpha, double beta, double dl);
double toX(double r, double theta, double phi);
double toY(double r, double theta, double phi);
double toZ(double r, double theta, double phi);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
#endif /* GEOMETRY_H */