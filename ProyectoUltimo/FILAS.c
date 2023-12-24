#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FILAS.h"

void InicFilita(Fila * fila)
{
    fila->Inicio=inicListaDOB();
    fila->Fin=inicListaDOB();
}

void MostrarFIL(Fila * fila)
{
    printf("||--------------------------------------------||\n");
    printf("||                INICIO                      ||\n");
    printf("||--------------------------------------------||\n");
    recorrerYmostrarDOB(fila->Inicio);
    printf("||--------------------------------------------||\n");
    printf("||                 FIN                        ||\n");
    printf("||--------------------------------------------||\n");

}


void agregarFIL(Fila * fila,stProductoFilas dato)
{
    nodoLisDob * Nuevo=crearNodoDOB(dato);
    fila->Fin=agregarAlFinalDOB(fila->Fin,Nuevo);
    if(fila->Inicio==NULL)
    {
        fila->Inicio=fila->Fin;
    }
    fila->Fin=Nuevo;
}


stProductoFilas extraer(Fila * fila)
{
    stProductoFilas rta;
    if(fila->Inicio!=NULL)
    {
        rta=verPrimeroDOB(fila->Inicio);
        fila->Inicio=borrarPrimeroDOB(fila->Inicio);
        if(fila->Inicio==NULL)
        {
            fila->Fin=inicListaDOB();
        }
    }

    return rta;
}


void leerFIL(Fila * fila)
{
    stProductoFilas A;
    A=CargarProdLD();
    agregarFIL(fila,A);
}


int filaVacia(Fila * fila)
{
    int resp=0;
    if(fila->Inicio==NULL)
    {
        resp=1;
    }
    return resp;
}


void NuevaVenta(Fila * fila)
{
    int flag=1;
    float Total=0;
    while(flag==1)
    {
        leerFIL(fila);
        printf("||--------------------------------------------||\n");
        printf("||Ingrese 1 para CONTINUAR o 0 para SALIR     ||\n");
        printf("||--------------------------------------------||\n");
        scanf("%i",&flag);
    }
}



void FilaAlArchivo(Fila *fila,int Legajo,int dia)
{

    Ventas aux2;
    char Nombre[30];
    int flag=0;
    float Total=0;
    NombreDelArchi(Nombre,Legajo);
    FILE * archix2=fopen(archi3,"ab");
    if(archix2)
    {
        NuevaVenta(fila);
        MostrarFIL(fila);
        Total=sumarFila(fila);
        strcpy(aux2.NombreDelCajero,Nombre);
        aux2.Dia=dia;
        aux2.Legajo=Legajo;
        aux2.Ingresos=Total/0.3;
        fwrite(&aux2,sizeof(Ventas),1,archix2);

        fclose(archix2);
    }
}

float sumarFila(Fila *fila)
{
    float Total=0;
    stProductoFilas aux;
    while(!filaVacia(fila))
    {
        aux=extraer(fila);
        Total+=aux.precio;
    }
    return Total;
}


void NombreDelArchi(char Nombre[], int Legajo)
{
    int flag=0;
    empleado aux;
    FILE *archi1=fopen(archi2,"rb");
    if(archi1)
    {
        while(fread(&aux,sizeof(empleado),1,archi1)>0 && flag==0)
        {
            if(aux.Legajo==Legajo)
            {
                strcpy(Nombre,aux.NombreYape);
                flag=1;
            }
        }
        fclose(archi1);
    }
}

void LiberarMemoriaFila(Fila *fila)
{
    nodoLisDob *actual = fila->Inicio;
    nodoLisDob *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }

    fila->Inicio = fila->Fin = inicListaDOB();
}

