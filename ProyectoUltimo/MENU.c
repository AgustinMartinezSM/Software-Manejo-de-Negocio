#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MENU.h"

int ValidacionAdmin()
{
    char Nombre[30];
    int contra;
    int flag=1;
    int i=0;
    while(i<3 && flag==1)
    {
        printf("||--------------------------------||\n");
        printf("||      Ingrese el usuario:  ");
        fflush(stdin);
        gets(Nombre);
        printf("\n||--------------------------------||\n");
        printf("||      Ingrese su contrasenia:  ");
        scanf(" %d",&contra);

        if((strcmp(Nombre,NombreAdmin)==0) && (contra==ContraAdmin))
        {
            MenuAdmin();
            flag=0;
        }
        else
        {
            printf("Datos incorrectos, vuelva a ingresar los datos\n");
        }
        i++;
    }
    return flag;
}

int ValidacionUsuario()
{
    FILE* archi;
    archi=fopen(archi2,"rb");
    empleado aux;
    char Nombre[30];
    char contra[30];
    int flag=1, i=0;
    if(archi)
    {
        while(i<3 && flag==1)
        {
            printf("||--------------------------------||\n");
            printf("||      Ingrese el usuario:  ");
            fflush(stdin);
            gets(Nombre);
            printf("\n||--------------------------------||\n");
            printf("||      Ingrese su contrasenia:  ");
            fflush(stdin);
            gets(contra);
            printf("||-------------------------------- ||\n");
            while(fread(&aux,sizeof(empleado),1,archi)>0 && flag==1)
            {

                if((strcmp(Nombre,aux.NombreYape)==0) && strcmp(contra,aux.contrasenia)==0)
                {
                    if(aux.estado == 1)
                    {
                        flag=0;
                    }
                }
            }
            i++;
        }
    }
    else
    {
        printf("Error");
    }
    return flag;
}

void Menu()
{

    int op = 0;
    int flag=0;

    do
    {
        system("CLS");
        printf("||--------------------------------||\n");
        printf("||     |  MENU DE OPCIONES  |     ||\n");
        printf("||--------------------------------||\n");
        printf("||--------------------------------||\n");
        printf("||                                ||\n");
        printf("||1. Ingresar como Administrador. ||\n");
        printf("||                                ||\n");
        printf("||2. Ingresar como Usuario.       ||\n");
        printf("||                                ||\n");
        printf("||--------------------------------||\n");
        printf("||3. Salir.                       ||\n");
        printf("||--------------------------------||\n");
        printf("||Ingrese una opcion: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            flag = ValidacionAdmin();
            if(flag == 0)
            {
                MenuAdmin();
            }
            else
            {
                printf("Usted a intentado 3 veces ingresar los datos, el programa se cerrara.\n");
            }
            break;

        case 2:
            flag=ValidacionUsuario();
            if(flag==0)
            {
                MenuUsuario();
            }
            else
            {
                printf("Usted a intentado 3 veces ingresar los datos, el programa se cerrara.\n");
                system("pause");
            }
            break;

        default:
            printf("|Saliendo...|\n");
            break;
        }
    }
    while (op != 3);


}


void MenuAdmin()
{
    int opcion = 0;
    do
    {
        system("CLS");
        printf("||--------------------------------||\n");
        printf("||     |  MENU DE OPCIONES  |     ||\n");
        printf("||        | ADMINISTRADOR |       ||\n");
        printf("||--------------------------------||\n");
        printf("||--------------------------------||\n");
        printf("||OPCIONES PRODUCTOS:             ||\n");
        printf("||1. Agregar Producto.            ||\n");
        printf("||2. Buscar Producto.             ||\n");
        printf("||3. Modificar productos.         ||\n");
        printf("||4. Mostrar Productos.           ||\n");
        printf("||--------------------------------||\n");
        printf("||OPCIONES EMPLEADOS:             ||\n");
        printf("||5. Menu Empleados.              ||\n");
        printf("||--------------------------------||\n");
        printf("||6. Salir.                       ||\n");
        printf("||--------------------------------||\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            CargarArchivo();
            break;

        case 2:
            MenuBuscar();
            break;

        case 3:
            MenuModificar();
            break;

        case 4:
            MenuMostrar();
            break;

        case 5:
            MenuEmpleados();
            break;

        case 6:
            system("CLS");
            break;
        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    }
    while (opcion != 6);
}

void MenuUsuario()
{
    int opcion = 0,legajo=0,dia=0;
    Fila  filita;
    InicFilita(&filita);

    do
    {
        printf("\n||--------------------------------||\n");
        printf("||     |  MENU DE OPCIONES  |     ||\n");
        printf("||       |     USUARIO    |       ||\n");
        printf("||--------------------------------||\n");
        printf("||--------------------------------||\n");
        printf("||1. Nueva venta.                 ||\n");
        printf("||                                ||\n");
        printf("||2. Ver stock.                   ||\n");
        printf("||--------------------------------||\n");
        printf("||3. <- Volver para atras.        ||\n");
        printf("||--------------------------------||\n");
        printf("||      Ingrese una opcion:  ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese su legajo: \n");
            fflush(stdin);
            scanf("%i",&legajo);
            printf("Ingrese el dia: \n");
            fflush(stdin);
            scanf("%i",&dia);
            FilaAlArchivo(&filita,legajo,dia);
            break;

        case 2:
            MenuMostrar();
            break;

        case 3:
            printf("Saliendo del programa.\n");
            break;

        default:
            printf("Error. Intente nuevamente.\n");
            break;
        }
    }
    while (opcion != 3);
    LiberarMemoriaFila(&filita);
}


void MenuBuscar()
{
    system("CLS");
    int opcion = 0, codigo = 0, i=0;
    char cat[20], nombre[20] ;
    nodoLDA*lista = InicLista();
    nodoLDA*listaEnc;
    nodoArbol*arbol = NULL;

    do
    {
        printf("||--------------------------------||\n");
        printf("||           |  MENU  |           ||\n");
        printf("||        |    BUSCAR    |        ||\n");
        printf("||--------------------------------||\n");
        printf("||--------------------------------||\n");
        printf("||1. Buscar por Codigo.           ||\n");
        printf("||                                ||\n");
        printf("||2. Buscar por Nombre.           ||\n");
        printf("||--------------------------------||\n");
        printf("||3. <- Volver para atras.        ||\n");
        printf("||--------------------------------||\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:

            lista = lda(lista, opcion);
            if(lista!=NULL)
            {

                PedirCategoria(cat);
                listaEnc = buscarCategoria(lista, cat);

                if(listaEnc != NULL)
                {
                    printf("||--------------------------------||\n");
                    printf("||  Ingresar codigo del producto:  ");
                    scanf(" %d", &codigo);
                    printf("||--------------------------------||\n");

                    arbol = BuscarPorCodigo(listaEnc->subArbol, codigo);
                    if(arbol != NULL)
                    {
                        mostrarProducto(arbol->dato);
                    }
                    else
                    {
                        printf("== No se encontro el producto. ==");
                    }
                }
                else
                {
                    printf("=Error al buscar la categoria.=");
                    system("pause");
                }
            }
            BorrarListaArboles(lista);
            break;

        case 2:
            lista = lda(lista, opcion);
            if(lista!=NULL)
            {

                PedirCategoria(cat);
                listaEnc = buscarCategoria(lista, cat);

                if(listaEnc != NULL)
                {
                    printf("||--------------------------------||\n");
                    printf("||  Ingresar nombre del producto:  ");
                    fflush(stdin);
                    gets(nombre);
                    printf("||--------------------------------||\n");

                    arbol = BuscarPorNombre(listaEnc->subArbol, nombre);

                    if(arbol != NULL)
                    {
                        mostrarProducto(arbol->dato);
                    }
                    else
                    {
                        printf("\n== No se encontro el producto. ==");
                    }
                }
                else
                {
                    printf("\n=Error al buscar la categoria.=");
                }
            }
            BorrarListaArboles(lista);
            break;

        case 3:
            printf("|| Saliendo del programa! ||.\n");
            break;

        default:
            printf("=Error. Intente nuevamente.=\n");
            break;
        }
    }
    while (opcion != 3);
}

void MenuModificar()
{
    system("CLS");
    printf("\n||  === |   Menu  | ===   ||");
    printf("|| === |  Modificar | === ||\n");
    celda arreglo[dimension];
    int validos = carga_desde_archivo(arreglo), codigo=0, opcion = 0, i = -1;
    char cat[20];

    if(validos >0)
    {
        PedirCategoria(cat);
        int pos = busca_pos_categoria(arreglo, cat, validos);
        if(pos >= 0 )
        {
            printf("||--------------------------------||\n");
            printf("||  Ingresar codigo del producto:  ");
            scanf(" %d", &codigo);
            printf("||--------------------------------||\n");
            nodoLista *nodoModificar = buscar_nodo_cod(arreglo[pos].productos, codigo);//Buscamos el nodo a modificar
            if(nodoModificar != NULL)
            {
                system("CLS");
                printf("\n|=|  PRODUCTO: |=|\n");
                mostrarProducto(nodoModificar->producto);
                do
                {
                    printf("||--------------------------------||\n");
                    printf("||   |  ELIJA QUE MODIFICAR:  |   ||\n");
                    printf("||--------------------------------||\n");
                    printf("||--------------------------------||\n");
                    printf("||1. Modificar Nombre.            ||\n");
                    printf("||2. Modificar Marca.             ||\n");
                    printf("||3. Modificar Precio.            ||\n");
                    printf("||4. Modificar Stock.             ||\n");
                    printf("||5. Modificar Estado(inactivo).  ||\n");
                    printf("||--------------------------------||\n");
                    printf("||6. <- Volver para atras.        ||\n");
                    printf("||--------------------------------||\n");
                    printf("||    Ingrese una opcion:  ");
                    scanf("%d", &opcion);
                    printf("||--------------------------------||\n");
                    nodoModificar = Modificar(nodoModificar,opcion);
                    system("CLS");
                    printf("\n|==|   Producto modificado:  |==|\n");
                    mostrarProducto(nodoModificar->producto);
                }
                while (opcion != 6);
            }
            else
            {
                printf("\n== No se encontro el codigo. ==\n");
                system("PAUSE");
            }
        }
        BorrarAdl(arreglo,validos);
    }
    else
    {
        printf("\n=ERROR=\n");
    }
}

void MenuEmpleados()
{
    nodoListaD*lista=NULL;
    int opcion = 0, legajo=0, flag = 0;
    do
    {
        system("CLS");
         printf("||--------------------------------||\n");
         printf("||       |  MENU EMPLEADOS  |     ||\n");
         printf("||--------------------------------||\n");
         printf("||--------------------------------||\n");
         printf("||1. Cargar un empleado.          ||\n");
         printf("||2. Buscar un empleado.          ||\n");
         printf("||3. Mostrar empleados.           ||\n");
         printf("||4. Modificar empleados.         ||\n");
         printf("||5. Dar de alta un empleado.     ||\n");
         printf("||--------------------------------||\n");
         printf("||6. <- Volver para atras.        ||\n");
         printf("||--------------------------------||\n");

         printf("||     Ingrese una opcion:  ");
         scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarEmpleadoArchivo();
            break;

        case 2:
            lista = archivoToLD();
            mostrarEmpleadoPorLegajoLD(lista);
            borrarLD(lista);
            break;

        case 3:
            MenuMostrarEmpleados();
            break;
        case 4:
            lista = archivoToLD();
            if(lista != NULL)
            {
                printf("\n||          |  MODIFICAR  |        ||\n");
                printf("||       |  ELIJA LA OPCION: |     ||\n");
                printf("||---------------------------------||\n");
                printf("||1. Modificar Nombre.             ||\n");
                printf("||2. Modificar edad.               ||\n");
                printf("||3. Modificar sueldo.             ||\n");
                printf("||4. Modificar estado.             ||\n");
                printf("||5. Modificar contrasenia.        ||\n");
                printf("||----------------------------------||\n");
                printf("||   Ingresar opcion:  ");
                scanf(" %d", &opcion);
                printf("||----------------------------------||\n");
                printf("||   Ingresar legajo:  ");
                scanf(" %d",&legajo);
                printf("||----------------------------------||\n");
                modificarEmpleadoPorLegajo(lista, opcion,legajo);
                system("PAUSE");
            }

            borrarLD(lista);

            break;
        case 5:
            lista = archivoToLD();
            printf("||--------------------------------------------||\n");
            printf("||       |  DAR DE ALTA AUTOMATICAMENTE |     ||\n");
            printf("||             Ingresar legajo:   ");
            scanf(" %d",&legajo);
            printf("||--------------------------------------------||\n");
            darDeAltaPorLegajoLD(lista,legajo);
            borrarLD(lista);
            break;
        case 6:
            printf("== Saliendo del programa. ==\n");
            system("CLS");
            break;
        default:
            printf("=Error. Intente nuevamente.=\n");
            break;
        }
    }
    while (opcion != 6);
}

void MenuMostrarEmpleados()
{
    int opcion = 0,legajo=0,flag=0;
    empleado datos;
    nodoLis1* lista=InicListaLDL1();

    lista= ArchivoToLDL(lista);

    do
    {
        system("CLS");
         printf("||--------------------------------------------||\n");
         printf("||           |  MENU DE OPCIONES  |           ||\n");
         printf("||              | ADMINISTRADOR |             ||\n");
         printf("||--------------------------------------------||\n");
         printf("||--------------------------------------------||\n");
         printf("||1. Mostrar un empleado.                     ||\n");
         printf("||2. Mostrar TODOS los empleados.             ||\n");
         printf("||3. Mostrar las ventas de los empleados.     ||\n");
         printf("||4. Modificar las ventas de un solo empleado.||\n");
         printf("||                                            ||\n");
         printf("||--------------------------------------------||\n");
         printf("||5. <- Salir.                                ||\n");
         printf("||--------------------------------------------||\n");
         printf("||   Ingrese una opcion:  ");
         scanf("%d", &opcion);
         printf("||--------------------------------------------||\n");

        switch (opcion)
        {
        case 1:
            printf("||--------------------------------------------||\n");
            printf("||   Ingresar numero del legajo:  ");
            scanf("%d",&legajo);
            printf("||--------------------------------------------||\n");
            flag = buscarEmpleadoPorLegajo(legajo,&datos);
            mostrarEmpleados(datos);
            system("pause");
            break;

        case 2:
            mostrarEmpleadosArchivo();
            system("PAUSE");
            break;

        case 3:
            MostrarTodosLosEmpleadosVentas(lista);
            system("pause");
            break;

        case 4:
            printf("||--------------------------------------------||\n");
            printf("||   Ingrese el legajo del usuario:  \n");
            fflush(stdin);
            scanf("%d", &legajo);
            printf("||--------------------------------------------||\n");
            MostrarVentasUNempleado(lista, legajo);
            system("pause");
            break;
        case 5:
            printf("== SALIENDO ==\n");
            break;
        default:
            printf("=Error. Intente nuevamente=\n");
            break;
        }
    }
    while (opcion != 5);
    LiberarMemoria(lista);
}

void MenuMostrar()
{
    nodoLDA*lista = InicLista();
    int opcion = 0, opcion2 = 0, i =-1;
    char cat[30];

    do
    {
         system("CLS");
         printf("||--------------------------------------------||\n");
         printf("||                 |  MENU  |                 ||\n");
         printf("||                |  MOSTRAR |                ||\n");
         printf("||--------------------------------------------||\n");
         printf("||--------------------------------------------||\n");
         printf("||1. Mostrar por Categoria.                   ||\n");
         printf("||2. Mostrar todos los datos.                 ||\n");
         printf("||--------------------------------------------||\n");
         printf("||3. <- Salir.                                ||\n");
         printf("||--------------------------------------------||\n");
         printf("||   Ingresar una opcion:  ");
         scanf("%d", &opcion);
         printf("||--------------------------------------------||\n");
        switch (opcion)
        {
        case 1:
            do
            {
                system("CLS");
                printf("||--------------------------------------------||\n");
                printf("||                 |  MENU  |                 ||\n");
                printf("||             |  MOSTRAR POR: |              ||\n");
                printf("||--------------------------------------------||\n");
                printf("||--------------------------------------------||\n");
                printf("||1. Mostrar por Orden Alfabetico.            ||\n");
                printf("||2. Mostrar por Codigo.                      ||\n");
                printf("||3. Mostrar por Stock.                       ||\n");
                printf("||4. Mostrar por Precio.                      ||\n");
                printf("||--------------------------------------------||\n");
                printf("||5. <- Salir.                                ||\n");
                printf("||--------------------------------------------||\n");
                printf("||   Ingresar una opcion:  ");
                scanf(" %d", &opcion2);
                printf("||--------------------------------------------||\n");
            }
            while(opcion2 < 1 || opcion2 > 5);//Hasta que no se ingrese bien
            if(opcion2 != 5)
            {
                lista = lda(lista,opcion2);//cargamos la lista en base la forma de mostrar
                if(lista != NULL)//Verificamos que la lista se haya cargado bien
                {
                    PedirCategoria(cat);//pedimos la categoria por la que se quieren mostrar los datos
                    mostrarListaArboles(lista,cat);
                    BorrarListaArboles(lista);
                    system("PAUSE");
                }
                else
                {
                    printf("=Error al cargar la lista=");
                }
            }
            break;

        case 2:
            system("CLS");
            MostrarArchivo();
            system("PAUSE");
            break;
        default:
            break;
        }
    }
    while (opcion != 3);
}





