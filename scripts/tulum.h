#ifndef TULUM_H
#define TULUM_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "geometry.h"
#include "modelonumerico.h"
typedef struct{
int i;
int A;
int n;
}estado;
159
typedef struct{
int y;
int q;
}recomendacion;
typedef struct{
int epsilon;
microMalla posicion; //Nueva posicion
double I; //la emision total.
}resultados;
recomendacion experto(estadoFisico delPlasma, double min,double nu);
resultados tomarDecision(recomendacion delExperto, estado delAutomata,
estadoFisico delPlasma,microMalla posicion, double I);
estado automata(estado delAutomata, int epsilon);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
#endif