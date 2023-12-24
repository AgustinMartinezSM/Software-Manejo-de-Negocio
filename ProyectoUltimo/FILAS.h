#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED


#include "ARCHIVOS.h"
#include "LD.h"

typedef struct
{
    nodoLisDob * Inicio;
    nodoLisDob * Fin;

} Fila;

void InicFilita(Fila * fila);
void MostrarFIL(Fila * fila);
void agregarFIL(Fila * fila,stProductoFilas dato);
stProductoFilas extraer(Fila * fila);
void leerFIL(Fila * fila);
int filaVacia(Fila * fila);
void NuevaVenta(Fila * fila);
void FilaAlArchivo(Fila *fila,int Legajo,int dia);
void NombreDelArchi(char Nombre[], int Legajo);
float sumarFila(Fila *fila);
void LiberarMemoriaFila(Fila *fila);



#endif // FILAS_H_INCLUDED
