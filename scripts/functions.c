#include<math.h>
/* Calcula la frecuencia critica del medio
*/
double nu_0(double ne){
return (9e3)*sqrt(ne);
}
double Lambda(double t, double nu){
return log(ALPHA*pow(t,3.0)/pow(nu,2.0)) - 5.0*GAMMA;
}
/* The Opacity Function
*/
double k_nu(double T, double n_e, double HII, double HeII, double HeIII, double n
double n_i[] = {HII,HeII,HeIII};
double Z_i[] = {1.0,1.0,2.0};
double A=0.0;
int i ;
/*kundu
* double lambda= C_light/nu;
* double K_HI;
* double K_HII;
* double Kappa;
* double A1 = lambda*n_e;
*/
// DULK
for(i=0;i<3;i++){
A+=n_i[i]*Z_i[i]*Z_i[i];
}
if (T<=2.0e5){
return ((9.78e2)*n_e*A/(nu*nu*pow(T,1.5)))*(18.2+1.5*log(T)-log(nu));
}else{
return ((9.78e2)*n_e*A/(nu*nu*pow(T,1.5)))*(24.5+log(T)-log(nu));
}
//
// K_HI= (2.0e-23/pow(T,1.5))*pow(A1,2.0)*(10.6+1.9*log(T)-1.26
// *log(C_light/lambda));
// K_HII = (1.38e-35)*(HI/n_e)*pow(A1,2.0)*(35459.0-0.40192*T-(874692.0/T));
// Kappa = (K_HI+K_HII);
// return Kappa;
//
// Chiuderi
// return (1.0e5)*((2.0*1.56e-47)/sqrt(PI*K))*
// ((pow(C_light,2.0)/pow(nu,2.0))/(2.0*K))*
// (n_e*A / pow(T,1.5))*Lambda(T,nu);
}
double Tau(double k1, double k2, double dx){
return (dx/2.0)*(k1+k2);
}
double S_nu(double nu, double temperature){
double h_plank = 6.6260693e-27; //erg*s
return 2.0*K*pow(nu,2.0)*temperature/pow(C_light,2.0);
}