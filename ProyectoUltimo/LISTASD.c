#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LISTASD.h"

nodoListaD*inicLD()
{
    return NULL;
}
//CASE 1
nodoListaD* agregarAlFinalLD(nodoListaD* lista, empleado nuevoEmpleado)
{
    nodoListaD* nuevoNodo = (nodoListaD*)malloc(sizeof(nodoListaD));

    nuevoNodo->dato = nuevoEmpleado;
    nuevoNodo->sig = NULL;
    nuevoNodo->ant = NULL;

    if (lista == NULL)
    {
        return nuevoNodo;
    }

    nodoListaD* actual = lista;

    while (actual->sig != NULL)
    {
        actual = actual->sig;
    }

    actual->sig = nuevoNodo;
    nuevoNodo->ant = actual;

    return lista;
}
//CASE 3
void mostrarLD(nodoListaD* lista)
{
    nodoListaD* actual = lista;

    while (actual != NULL)
    {
        mostrarEmpleados(actual->dato);
        printf("--------------------\n");
        actual = actual->sig;
    }
}

nodoListaD* buscarPorLegajoLD(nodoListaD* lista, int legajo)
{
    nodoListaD* actual = lista;

    while (actual != NULL)
    {
        if (actual->dato.Legajo == legajo)
        {
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;  // No se encontro el legajo
}

nodoListaD* darDeBajaPorLegajoLD(nodoListaD* lista, int legajo)
{
    nodoListaD* encontrado = buscarPorLegajo(lista, legajo);

    if (encontrado != NULL)
    {
        encontrado->dato.estado = 0;  // Cambia el estado a inactivo
        printf("Empleado con legajo %d dado de baja.\n", legajo);
    }
    else
    {
        printf("No se encontro un empleado con el legajo %d.\n", legajo);
    }

    return lista;
}

void borrarLD(nodoListaD*lista)
{
    if(lista != NULL)
    {
        BorrarLista(lista->sig);
        free(lista);
    }
}

nodoListaD* archivoToLD()
{
    FILE *empleados = fopen("empleados.bin", "rb");

    if (empleados == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return 0;
    }

    nodoListaD *listaLd = inicializarLD();
    empleado e;

    while (fread(&e, sizeof(empleado), 1, empleados) > 0)
    {
        listaLd = agregarAlFinal(listaLd, e);
    }

    fclose(empleados);

    return listaLd;
}
//CASE 2
void mostrarEmpleadoPorLegajoLD(nodoListaD* lista)
{
    int legajoBuscar;
    printf("Ingrese el legajo a buscar: ");
    scanf("%d", &legajoBuscar);

    nodoListaD* encontrado = buscarPorLegajo(lista, legajoBuscar);

    if (encontrado != NULL)
    {
        printf("Empleado encontrado:\n");
        mostrarEmpleados(encontrado->dato);
    }
    else
    {
        printf("No se encontro un empleado con el Legajo %d\n", legajoBuscar);
    }
}
//CASE 4:
void modificarEmpleadoPorLegajo(nodoListaD* lista, int op, int legajoModificar)
{
    nodoListaD* encontrado = buscarPorLegajo(lista, legajoModificar);

    if (encontrado != NULL)
    {
        if(op ==  1)
        {
            printf("Ingrese el nuevo Nombre y Apellido: ");
            fflush(stdin);
            fgets(encontrado->dato.NombreYape, sizeof(encontrado->dato.NombreYape), stdin);
            encontrado->dato.NombreYape[strcspn(encontrado->dato.NombreYape, "\n")] = '\0'; // Elimina el caracter de nueva línea
        }
        else if(op == 2)
        {
            printf("Ingrese la nueva Edad: ");
            scanf("%d", &encontrado->dato.edad);
        }
        else if(op == 3)
        {
            printf("Ingresar el nuevo sueldo: ");
            scanf(" %d", &encontrado->dato.sueldo);
        }
        else if(op == 4)
        {
            encontrado->dato.estado=0;
        }
        else
        {
            printf("Ingresar contrasenia: ");
            fflush(stdin);
            gets(encontrado->dato.contrasenia);
        }
    }
    else
    {
        printf("No se encontró un empleado con el Legajo %d\n", legajoModificar);
    }
}

void modificarRegistroEmpleado(empleado nuevoEmpleado)
{
    FILE *buff;
    empleado datos, datosModificados;
    int flag = 0, pos = 0;

    buff = fopen(archi2, "r+b");

    if (buff != NULL)
    {
        while ((fread(&datos, sizeof(empleado), 1, buff) > 0) && (flag == 0))
        {
            // Comprobar si el Legajo del empleado coincide con el Legajo buscado
            if (datos.Legajo == nuevoEmpleado.Legajo)
            {
                pos = ftell(buff)/sizeof(empleado); // Guardamos la posición del registro
                pos--;
                //datosModificados = ModificarDatosEmpleado(datos, nuevoEmpleado); // Modificamos el empleado
                flag = 1;
            }
        }
        fclose(buff);
        if (flag == 1)
        {
            SobreescribirEmpleado(datosModificados, pos); // Lo sobreescribimos en el archivo
        }
    }
    else
    {
        printf("Error al abrir el archivo\n\n");
    }
}

void SobreescribirEmpleado(empleado datos, int pos)
{
    FILE* buff = fopen(archi2, "r+b");

    if (buff != NULL)
    {
        fseek(buff, (pos * sizeof(empleado)), SEEK_SET);
        fwrite(&datos, sizeof(empleado), 1, buff);
        fclose(buff);
    }
    else
    {
        printf("\nError al abrir el archivo\n");
    }
}


