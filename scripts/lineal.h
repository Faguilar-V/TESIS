#ifndef LINEAL_H
#define LINEAL_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
typedef struct{
int n; //Numero de splines generados
long double x[450];
long double y[450];
long double m[450];
}lineal;
lineal ilineal(char *file);
double f(lineal lin, double x);
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
#endif