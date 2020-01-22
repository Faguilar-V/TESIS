#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "lineal.h"
#include "functions.h"
#include "physics.h"
#include "geometry.h"
#include "help.h"
#include "modelonumerico.h"
#include "tulum.h"
#define VERSION "1.0"
void imprime(FILE *b, FILE *c,resultados resultado,
microMalla posicion,
estadoFisico estadofisico){
//Imprimiendo los perfiles.
fprintf(c,"%le %le %le %le %le %le %le %le %le %le\n",
posicion.xb.z,
posicion.xb.r-Rsun,
estadofisico.perfil[0], //temperatura
estadofisico.perfil[1], //n_e
estadofisico.perfil[2], //H total
estadofisico.perfil[3], //HI
estadofisico.perfil[4], //HII
estadofisico.perfil[6], //HeI
estadofisico.perfil[7], //HeII
estadofisico.perfil[8]); //HeIII
//Imprimiendo la emision
fprintf(b,"%le %le %le %le %le %le\n",
	posicion.xb.z,
posicion.xb.r-Rsun,
estadofisico.kappa,
estadofisico.tau,
estadofisico.Il,
resultado.I);
}
int main(int argc, char **argv){
double porcentaje;
int pori;
int edoA,iA;
int line=0;
int isline=0;
int verbose = 0;
int puntoenx = 0;
int puntoeny = 0;
int solounpunto = 0;
int xini,xfin,yini,yfin;
int x,y,m;
int parai=0;
double z,z_0,dzDetail;
double alpha,beta,dz,dzBig;
int n = 5; //ok
double min = 1e-25;
double detail = 0.5;
double F = -2.0*Rsun; //OK
double H = 2.0*Rsun; //OK
double dl = 20.0; //km
double deltaTau = dl;
double nu = 43e9; //OK Hz
double wl = 0.0; //OK
double r,theta,phi,I,rt,n0,tau,mt;
int epsilon;
double localintensity;
double t_temp;
int cuadrante=0;
char outputfile[100];
char outputfileverbose[100];
char temperaturefile[100];
char densityfile[100];
char hydrogenfile[100];
char comando[200];
har perfilesOut[100];
char emisionOut[100];
lineal temperature;
lineal density;
lineal hydrogen;
lineal HI;
lineal HII;
lineal HeI;
lineal HeII;
lineal HeIII;
FILE *fout;
FILE *foute;
FILE *foutp;
int i,j;
int surface = 0; //no estoy en la superficie
pixel pix;
microMalla posicion;
punto xa,xb;
resultados resultado;
estadoFisico estadofisico;
recomendacion recomendaciones;
estado Automata;
int nStep = 100;
sprintf(outputfile,"sun.dat");
sprintf(temperaturefile,"data/temperature.dat");
sprintf(densityfile,"data/electronic.dat");
sprintf(hydrogenfile,"data/hydrogen.dat");
sprintf(outputfileverbose,"verbose_sun.dat");
sprintf(perfilesOut,"perfiles.dat");
sprintf(emisionOut,"emision.dat");
/******************Get Parameters********************/
printf("Pakal ");
printf(VERSION);
printf(" GNU/GPL license\n");
for (i=1; i<argc;i++){
sprintf(comando,"%s",argv[i]);
if (strcmp(comando,"-v") == 0){
verbose = 1;
}
if (strcmp(comando,"-xy") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%i\n",&puntoenx) > 0){
printf(".");
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%i\n",&puntoeny) > 0){
printf(".");
solounpunto=1;
}else{
imprimeInstrucciones();
return 0;
}
}else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-detail") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%le\n",&detail) > 0){
printf(".");
}else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-min") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%lf\n",&min) > 0){
printf(".");
}else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-l") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%i\n",&line) > 0){
isline=1;
printf(".");
}else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-help") == 0){
imprimeAyuda();
return 0;
}
if (strcmp(comando,"-wl") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%lf\n",&wl) > 0)
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-nu") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%lf\n",&nu) > 0)
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-h") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%lf\n",&H) > 0)
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-f") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%lf\n",&F) > 0)
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-big") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%i\n",&nStep) > 0)
printf(".");
else{
	imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-r") == 0){
sprintf(comando,"%s",argv[++i]);
if (sscanf(comando,"%i\n",&n) > 0)
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-o") == 0){
if (sprintf(outputfile,"%s",argv[++i])){
printf(".");
sprintf(outputfileverbose,"verbose_%s",outputfile);
}else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-t") == 0){
if (sprintf(temperaturefile,"%s",argv[++i]))
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-d") == 0){
if (sprintf(densityfile,"%s",argv[++i]))
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
if (strcmp(comando,"-H") == 0){
if (sprintf(hydrogenfile,"%s",argv[++i]))
printf(".");
else{
imprimeInstrucciones();
return 0;
}
}
}
dl=((double)nStep)*detail;
printf("\nValues : \n");
if ( (n % 2) == 0) n++;
if (wl != 0.0)
printf("Wavelength %lf\n",wl);
else
printf("Frecuency %lf\n",nu);
printf("Height %lf\n",H/Rsun);
printf("Floor %lf\n",F/Rsun);
printf("Int. step %lf\n",dl);
printf("Detail %le\n",detail);
printf("Resolution %ix%i\n",n,n);
printf("Minimal LI %le\n",min);
printf("(OUT) File Image %s\n",outputfile);
printf("(IN) Temperature file %s\n",temperaturefile);
printf("(IN) Electronic Density file %s\n",densityfile);
printf("(IN) Hydrogen Density file %s\n",hydrogenfile);
/********************* (END)Get Parameters*******************/
/******************** OUTPUTS FILES *************************/
fout = fopen(outputfile, "w+");
temperature = ilineal(temperaturefile);
density = ilineal(densityfile);
hydrogen = ilineal(hydrogenfile);
HI = ilineal("data/HI.dat");
HII = ilineal("data/HII.dat");
HeI = ilineal("data/HeI.dat");
HeII = ilineal("data/HeII.dat");
HeIII = ilineal("data/HeIII.dat");
if (verbose==1){
foutp = fopen(perfilesOut, "w+");
foute = fopen(emisionOut, "w+");
}
/**************** (END) OUTPUTS FILES *********************/
if (solounpunto==1){ //Vamos a integrar un punto
printf("Single Point (%i, %i)\n",puntoenx,puntoeny);
xini = xfin = puntoenx;
yini = yfin =puntoeny;
}else if (isline==1){ // Vamos a integrar una linea
yini= 0;
yfin = (n-1)/2;
xini = xfin =line;
printf("Image Line (%i,%i:%i)\n",line,yini,yfin);
}else{ //vamos a integrar toda la imagen
xini= -(n-1)/2;
xfin = (n-1)/2;
yini=-(n-1)/2;
yfin=(n-1)/2;
}
/********************************************* **
********************************************* ***
*********** COMIENZA LA INTEGRACION ******** ***
********************************************* ***********
********************************************* *******
********************************************* ***
********************************************* *
*/
for (x = xini; x <= xfin;x++ ){
alpha = Alpha((double)x, n); //ok
for (y= yini; y <= yfin;y++ ){
beta = Beta((double)x,(double)y,n); //ok
cuadrante = 0;
if (alpha >= 0.0 && beta >= 0.0) cuadrante=1;
if (alpha <= 0.0 && beta >= 0.0) cuadrante=2;
if (alpha <= 0.0 && beta <= 0.0) cuadrante=3;
if (alpha >= 0.0 && beta <= 0.0) cuadrante=4;
z_0 = Z_0(alpha,beta,F);
dzBig = Dz(alpha,beta,dl);
dzDetail = Dz(alpha,beta,detail);
pix.alpha=alpha;
pix.beta = beta;
pix.cuadrante = cuadrante;
pix.dzBIG = dzBig;
pix.dzDETAIL = dzDetail;
pix.dlBIG = dl;
pix.dlDETAIL = detail;
z=z_0;
xa = calculaPunto(pix,z);
n0 = nu_0(f(density,xa.r-Rsun));
if (z_0 > F){
	//Si estoy en la superficie
if (n0 <= nu){ //Se refleja?
//NO
//La radiacion de fondo es el de un cuerpo negro normal.
I = S_nu(nu,f(temperature,rt-Rsun));
}else{
//SI
I=0.0; //se reflejo
}
}else{
I=0; //no hay radiacion de fondo.
}
z += pix.dzDETAIL;
xb = calculaPunto(pix,z);
posicion.pix = pix;
posicion.xa = xa;
posicion.xb = xb;
posicion.step= 0;
Automata.i = 0;
Automata.A = 1;
Automata.n = nStep;
recomendaciones.y=0;
recomendaciones.q=0;
/***********************
*** LINEA DE VISION ***
*********INICIA********/
j=0;
while (z <= H){
estadofisico= modeloFisico(temperature,density,hydrogen,
HI, HII, HeI, HeII, HeIII,
posicion, nu);
recomendaciones = experto(estadofisico, min,nu);
resultado = tomarDecision(recomendaciones, Automata,
estadofisico,posicion,I);
if (verbose)
imprime(foute,foutp,resultado,posicion,estadofisico);
epsilon = resultado.epsilon;
edoA=Automata.A;
iA =Automata.i;
Automata = automata(Automata, epsilon);
I = resultado.I;
porcentaje=100.0*(1.0-((H-z)/(H-z_0)));
j++;
if (j==10000 ){
j=0;
printf("A%i,%i,i=%i -> ",edoA, epsilon, iA);
printf("A%i,i=%i %lf %le %le %lf\n",
Automata.A,
Automata.i,
porcentaje,
z,
estadofisico.Il,
C_light*C_light*I/(2.0*K*nu*nu));
}
posicion = resultado.posicion;
z = posicion.xb.z;
}
/**********TERMINA******
*** LINEA DE VISION ***
***********************/
printf("%i %i %le %lf\n",x,y,I,
C_light*C_light*I/(2.0*K*nu*nu));
fprintf(fout,"%i %i %le\n",x,y,I);
fflush(fout);
}
}
fclose(fout);
if (verbose==1){
fclose(foute);
fclose(foutp);
}
return 0;
}