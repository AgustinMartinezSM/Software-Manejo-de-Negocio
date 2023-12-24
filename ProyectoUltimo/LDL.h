#ifndef LDL_H_INCLUDED
#define LDL_H_INCLUDED
#include "ARCHIVOS.h"


typedef struct
{
    float Total;
    int dia;
} Ventas2;

typedef struct
{
    Ventas2 dato;
    struct nodoLis2 * sig;
} nodoLis2;

typedef struct
{
    int Legajo;
    char NombreDelCajero[30];
    struct nodoLis2 * ListadeVentas;
    struct nodoLis1 * sig;
} nodoLis1;

nodoLis1 * InicListaLDL1();
nodoLis2 * InicListaLDL2();
nodoLis2 * BuscarAlFinal(nodoLis2 * Lista);
nodoLis2 * CrearNodo2(Ventas2 dato);
nodoLis1 * CrearNodo1(char NombreCaj[],int Legajo);
nodoLis2* AgregarAlFinal(nodoLis2 * Lista, Ventas2 dato);
nodoLis1 * agregarAlPpioLIS1(nodoLis1 * Lista,nodoLis1 * Nuevo);
nodoLis1*BuscarNodoLis1(nodoLis1*lista,int Legajo);
nodoLis1 * AltaLis(nodoLis1 * Lista, char Nombre[],int Legajo, int Dia, float Total);
nodoLis1 * ArchivoToLDL(nodoLis1 * Lista);
void MostrarVentasUNempleado(nodoLis1 * Lista, int Legajo);
void MostrarTodosLosEmpleadosVentas(nodoLis1 * Lista);
void LiberarMemoria(nodoLis1 * Lista);





#endif // LDL_H_INCLUDED
