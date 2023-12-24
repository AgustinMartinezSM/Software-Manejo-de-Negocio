#ifndef LD_H_INCLUDED
#define LD_H_INCLUDED
#include "ARCHIVOS.h"
#include "LISTAS.h"


typedef struct nodoLisDob
{
    stProductoFilas dato;
    struct nodoLisDob * sig;
    struct nodoLisDob * ante;

} nodoLisDob;

nodoLisDob * inicListaDOB();
nodoLisDob * crearNodoDOB(stProductoFilas dato);
nodoLisDob * agregarAlPrincipioDOB(nodoLisDob * lista, nodoLisDob * nuevoNodo);
nodoLisDob * buscarUltimoDOB(nodoLisDob * lista);
nodoLisDob * agregarAlFinalDOB(nodoLisDob * lista, nodoLisDob * nuevoNodo);
void MostrarProdFilas(stProductoFilas dato);
stProductoFilas verPrimeroDOB (nodoLisDob * lista);
nodoLisDob * borrarPrimeroDOB (nodoLisDob * lista);
void mostrarNodoDOB(nodoLisDob * aux);
void recorrerYmostrarDOB(nodoLisDob * lista);
stProductoFilas CargarProdLD();






#endif // LD_H_INCLUDED
