#include "tulum.h"
recomendacion experto(estadoFisico delPlasma, double min, double nu){
recomendacion resp;
if (delPlasma.n0 > nu){// se refleja
//si
resp.y = 0;
resp.q = 0;
}else{
if (delPlasma.Il >= min){
resp.y = 0;
resp.q = 2;
}else{
resp.y = 1;
resp.q = 1;
}
}
return resp;
}
resultados tomarDecision(recomendacion delExperto,
estado delAutomata, estadoFisico delPlasma,
microMalla posicion, double I){
resultados resultado;
int y = delExperto.y;
int q = delExperto.q;
int A = delAutomata.A;
int epsilon = 3; //3 es no se que hacer.
double Il = delPlasma.Il;
double tau = delPlasma.tau;
punto xa = posicion.xa;
punto xb = posicion.xb;
pixel pix = posicion.pix;
double z; //variable dummy
int step;
resultado.posicion.pix = pix; //guardo los valores
//Primero ejecuto, luego cambio los estados!!!!
switch (A){
/*********************************
********* ESTADO A1 *************
********************************/
case 1:
switch (q){
case 0: //switch A=1, q=0
switch (y){ //1,0,0
case 0:
I=0.0; //Se reflejo
xa = xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=0;
step = 0;
break;
default: //1 0 X
epsilon = 3; //NO SE QUE HACER
break;
} //switch A=1, q=0, y
break;
case 1: //switch A=1, q=1 ,y
switch (y){
case 1: // 1, 1, 1
xa = xb;
z= xb.z + pix.dzBIG;
xb = calculaPunto(pix, z);
epsilon=1;
step = 1;
break;
default:
epsilon = 3; //NO SE QUE HACER
break;
} //switch A=1, q=1, y
break;
case 2: //switch A=1, q=2
switch (y){
case 0: // 1, 2, 0
I = I*exp(-tau) + Il;
xa = xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=0;
step = 0;
break;
default:
epsilon=3; //no se que hacer
break;
} //switch A=1, q=2, y
break;
default://switch A=1, q=X
epsilon=3; //no se que hacer
break; //switch A=1, q=X
}
break; //1
/*********************************
********* ESTADO A2 *************
********************************/
case 2:
switch (q){
case 0: //switch A=2, q=0
switch (y){
case 0: //2,0,0
I=0.0;
xa=xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=0;
step = 0;
break;
default:
epsilon=3;
break;
} //switch A=2, q=0, y
break;
case 1: //switch A=2, q=1
switch (y){
case 1: //2,1,1
xa=xb;
z= xb.z + pix.dzBIG;
xb = calculaPunto(pix, z);
epsilon=1;
step = 1;
break;
default:
epsilon=3;
break;
} //switch A=2, q=1, y
break;
case 2: //switch A=2, q=2
switch (y){
case 0: //2,2,0
z= xa.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=2;
step = 2; //aunque en realidad es hacia atras
break;
default:
epsilon=3;
break;
} //switch A=2, q=2, y
break;
default://switch A=2, q=X
epsilon=3;
break; //switch A=2, q=X
}
break; //2
/*********************************
********* ESTADO A3 *************
********************************/
case 3:
switch (q){
case 0: //switch A=3, q=0
switch (y){
case 0: //3 0 0
I=0.0;
xa=xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=0;
step=0;
break;
default:
epsilon=3;
break;
} //switch A=3, q=0, y
break;
case 1: //switch A=3, q=1
switch (y){
case 1: //3,1,1
I= I*exp(-tau) + Il;
xa=xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=1;
step=0;
break;
default:
epsilon=3;
break;
} //switch A=3, q=1, y
break;
case 2: //switch A=2, q=2
switch (y){
case 0: //3,2,0
I= I*exp(-tau) + Il;
xa=xb;
z= xb.z + pix.dzDETAIL;
xb = calculaPunto(pix, z);
epsilon=1;
step=0;
break;
default:
epsilon=3;
break;

} //switch A=3, q=2, y
break;
default://switch A=3, q=X
epsilon=3;
break; //switch A=3, q=X
}
break; //3
/*********************************
********* ESTADO A4 *************
********************************/
default:
printf("Error en tulum l203.\n");
epsilon=3;
break;
}
resultado.epsilon = epsilon;
resultado.I = I;
resultado.posicion.xa = xa;
resultado.posicion.xb = xb;
resultado.posicion.step = step;
return resultado;
}
estado automata(estado delAutomata, int epsilon){
int A = delAutomata.A;
int i = delAutomata.i;
int n = delAutomata.n;
estado nuevoEstado;
switch(A){
case 1:
switch(epsilon){
case 0: A = 1; break;
case 1: A = 2; break;
case 2: A = 4; break;
default: A = 4; break;
}
break;
case 2:
switch(epsilon){
case 0: A = 1; break;
case 1: A = 2; break;
case 2: A = 3; i=1; break;
default: A = 4; break;
}
break;
case 3:
if (epsilon == 0) A=1;
else if (epsilon == 1 && i < n){ A=3; i++;}
else if (epsilon == 1 && i == n){ A=1;}
else if (epsilon == 2){ A=4;}
else{ A=4;}
break;
case 4:
printf("Estado 4: E R R O R........\n");
break;
default:
printf("Estado > 4: E R R O R........\n");
break;
}
nuevoEstado.A = A;
nuevoEstado.i = i;
nuevoEstado.n = n;
return nuevoEstado;
}
166