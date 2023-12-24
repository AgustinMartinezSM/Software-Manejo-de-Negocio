#ifndef LDA_H_INCLUDED
#define LDA_H_INCLUDED

#include "ARCHIVOS.h"

//Estructuras

typedef struct{
    char categoria[30];
    struct nodoArbol*subArbol;
    struct nodoLDA*sig;
}nodoLDA;

typedef struct{
    stProducto dato;
    struct nodoArbol*der;
    struct nodoArbol*izq;
}nodoArbol;

typedef struct
{
    stRegistro datos;
    struct arbolito*der;
    struct arbolito*izq;
} arbolito;

//Prototipados

nodoLDA*lda(nodoLDA*lista, int op );
nodoLDA*buscarCategoria(nodoLDA*lista,char buscado[]);
nodoLDA*crearNodoLista(stRegistro a);
nodoArbol*crearNodoArbol(stRegistro a);
nodoLDA*agregarPpio(nodoLDA*lista,stRegistro a);
nodoLDA*Alta(nodoLDA*lista,stRegistro a, int op);
nodoLDA*InicLista();
nodoArbol*insertarNombre(nodoArbol*arbol,stRegistro a);
nodoArbol*insertarCodigo(nodoArbol*arbol,stRegistro a);
nodoArbol*insertarStock(nodoArbol*arbol,stRegistro a);
nodoArbol*insertarPrecio(nodoArbol*arbol,stRegistro a);
nodoArbol*BuscarPorCodigo(nodoArbol*arbol, int codigo);
nodoArbol*BuscarPorNombre(nodoArbol*arbol, char nombre[]);
void mostrarNodoArbol( nodoArbol* arbol);
void mostrarListaArboles( nodoLDA* listaArboles, char cat[]);
void BorrarListaArboles(nodoLDA*lista);
void BorrarArbol(nodoArbol*arbol);


#endif // LDA_H_INCLUDED
