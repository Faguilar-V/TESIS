#include "functions.h"
#include "modelonumerico.h"
#include "lineal.h"
#include "geometry.h"
estadoFisico modeloFisico(lineal temperature, lineal Ne,
lineal NH, lineal NHI,
lineal NHII, lineal NHeI,
lineal NHeII, lineal NHeIII,
microMalla posicion,double nu){
estadoFisico plasma;
punto xa = posicion.xa;
punto xb = posicion.xb;
double H = f(NH, xb.r-Rsun);
double n_e = f(Ne, xb.r-Rsun);
double T = f(temperature, xb.r-Rsun);
double HI = H*f(NHI,T); //Total de Hidrogeno Neutro.
double HII = H*f(NHII,T);
double He = (0.1)*H;
double HeI = He*f(NHeI,T);
double HeII = He*f(NHeII,T);
double HeIII = He*f(NHeIII,T);
double Ta = f(temperature, xa.r-Rsun);
double n_ea = f(Ne, xa.r-Rsun);
double Ha = f(NH, xa.r-Rsun);
double Hea = (0.1)*Ha;
double HIIa = Ha*f(NHII,Ta);
double HeIIa = Hea*f(NHeII,Ta);
double HeIIIa = Hea*f(NHeIII,Ta);
double kappa_a;
plasma.perfil[0] = T;
plasma.perfil[1] = n_e;
plasma.perfil[2] = H;
plasma.perfil[3] = HI;
plasma.perfil[4] = HII;
plasma.perfil[5] = He;
plasma.perfil[6] = HeI;
plasma.perfil[7] = HeII;
plasma.perfil[8] = HeIII;
plasma.perfil[9] = HII+HeII+HeIII;
plasma.kappa = k_nu(T,n_e,HII,HeII,HeIII,nu);
kappa_a = k_nu(Ta,n_ea,HIIa,HeIIa,HeIIIa,nu);
if (posicion.step == 0 || posicion.step == 2) //paso peque~no
plasma.tau = Tau(plasma.kappa,kappa_a,posicion.pix.dlDETAIL);
else if (posicion.step == 1) //paso grande
plasma.tau = Tau(plasma.kappa,kappa_a,posicion.pix.dlBIG);
else
printf("Error al leer el paso de integracion (modelonumerico.c L62)\n");
plasma.Il = S_nu(nu,T)*(1.0 - exp(-plasma.tau));
plasma.n0 = nu_0(n_e);
return plasma;
}