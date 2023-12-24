#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADL.h"


nodoLista* crear_nodo_lista(stRegistro producto)
{
    nodoLista* aux = (nodoLista*) malloc(sizeof(nodoLista));

    strcpy(aux->producto.marca, producto.marca);
    strcpy(aux->producto.nombre, producto.nombre);
    aux->producto.codigo = producto.codigo;
    aux->producto.precio = producto.precio;
    aux->producto.stock = producto.stock;
    aux->producto.estado = producto.estado;
    aux->sig = NULL;

    return aux;
}

int busca_pos_categoria(celda arregloDL[], char categoria[], int validos)
{
    int i = 0;
    int respuesta = -1;

    while ((i < validos) && (respuesta == -1))
    {
        if (strcmp(arregloDL[i].categoria, categoria) == 0)
        {
            respuesta = i;
        }
        i++;
    }

    return respuesta;
}


int agregar_categoria(celda arregloDL[], char categoria[], int validos)
{
    strcpy(arregloDL[validos].categoria, categoria);

    arregloDL[validos].productos = NULL;

    validos++;

    return validos;
}

nodoLista* agregar_producto(nodoLista* lista, nodoLista* nuevoNodoLista)
{
    if (lista != NULL)
    {
        nuevoNodoLista->sig = lista;
    }

    lista = nuevoNodoLista;

    return lista;
}

int alta(celda arregloDL[], stRegistro registro, int validos)
{
    nodoLista* aux = crear_nodo_lista(registro);

    int pos = busca_pos_categoria(arregloDL, registro.categoria, validos);
    if (pos == -1)
    {
        validos = agregar_categoria(arregloDL, registro.categoria, validos);
        pos = validos - 1;
    }

    arregloDL[pos].productos = agregar_producto(arregloDL[pos].productos, aux);

    return validos;
}


int carga_desde_archivo(celda arregloDL[])
{
    FILE* buff = fopen(archivo, "rb");
    stRegistro registro;

    int validos = 0;

    if (buff != NULL)
    {
        while (fread(&registro, sizeof(stRegistro), 1, buff) > 0 && validos < dimension)
        {
            if(registro.estado == 1)
            {
                validos = alta(arregloDL, registro, validos);
            }
        }
        fclose(buff);
    }
    else
    {
        printf("=Error al abrir el archivo=\n");
    }

    return validos;
}

nodoLista*Modificar(nodoLista*nodoModificar, int op)
{
    if (nodoModificar != NULL)
    {
        nodoModificar = ModificarProducto(nodoModificar, op);

        ModificarRegistro(nodoModificar->producto);//Lo modificamos en el archivo
    }

    return nodoModificar;
}

nodoLista*ModificarProducto(nodoLista *datos, int op)
{
    if (op == 1)
    {
        printf("||--------------------------------------------||\n");
        printf("||  Ingresar nuevo Nombre:  ");
        fflush(stdin);
        gets(datos->producto.nombre);
        printf("||--------------------------------------------||\n");
    }
    else if (op == 2)
    {
        printf("||--------------------------------------------||\n");
        printf("||  Ingresar nuevo Nombre de Marca:  ");
        fflush(stdin);
        gets(datos->producto.marca);
        printf("||--------------------------------------------||\n");
    }
    else if (op == 3)
    {
        printf("||--------------------------------------------||\n");
        printf("||  Ingresar nuevo Precio:  ");
        scanf(" %f", &datos->producto.precio);
        printf("||--------------------------------------------||\n");
    }
    else if (op == 4)
    {
        printf("||--------------------------------------------||\n");
        printf("||  Ingresar nuevo Stock:  ");
        scanf(" %d", &datos->producto.stock);
        printf("||--------------------------------------------||\n");
    }
    else if (op == 5)
    {
        printf("||--------------------------------------------||\n");
        datos->producto.estado = !datos->producto.estado;
        printf("||      ==ESTADO MODIFICADO A INACTIVO==      ||\n");
        printf("||--------------------------------------------||\n");
    }
    else
    {
        printf("=ERROR=");
    }

    return datos;
}

nodoLista *buscar_nodo_cod(nodoLista *lista, int codigo)
{
    while (lista != NULL)
    {
        if (lista->producto.codigo == codigo)
        {
            return lista;
        }
        lista = lista->sig;
    }
    return lista;
}

void BorrarAdl(celda Adl[], int validos)
{
    for(int i=0; i<validos ;i++)
    {
        BorrarLista(Adl[i].productos);
    }
}

void BorrarLista(nodoLista*lista)
{
    if(lista != NULL)
    {
        BorrarLista(lista->sig);
        free(lista);
    }
}
