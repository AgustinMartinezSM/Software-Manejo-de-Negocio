#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LISTAS.h"

void cargarDatosEmpleado(empleado *nuevoEmpleado)
{
    printf("||--------------------------------------------||\n");
    printf("||------      CARGAR DATOS EMPLEADO     ------||\n");
    printf("||--------------------------------------------||\n");
    printf("||    INGRESE LOS DATOS DEL NUEVO EMPLEADO:   ||\n");
    printf("||--------------------------------------------||\n");
    printf("||--------------------------------------------||\n");
    printf("|| Ingrese el NOMBRE y APELLIDO:  ");
    fflush(stdin);
    gets(nuevoEmpleado->NombreYape);
    printf("||--------------------------------------------||\n");

    printf("||Ingrese la EDAD:  ");
    scanf(" %d", &nuevoEmpleado->edad);
    printf("||--------------------------------------------||\n");

    do
    {
        printf("||--------------------------------------------||\n");
        printf("|| Ingrese el DNI del empleado:  ");
        scanf(" %d", &nuevoEmpleado->DNI);
        printf("||--------------------------------------------||\n");

        if (validarDNI(nuevoEmpleado->DNI) == 1)
        {
            printf("=ERROR. Ingrese nuevamente el DNI=\n");
        }
    }
    while (validarDNI(nuevoEmpleado->DNI) == 1);
    printf("||--------------------------------------------||\n");
    strcpy(nuevoEmpleado->tipoEmpleado, "Cajero");
    printf("||     EMPLEADO REGISTRADO COMO 'Cajero'      ||\n");
    printf("||--------------------------------------------||\n");

    nuevoEmpleado->estado = 1;
    printf("||     ESTADO REGISTRADO COMO 'ACTIVO'        ||\n");
    printf("||--------------------------------------------||\n");

    nuevoEmpleado->Legajo = CargarLegajos(*nuevoEmpleado) + 1;
    printf("||     LEGAJO ASIGNADO AUTOMATICAMENTE        ||\n");
    printf("||--------------------------------------------||\n");

    printf("|| Ingrese la fecha de Registro xx/xx: ");
    fflush(stdin);
    gets(nuevoEmpleado->FechadeReg);
    printf("||--------------------------------------------||\n");

    nuevoEmpleado->sueldo = sueldoFijo;
    printf("||     SUELDO CORRESPONDIENTE ASIGNADO        ||\n");
    printf("||--------------------------------------------||\n");

    printf("Ingresar contrasenia del usuario: ");
    fflush(stdin);
    gets(nuevoEmpleado->contrasenia);
    printf("||--------------------------------------------||\n");
    printf("||--------------------------------------------||\n");
    printf("||      INGRESE LOS DATOS DE DOMICILIO:       || \n");
    printf("||--------------------------------------------||\n");
    printf("||  Ingrese la calle:  ");
    fflush(stdin);
    gets(nuevoEmpleado->A.calle);
    printf("||--------------------------------------------||\n");

    printf("||  Ingrese la altura:  ");
    fflush(stdin);
    scanf(" %d", &nuevoEmpleado->A.altura);
    printf("||--------------------------------------------||\n");
}

int CargarLegajos(empleado A)
{
    int MayorLegajo = 0;
    FILE *empleados = fopen("empleados.bin", "rb");

    if (empleados != NULL)
    {
        fseek(empleados, -1 * sizeof(empleado), SEEK_END);

        if (fread(&A, sizeof(empleado), 1, empleados))
        {
            MayorLegajo = A.Legajo;
        }

        fclose(empleados);
    }

    return MayorLegajo;
}

int validarDNI(int DNI)
{
    FILE *empleados = fopen("empleados.bin", "rb");
    if (empleados == NULL)
    {
        printf("=ERROR.No se pudo abrir el archivo=\n");
        return 1; // Si hay un problema con el archivo DNI no valido
    }

    empleado e;
    while (fread(&e, sizeof(empleado), 1, empleados) == 1)
    {
        if (e.DNI == DNI)
        {
            fclose(empleados);
            return 1; // El DNI ya existe
        }
    }

    fclose(empleados);
    return 0; // El DNI valido
}

void agregarEmpleadoArchivo()
{
    empleado nuevoEmpleado;

    FILE *archivoEmpleados= fopen("empleados.bin", "ab");

    if (archivoEmpleados == NULL)
    {
        printf("=ERROR. NO se pudo abrir el archivo=\n");
    }

    cargarDatosEmpleado(&nuevoEmpleado);
    fwrite(&nuevoEmpleado, sizeof(empleado), 1, archivoEmpleados);

    fclose(archivoEmpleados);
    printf("||--------------------------------------------||\n");
    printf("|| EMPLEADO AGREGADO AL ARCHIVO CON EXITO     ||\n");
    printf("||--------------------------------------------||\n");
}

void mostrarEmpleadosArchivo()
{
    empleado e;
    FILE *empleados = fopen("empleados.bin", "rb");

    if (empleados == NULL)
    {
        printf("=ERROR. NO se pudo abrir el archivo=\n");
        return;
    }

    while (fread(&e, sizeof(empleado), 1, empleados) > 0)
    {
        printf("\n\n||--------------------------------------------||\n");
        printf("||--------------------------------------------||\n");
        mostrarEmpleados(e);
        printf("||--------------------------------------------||\n");
        printf("||--------------------------------------------||\n\n");
    }

    fclose(empleados);
}

void mostrarEmpleados(empleado e)
{
    printf("||--------------------------------------------||\n");
    printf("||--------------------------------------------||\n");
    printf("||             MOSTRAR EMPLEADOS              ||\n");
    printf("||--------------------------------------------||\n");
    printf("||--------------------------------------------||\n");
    printf("||LEGAJO: %d                                  ||\n", e.Legajo);
    printf("||--------------------------------------------||\n");
    printf("||NOMBRE Y APELLIDO: %s                       ||\n", e.NombreYape);
    printf("||--------------------------------------------||\n");
    printf("||EDAD: %d                                    ||\n", e.edad);
    printf("||--------------------------------------------||\n");
    printf("||DNI: %d                                     ||\n", e.DNI);
    printf("||--------------------------------------------||\n");
    printf("||TIPO DE EMPLEADO: %s                        ||\n", e.tipoEmpleado);
    printf("||--------------------------------------------||\n");
    printf("||DIRECCION: | %s | | %d |                    ||\n", e.A.calle, e.A.altura);
    printf("||--------------------------------------------||\n");
    printf("||SUELDO: %d                                  ||\n", e.sueldo);
    printf("||--------------------------------------------||\n");

    if (e.estado == 1)
    {
        printf("||ESTADO: ACTIVO                              ||\n");
        printf("||--------------------------------------------||\n");
    }
    else
    {
        printf("||ESTADO: INACTIVO                            ||\n");
        printf("||--------------------------------------------||\n");
    }

    printf("||FECHA DE REGISTRO: %s                       ||\n", e.FechadeReg);
    printf("||--------------------------------------------||\n");
    printf("||CONTRASENIA: %s                             ||\n", e.contrasenia);
    printf("||--------------------------------------------||\n");
    printf("||--------------------------------------------||\n");
}

int buscarEmpleadoPorLegajo(int legajo, empleado *encontrado)
{
    FILE *empleados = fopen("empleados.bin", "rb");
    empleado datos;

    int flag =0;
    if (empleados == NULL)
    {
        printf("=ERROR. NO se pudo abrir el archivo=\n");
        return;  // No se pudo abrir el archivo
    }

    int encontradoFlag = 0;

    while (fread(&datos, sizeof(empleado), 1, empleados) > 0 && !encontradoFlag)
    {
        if (datos.Legajo == legajo)
        {
            *encontrado= datos;
            encontradoFlag = 1;  // Se encontro el empleado
            flag=1;
        }
    }

    fclose(empleados);

    if (!encontradoFlag)
    {
        printf("||---------------------------------------------------||\n");
        printf("||=NO se encontro un empleado con el LEGAJO: | %d |  ||\n", legajo);
        printf("||---------------------------------------------------||\n");
        flag=0;
    }

    return flag;
}

void buscarYMostrarEmpleadoPorLegajo()
{
    int legajoBuscar;
    printf("||--------------------------------------------||\n");
    printf("||  Ingrese el legajo a buscar:  ");
    scanf("%d", &legajoBuscar);
    printf("||--------------------------------------------||\n");

    empleado encontrado;

    if (buscarEmpleadoPorLegajo(legajoBuscar, &encontrado))
    {
        printf("||--------------------------------------------||\n");
        printf("||            ¡EMPLEADO ENCONTRADO!           ||\n");
        printf("||--------------------------------------------||\n");
        mostrarEmpleados(encontrado);
    }
    else
    {
        printf("=ERROR. NO se encontro un empleado con el LEGAJO: |%d| =\n", legajoBuscar);
    }
}

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
        printf("||--------------------------------------------||\n");
        printf("||--------------------------------------------||\n");
        actual = actual->sig;
    }
}

nodoListaD* buscarPorLegajoLD(nodoListaD* lista, int legajo)
{
    nodoListaD* actual = lista;
    nodoListaD* encontrado = NULL;

    while (actual != NULL)
    {
        if(actual->dato.Legajo == legajo)
        {
            encontrado =actual;
            return encontrado;
        }
        actual = actual->sig;

    }
    return encontrado;  // No se encontro el legajo
}

nodoListaD* darDeAltaPorLegajoLD(nodoListaD* lista, int legajo)
{
    empleado encontrado;
    int flag = buscarEmpleadoPorLegajo(legajo,&encontrado);

    if (flag == 1)
    {
        encontrado.estado = 1;  // Cambia el estado a inactivo
        printf("||---------------------------------------------||\n");
        printf("||  Empleado con LEGAJO: |%d| dado de |ALTA|   ||\n", legajo);
        printf("||---------------------------------------------||\n");
        modificarRegistroEmpleado(encontrado);
    }
    else
    {
        printf("=ERROR. NO se encontro un empleado con el LEGAJO: |%d|.\n", legajo);
    }

    return lista;
}

void borrarLD(nodoListaD*lista)
{
    if(lista != NULL)
    {
        borrarLD(lista->sig);
        free(lista);
    }
}

nodoListaD* archivoToLD()
{
    FILE *empleados = fopen("empleados.bin", "rb");

    if (empleados == NULL)
    {
        printf("=ERROR. NO se pudo abrir el archivo==\n");
        return 0;
    }

    nodoListaD *listaLd = inicLD();
    empleado e;

    while (fread(&e, sizeof(empleado), 1, empleados) > 0)
    {
        listaLd = agregarAlFinalLD(listaLd, e);
    }

    fclose(empleados);

    return listaLd;
}
//CASE 2
void mostrarEmpleadoPorLegajoLD(nodoListaD* lista)
{
    int legajoBuscar=0;
    printf("||--------------------------------------------||\n");
    printf("|| Ingrese el LEGAJO a buscar: ");
    printf("||--------------------------------------------||\n");
    scanf( "%d", &legajoBuscar);

    nodoListaD* encontrado = buscarPorLegajoLD(lista, legajoBuscar);

    if (encontrado != NULL)
    {
        printf("||--------------------------------------------||\n");
        printf("||           ¡EMPLEADO ENCONTRADO!            ||\n");
        printf("||--------------------------------------------||\n");
        mostrarEmpleados(encontrado->dato);
        system("PAUSE");
    }
    else
    {
        printf("=ERROR. NO se encontro un empleado con el LEGAJO |%d| =\n", legajoBuscar);
    }
}
//CASE 4:
void modificarEmpleadoPorLegajo(nodoListaD* lista, int op, int legajoModificar)
{
    nodoListaD* encontrado = buscarPorLegajoLD(lista, legajoModificar);
    if (encontrado != NULL)
    {
        if(op ==  1)
        {
            printf("||--------------------------------------------||\n");
            printf("||INGRESE NUEVO:                              ||\n");
            printf("|| NOMBRE Y APELLIDO:  ");
            fflush(stdin);
            fgets(encontrado->dato.NombreYape, sizeof(encontrado->dato.NombreYape), stdin);
            printf("||--------------------------------------------||\n");
            encontrado->dato.NombreYape[strcspn(encontrado->dato.NombreYape, "\n")] = '\0'; // Elimina el caracter de nueva línea
        }
        else if(op == 2)
        {
            printf("||--------------------------------------------||\n");
            printf("||INGRESE NUEVO:                              ||\n");
            printf("|| EDAD:  ");
            scanf("%d", &encontrado->dato.edad);
            printf("||--------------------------------------------||\n");

        }
        else if(op == 3)
        {
            printf("||--------------------------------------------||\n");
            printf("||INGRESE NUEVO:                              ||\n");
            printf("|| SUELDO:  ");
            scanf(" %d", &encontrado->dato.sueldo);
            printf("||--------------------------------------------||\n");
        }
        else if(op == 4)
        {
            printf("||--------------------------------------------||\n");
            encontrado->dato.estado = 0;
            printf("||          ESTADO CAMBIADO A 'INACTIVO'      ||\n");
            printf("||--------------------------------------------||\n");
        }
        else
        {
            printf("||--------------------------------------------||\n");
            printf("||INGRESE NUEVA:                              ||\n");
            printf("|| CONTRASENIA:  ");
            fflush(stdin);
            gets(encontrado->dato.contrasenia);
            printf("||--------------------------------------------||\n");
        }
        mostrarEmpleados(encontrado->dato);
        modificarRegistroEmpleado(encontrado->dato);
    }
    else
    {
        printf("=ERROR. NO se encontro un empleado con el LEGAJO: |%d| =\n", legajoModificar);
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
                datosModificados = ModificarDatosEmpleado(datos, nuevoEmpleado); // Modificamos el empleado
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
        printf("=ERROR al abrir el archivo=\n\n");
    }
}

empleado ModificarDatosEmpleado(empleado datos, empleado datosModificar)
{
    strcpy(datos.NombreYape,datosModificar.NombreYape);
    datos.edad = datosModificar.edad;
    datos.sueldo = datosModificar.sueldo;
    datos.estado = datosModificar.estado;
    strcpy(datos.contrasenia,datosModificar.contrasenia);

    return datos;

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
        printf("=ERROR al abrir el archivo=\n");
    }
}
