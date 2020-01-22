#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "physics.h"
#include "lineal.h"
//Public Functions
double nu_0(double ne);
double k_nu(double T, double n_e, double HII,
double HeII, double HeIII, double nu);
double Tau(double k1, double k2, double dx);
double S_nu(double nu, double temperature);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
#endif /* FUNCTIONS_H */