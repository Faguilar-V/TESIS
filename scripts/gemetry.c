#include <math.h>
#include <stdio.h>
double Alpha(double x,int n){
	return atan(2.0*Rt*x/(UA*((double)n-1.0)));
}
double Beta(double x, double y,int n){
return atan(2.0*Rt*y /
(sqrt(pow(2.0*Rt*x,2.0)+pow(((double)n-1.0)*UA,2.0))));
}
double R(double alpha, double beta, double z){
double C;
double C2;
double D;
double B;
double B2;
if (alpha == 0.0){ //bug NAN!! corregido
C = UA-z;
D = z;
}else{
C = (UA-z)/cos(alpha);
C2 = pow(UA,2.0) + (pow(C,2.0) - 2.0*UA*C*cos(alpha));
D = sqrt(C2);
}
B = C*tan(beta);
B2 = pow(B,2.0)+pow(D,2.0);
return sqrt(B2);
}
double Theta(double alpha,double beta, double z){
double C = (UA-z)/cos(alpha);
double D = sqrt(pow(UA,2.0) + pow(C,2.0) - 2.0*UA*C*cos(alpha));
if (z >= 0.0 && alpha==0)
return 0.0;
if (z < 0.0 && alpha==0)
return 3.141592654;
return acos((pow(UA,2.0)+pow(D,2.0)-pow(C,2.0))/(2.0*UA*D));
}
double Phi(double alpha, double beta, double z){
double C = (UA-z)/cos(alpha);
double B = C*tan(beta);
double E = sqrt(pow(B,2.0)+pow(C,2.0));
double D = sqrt(pow(UA,2.0) + pow(C,2.0) - 2.0*UA*C*cos(alpha));
double G = C + D;
double r = sqrt(pow(B,2.0)+pow(D,2.0));
if (B==0.0)
return 0.0;
else
return acos( (pow(G,2.0)+pow(r,2.0)-pow(E,2.0))/(2.0*G*r));
// return acos( D / sqrt(pow(B,2.0)-pow(D,2.0)));
}
double Z_A(double alpha, double beta){
double K1 = (pow(tan(beta),2.0)/pow(cos(alpha),2.0)) +
pow(tan(alpha),2.0);
double A1 = pow(2.0*K1*UA,2.0) -4.0*(K1+1.0)*
(K1*UA*UA - Rsun*Rsun);
double pre = 0.0;
if (A1 < 0.0){
printf("Error on %le %le\n",alpha,beta);
return -1.0;
}
pre = (2.0*K1*UA + sqrt(A1))/(2.0*(K1+1.0));
if (pre >= 0.0) return pre;
printf("Error on %le %le\n",alpha,beta);
return -1.0;
}
double Z_0(double alpha, double beta, double F){
double r = 0.0;
if (F >= 0.0){
r = R(alpha,beta,F);
if (r > Rsun) return F;
else
return Z_A(alpha,beta);
}else{
r = R(alpha,beta,0.0);
if (r > Rsun) return F;
else
return Z_A(alpha,beta);
}
}
double Dz(double alpha, double beta, double dl){
return cos(alpha)*cos(beta)*dl;
}
double toX(double r, double theta, double phi){
return r*cos(phi)*sin(theta);
}
double toY(double r, double theta, double phi){
return r*sin(phi);
}
double toZ(double r, double theta, double phi){
return r*cos(phi)*cos(theta);
}
punto calculaPunto(pixel p, double z){
punto x;
double r,theta,phi;
r = R(p.alpha, p.beta, z);
theta = Theta(p.alpha, p.beta, z);
phi = Phi(p.alpha, p.beta, z);
switch(p.cuadrante){
case 0:
printf("Error al definir cuadrante\n");
break;
case 2 :
theta = -theta;
break;
case 3:
theta = -theta;
phi = -phi;
break;
case 4:
phi = -phi;
break;
}
x.r=r;
x.theta=theta;
x.phi=phi;
x.z=z;
return x;
}