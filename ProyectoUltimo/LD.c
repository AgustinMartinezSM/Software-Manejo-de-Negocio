#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LD.h"


nodoLisDob * inicListaDOB()
{
    return NULL;
}

nodoLisDob * crearNodoDOB(stProductoFilas dato)
{
    nodoLisDob* aux= (nodoLisDob *)malloc(sizeof(nodoLisDob));
    aux->dato=dato;
    aux->ante=NULL;
    aux->sig=NULL;
    return aux;
}

nodoLisDob * agregarAlPrincipioDOB(nodoLisDob * lista, nodoLisDob * nuevoNodo)
{
    nuevoNodo->sig=lista;
    if(lista!=NULL)
    {
        lista->ante=nuevoNodo;
    }
    return nuevoNodo;
}

// recursivo
nodoLisDob * buscarUltimoDOB(nodoLisDob * lista)
{
    nodoLisDob * rta=NULL;
    if(lista!=NULL)
    {
        if(lista->sig==NULL)
        {
            rta=lista;
        }
        else
        {
            rta=buscarUltimoDOB(lista->sig);
        }
    }
    return rta;
}

nodoLisDob * agregarAlFinalDOB(nodoLisDob * lista, nodoLisDob * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nodoLisDob * ultimo = buscarUltimoDOB(lista);
        ultimo->sig = nuevoNodo;
        nuevoNodo->ante = ultimo;
    }
    return lista;
}

stProductoFilas verPrimeroDOB(nodoLisDob * lista)
{
    stProductoFilas rta;

    if(lista)
        rta=lista->dato;

    return rta;

}

nodoLisDob * borrarPrimeroDOB (nodoLisDob * lista)
{
    nodoLisDob * aux = lista;;
    if (lista)
    {
        lista=lista->sig;
        if(lista)
            lista->ante=NULL;
        free(aux);
    }
    return lista;
}


void MostrarProdFilas(stProductoFilas dato)
{
    printf("||--------------------------------------------||\n");
    printf("||              LISTADO DE VENTA              ||\n");
    printf("||--------------------------------------------||\n");
    printf("||CODIGO:  %i                                 ||\n",dato.codigo);
    printf("||NOMBRE DEL PRODUCTO:  %s                    ||\n",dato.nombre);
    printf("||MARCA DEL PRODUCTO:  %s                     ||\n",dato.marca);
    printf("||PRECIO:  %.2f                               ||\n",dato.precio);
    printf("||--------------------------------------------||\n");
}

void mostrarNodoDOB(nodoLisDob * aux)
{
    MostrarProdFilas(aux->dato);
}

void recorrerYmostrarDOB(nodoLisDob * lista)
{
    nodoLisDob * seg = lista;
    while (seg != NULL)
    {
        mostrarNodoDOB(seg);
        seg= seg->sig;
    }
}


stProductoFilas CargarProdLD()
{
    stProductoFilas aux;
    stRegistro aux2;
    int codigo=0;
    int flag=0, pos=0;
    FILE * archiv=fopen(archivo,"r+b");
    if(archiv)
    {
        printf("||--------------------------------------------||\n");
        printf("||  INGRESE CODIGO DEL PRODUCTO:  \n");
        scanf("%i",&codigo);
        printf("||--------------------------------------------||\n");
        while(flag==0 && fread(&aux2,sizeof(stRegistro),1,archiv)>0 )
        {
            if(aux2.codigo==codigo && aux2.estado==1)
            {
                if(aux2.stock>0)
                {
                    aux.codigo=aux2.codigo;
                    aux.precio=aux2.precio;
                    strcpy(aux.marca,aux2.marca);
                    strcpy(aux.nombre,aux2.nombre);
                    aux2.stock--;
                    pos = ftell(archiv)/sizeof(stRegistro);
                    pos--;
                    flag=1;
                }
                else
                {
                    printf("=ERROR, el producto NO tiene stock=\n");
                    flag=1;
                }

            }
        }
        fclose(archiv);
        if(flag==1){
            SobreescribirRegistro(aux2,pos);
        }
        else
        {
            printf("=ERRO. No se encontro el producto=\n");
        }

    }
    else
    {
        printf("=ERROR. NO se pudo abrir el archivo=\n");
    }
    return aux;
}



