#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDA.h"

nodoLDA*lda(nodoLDA*lista, int op)
{
    stRegistro a;
    FILE*buff=fopen(archivo,"rb");

    if(buff!=NULL)
    {
        while(fread(&a,sizeof(stRegistro),1,buff)>0)
        {
            if(a.estado == 1)
            {
                lista=Alta(lista,a,op);
            }
        }
        fclose(buff);
    }
    else
    {
        puts("=ERROR=");
    }

    return lista;
}

nodoLDA*buscarCategoria(nodoLDA*lista,char buscado[])
{
    nodoLDA*rta=NULL;
    int flag=0;

    while(lista != NULL && flag == 0)
    {
        if(strcmp(lista->categoria,buscado)==0)
        {
            rta=lista;
            flag=1;
        }
        lista=lista->sig;
    }
    return rta;
}

nodoLDA*crearNodoLista(stRegistro a)
{
    nodoLDA*aux=(nodoLDA*)malloc(sizeof(nodoLDA));
    strcpy(aux->categoria,a.categoria);
    aux->sig=NULL;
    aux->subArbol=NULL;

    return aux;
}

nodoArbol*crearNodoArbol(stRegistro a)
{
    nodoArbol*aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    aux->der=NULL;
    aux->izq=NULL;
    aux->dato.codigo=a.codigo;
    strcpy(aux->dato.marca,a.marca);
    strcpy(aux->dato.nombre,a.nombre);
    aux->dato.precio=a.precio;
    aux->dato.stock=a.stock;
    aux->dato.estado=a.estado;

    return aux;
}

nodoLDA*agregarPpio(nodoLDA*lista,stRegistro a)
{
    if(lista==NULL)
    {
        lista=crearNodoLista(a);
    }
    else
    {
        nodoLDA*nuevo=crearNodoLista(a);
        nuevo->sig=lista;
        lista=nuevo;
    }

    return lista;
}

nodoLDA*Alta(nodoLDA*lista, stRegistro a, int op)
{
    nodoLDA*buscado=buscarCategoria(lista,a.categoria);
    if(buscado==NULL)
    {
        lista=agregarPpio(lista,a);
        buscado=lista;
    }
    if(op == 1)//Opciones para ver de que forma vamos a cargar la LDA dependiendo el uso
    {
        buscado->subArbol=insertarNombre(buscado->subArbol,a);
    }
    else if(op == 2)
    {
        buscado->subArbol=insertarCodigo(buscado->subArbol,a);
    }
    else if(op == 3)
    {
        buscado->subArbol=insertarStock(buscado->subArbol,a);
    }
    else
    {
        buscado->subArbol=insertarPrecio(buscado->subArbol,a);
    }

    return lista;
}

nodoLDA*InicLista()
{
    return NULL;
}

nodoArbol*insertarNombre(nodoArbol*arbol,stRegistro a)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(a);
    }
    else
    {
        if((strcmp(a.nombre,arbol->dato.nombre)>0) || (strcmp(a.nombre,arbol->dato.nombre)==0))
        {
            arbol->der=insertarNombre(arbol->der,a);
        }
        else
        {
            arbol->izq=insertarNombre(arbol->izq,a);
        }
    }
    return arbol;
}


nodoArbol*insertarCodigo(nodoArbol*arbol,stRegistro a)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(a);
    }
    else
    {
        if(arbol->dato.codigo<a.codigo)
        {
            arbol->der=insertarCodigo(arbol->der,a);
        }
        else
        {
            arbol->izq=insertarCodigo(arbol->izq,a);
        }
    }
    return arbol;
}

nodoArbol*insertarStock(nodoArbol*arbol,stRegistro a)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(a);
    }
    else
    {
        if(arbol->dato.stock <= a.stock)
        {
            arbol->der=insertarStock(arbol->der,a);
        }
        else
        {
            arbol->izq=insertarStock(arbol->izq,a);
        }
    }
    return arbol;
}

nodoArbol*insertarPrecio(nodoArbol*arbol,stRegistro a)
{
    if(arbol==NULL)
    {
        arbol=crearNodoArbol(a);
    }
    else
    {
        if(arbol->dato.precio<a.precio)
        {
            arbol->der=insertarPrecio(arbol->der,a);
        }
        else
        {
            arbol->izq=insertarPrecio(arbol->izq,a);
        }
    }
    return arbol;
}

nodoArbol*BuscarPorCodigo(nodoArbol*arbol, int codigo)
{
    nodoArbol*encontrado = NULL;

    if(arbol == NULL)
    {
        return encontrado;
    }
    else
    {
        if(arbol->dato.codigo == codigo)
        {
            return arbol;
        }
        else
        {
            if(codigo >= arbol->dato.codigo)
            {
                encontrado = BuscarPorCodigo(arbol->der,codigo);
            }
            else
            {
                encontrado = BuscarPorCodigo(arbol->izq,codigo);
            }
        }
    }

    return encontrado;
}

nodoArbol*BuscarPorNombre(nodoArbol*arbol, char nombre[])
{
    nodoArbol*encontrado = NULL;

    if(arbol == NULL)
    {
        return encontrado;
    }
    else
    {
        if(strcmp(nombre, arbol->dato.nombre) == 0)
        {
            return arbol;
        }
        else
        {
            if(strcmp(nombre, arbol->dato.nombre) > 0)
            {
                encontrado = BuscarPorNombre(arbol->der,nombre);
            }
            else
            {
                encontrado = BuscarPorNombre(arbol->izq,nombre);
            }
        }
    }

    return encontrado;
}

void mostrarProducto(stProducto prod)
{
    printf("||--------------------------------------------||\n");
    printf("||        INFORMACION DEL PRODUCTO:           ||\n");
    printf("||--------------------------------------------||\n");
    printf("|| CODIGO: %d                                 ||\n", prod.codigo);
    printf("|| NOMBRE: %s                                 ||\n", prod.nombre);
    printf("|| MARCA: %s                                  ||\n", prod.marca);
    printf("|| PRECIO: %.2f                               ||\n", prod.precio);
    printf("|| STOCK: %d                                  ||\n", prod.stock);
    printf("|| ESTADO: ");

    if(prod.estado != 1)
    {
        printf("||--------------------------------------------||\n");
        printf("  INACTIVO                                    ||\n");
        printf("||--------------------------------------------||\n");
    }
    else
    {
        printf("||--------------------------------------------||\n");
        printf("||  ACTIVO                                    ||\n");
        printf("||--------------------------------------------||\n");
    }
    printf("||--------------------------------------------||\n");
}

// Función para mostrar datos de un nodo de árbol
void mostrarNodoArbol( nodoArbol* arbol)
{
    if(arbol != NULL)
    {
        mostrarNodoArbol(arbol->izq);
        mostrarProducto(arbol->dato);
        mostrarNodoArbol(arbol->der);
    }

    // También podrías mostrar datos adicionales del árbol si los tienes
}

// Función para mostrar una lista de árboles
void mostrarListaArboles( nodoLDA* listaArboles, char cat[])
{

    while (listaArboles != NULL && strcmp(listaArboles->categoria,cat) != 0)
    {


        listaArboles = listaArboles->sig;
    }
    if(listaArboles != NULL)
    {
        printf("||---------------------||\n");
        printf("||\n  CATEGORIA: | %s |||\n", listaArboles->categoria);
        printf("||---------------------||\n");

        // Mostrar todos los nodos del árbol asociado a esta categoría
        mostrarNodoArbol(listaArboles->subArbol);
    }
}

void BorrarListaArboles(nodoLDA*lista)
{
    if(lista==NULL)
    {
        return;
    }
    else
    {
        BorrarListaArboles(lista->sig);
        BorrarArbol(lista->subArbol);
        free(lista);
    }
}

void BorrarArbol(nodoArbol*arbol)
{
    if(arbol==NULL)
    {
        return;
    }
    else
    {
        BorrarArbol(arbol->izq);
        free(arbol);
        BorrarArbol(arbol->der);
    }
}
