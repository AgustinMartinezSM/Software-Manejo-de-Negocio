#ifndef ADL_H
#define ADL_H

#include "ARCHIVOS.h"//Incluimos la libreria que contiene las estructuras de registro y stProducto

#define dimension 7

//Estructuras

typedef struct nodoLista {
    stProducto producto;
    struct nodoLista* sig;
} nodoLista;

typedef struct {
    char categoria[30];
    nodoLista* productos;
} celda;

//Prototipados

int carga_desde_archivo(celda arregloDL[]);
int busca_pos_categoria(celda arregloDL[], char categoria[], int validos);
int agregar_categoria(celda arregloDL[], char categoria[], int validos);
int alta(celda arregloDL[], stRegistro registro, int validos);
void BorrarLista(nodoLista*lista);
void BorrarAdl(celda Adl[], int validos);
nodoLista* crear_nodo_lista(stRegistro producto);
nodoLista*Modificar(nodoLista*nodoModificar, int op);
nodoLista *ModificarProducto(nodoLista *datos, int op);
nodoLista *buscar_nodo_cod(nodoLista *lista, int codigo);
nodoLista* agregar_producto(nodoLista* lista, nodoLista* nuevoNodoLista);

#endif // ADL_H_INCLUDED
