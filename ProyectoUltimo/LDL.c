#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDL.h"


nodoLis1 * InicListaLDL1()
{
    return NULL;
}


nodoLis2 * InicListaLDL2()
{
    return NULL;
}


nodoLis2 * BuscarAlFinal(nodoLis2 * Lista)
{
    nodoLis2 * seg=Lista;
    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }
    return seg;
}


nodoLis2 * CrearNodo2(Ventas2 dato)
{
    nodoLis2 * Nuevo=(nodoLis2*)malloc(sizeof(nodoLis2));
    Nuevo->dato=dato;
    Nuevo->sig=NULL;
    return Nuevo;
}

nodoLis1 * CrearNodo1(char NombreCaj[],int Legajo)
{
    nodoLis1 * Nuevo=(nodoLis1*)malloc(sizeof(nodoLis1));
    strcpy(Nuevo->NombreDelCajero,NombreCaj);
    Nuevo->Legajo=Legajo;
    Nuevo->ListadeVentas= NULL;
    Nuevo->sig=NULL;
    return Nuevo;
}


nodoLis2* AgregarAlFinal(nodoLis2 * Lista, Ventas2 dato)
{
    if(Lista==NULL)
    {
        Lista=CrearNodo2(dato);
    }
    else
    {
        nodoLis2 * Ultimo=BuscarAlFinal(Lista);
        Ultimo->sig=CrearNodo2(dato);
        Lista=Ultimo;
    }
    return Lista;
}

nodoLis1 * agregarAlPpioLIS1(nodoLis1 * Lista,nodoLis1 * Nuevo)
{

    if(Lista==NULL)
    {
        Lista=Nuevo;
    }
    else
    {
        Nuevo->sig=Lista;
        Lista=Nuevo;
    }
    return Lista;
}


nodoLis1*BuscarNodoLis1(nodoLis1*lista,int Legajo)
{
    nodoLis1*rta=NULL;
    nodoLis1* seg= lista;

    int flag=0;

    while(seg != NULL && flag == 0)
    {
        if(seg->Legajo==Legajo)
        {
            rta=seg;
            flag=1;
        }
        seg=seg->sig;
    }
    return rta;
}



nodoLis1 * AltaLis(nodoLis1 * Lista, char Nombre[],int Legajo, int Dia, float Total)
{
    Ventas2 dato;
    dato.dia=Dia;
    dato.Total=Total;
    nodoLis1 * Buscado=BuscarNodoLis1(Lista,Legajo);

    if(Buscado==NULL)
    {
        nodoLis1 * NuevoLeg=CrearNodo1(Nombre,Legajo);
        Lista=agregarAlPpioLIS1(Lista,NuevoLeg);
        Buscado=Lista;
    }
    Buscado->ListadeVentas=AgregarAlFinal(Buscado->ListadeVentas,dato);
    return Lista;
}


nodoLis1 * ArchivoToLDL(nodoLis1 * Lista)
{
    FILE * archi=fopen(archi3,"rb");
    Ventas aux;
    if(archi)
    {
        while(fread(&aux,sizeof(Ventas),1,archi)>0)
        {
            Lista=AltaLis(Lista,aux.NombreDelCajero,aux.Legajo,aux.Dia,aux.Ingresos);
        }
        fclose(archi);
    }
    return Lista;
}


void MostrarVentasUNempleado(nodoLis1 * Lista, int Legajo)
{
    nodoLis1*Buscado=BuscarNodoLis1(Lista,Legajo);
    if(Buscado==NULL)
    {
        printf("=ERROR. No se encontro el empleado=\n");
    }
    else
    {
        printf("||--------------------------------------------||\n");
        printf("||---------      VENTA EMPLEADO:      --------||\n");
        printf("||--------------------------------------------||\n");
        printf("|| LEGAJO:  %i                                ||\n",Buscado->Legajo);
        printf("||--------------------------------------------||\n");
        printf("|| NOMBRE DEL EMPLEADO:  %s                   ||\n",Buscado->NombreDelCajero);
        printf("||--------------------------------------------||\n");
        nodoLis2 * seg=Buscado->ListadeVentas;
        while(seg!=NULL)
        {
            printf("||--------------------------------------------||\n");
            printf("|| TOTAL DE INGRESOS:  %.2f                   ||\n",seg->dato.Total);
            printf("|| DIA:  %i                                   ||\n",seg->dato.dia);
            printf("||--------------------------------------------||\n");
            seg=seg->sig;
        }
    }
}


void MostrarTodosLosEmpleadosVentas(nodoLis1 * Lista)
{
    nodoLis1 * seg1=Lista;
        printf("||--------------------------------------------||\n");
        printf("||        EMPLEADOS TOTALES REGISTRADOS:      ||\n");
        printf("||--------------------------------------------||\n");
    while(seg1!=NULL)
    {
        printf("||--------------------------------------------||\n");
        printf("|| LEGAJO:  %i                                ||\n",seg1->Legajo);
        printf("||--------------------------------------------||\n");
        printf("|| NOMBRE DEL EMPLEADO:  %s                   ||\n",seg1->NombreDelCajero);
        printf("||--------------------------------------------||\n");
        nodoLis2 * seg2=seg1->ListadeVentas;
        while(seg2!=NULL)
        {
            printf("||--------------------------------------------||\n");
            printf("|| TOTAL DE INGRESOS:  %.2f                   ||\n",seg2->dato.Total);
            printf("|| DIA:  %i                                   ||\n",seg2->dato.dia);
            printf("||--------------------------------------------||\n");
            printf("||--------------------------------------------||\n\n");
            seg2=seg2->sig;
        }
        seg1=seg1->sig;
    }
}

void LiberarMemoria(nodoLis1 * Lista)
{
    nodoLis1 *actual1 = Lista;
    nodoLis1 *siguiente1;

    while (actual1 != NULL)
    {
        nodoLis2 *actual2 = actual1->ListadeVentas;
        nodoLis2 *siguiente2;

        while (actual2 != NULL)
        {
            siguiente2 = actual2->sig;
            free(actual2);
            actual2 = siguiente2;
        }

        siguiente1 = actual1->sig;
        free(actual1);
        actual1 = siguiente1;
    }
}

