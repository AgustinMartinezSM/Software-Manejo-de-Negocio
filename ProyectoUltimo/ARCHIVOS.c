#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ARCHIVOS.h"

stRegistro PedirDatos(int*flag)
{

    stRegistro articuloNuevo;
    printf("||--------------------------------------------||\n");
    printf("||       ==INGRESAR DATOS DEL PRODUCTO==      ||\n");
    printf("||--------------------------------------------||\n");

    do
    {
        printf("||--------------------------------------------||\n");
        printf("|| NOMBRE A BUSCAR:  ");
        fflush(stdin);
        gets(articuloNuevo.nombre);
        printf("||--------------------------------------------||\n");
        *flag = BuscarNombre(articuloNuevo.nombre);
    }
    while(*flag == 0);

    if(*flag == -1)
    {
        PedirCategoria(articuloNuevo.categoria);
        printf("||--------------------------------------------||\n");
        printf("|| CATEGORIA: | %s |                          ||\n", articuloNuevo.categoria);
        printf("||--------------------------------------------||\n");

        printf("||--------------------------------------------||\n");
        articuloNuevo.codigo = BuscarCodigo();
        printf("||  CODIGO: | %d |                            ||\n", articuloNuevo.codigo);
        printf("||--------------------------------------------||\n");

        printf("||--------------------------------------------||\n");
        printf("||  MARCA:   ");
        fflush(stdin);
        gets(articuloNuevo.marca);
        printf("||--------------------------------------------||\n");

        printf("||--------------------------------------------||\n");
        printf("||  PRECIO:   ");
        scanf(" %f", &articuloNuevo.precio);
        printf("||--------------------------------------------||\n");

        printf("||--------------------------------------------||\n");
        printf("||  STOCK:  ");
        scanf(" %d", &articuloNuevo.stock);
        printf("||--------------------------------------------||\n");

        printf("||--------------------------------------------||\n");
        articuloNuevo.estado = 1;
        printf("||       ESTADO: ASIGNADO COMO ACTIVO         ||\n");
        printf("||--------------------------------------------||\n");

        system("CLS");
        printf("||--------------------------------------------||\n");
        printf("||     ===PRODUCTO AGREGADO CON EXITO ===     ||\n");
        printf("||--------------------------------------------||\n");
        MostrarDatos(articuloNuevo);

        system("pause");
        *flag= -1;
        return articuloNuevo;
    }
}

int BuscarNombre(char nombre[])//Buscamos un codigo aleatorio para asignarle verificando que no se repita
{
    stRegistro art;
    FILE *buff;
    int op=0, pos=0;
    int flag=-1;

    buff = fopen(archivo, "rb");

    if (buff != NULL)
    {
        while (fread(&art, sizeof(stRegistro), 1, buff) > 0)
        {
            if(strcmp(nombre,art.nombre) == 0)
            {
                if(art.estado == 1)
                {
                    flag=0;
                    printf("==Error.NOMBRE DUPLICADO==\n");
                    system("PAUSE");
                    return flag;
                }
                else
                {
                    printf("||--------------------------------------------||\n");
                    printf("||----PRODUCTO ENCONTRADO EN LOS REGISTROS----||\n");
                    printf("||-PRESIONE: 1 Para dar de ALTA.              ||\n");
                    printf("||-PRESIONE: 0 Para ingresar otro nombre.     ||\n");
                    printf("||--------------------------------------------||\n");
                    scanf(" %d", &op);
                    if(op == 1)
                    {
                        pos = ftell(buff)/sizeof(stRegistro);//Guardamos la posicion del registro
                        pos--;
                        art.estado = 1;
                        SobreescribirRegistro(art,pos);
                        flag=1;
                        return flag;
                    }
                    else
                    {
                        flag=0;
                        return flag;
                    }
                }

            }
            else
            {
                flag=-1;
            }
        }
        fclose(buff);
    }
    else
    {
        printf("=ERROR=");
    }
    return flag;
}

void PedirCategoria(char cat[])
{
    const char categoria[][30] = categorias;
    int i=-1;

    while(i < 0 || i > 6)
    {
        printf("||--------------------------------------------||\n");
        printf("||--------------------------------------------||\n");
        printf("||           |CATEGORIA DE PRODUCTOS|         ||\n");
        printf("||--------------------------------------------||\n");
        printf("||--------------------------------------------||\n");
        printf("||0. -> ALIMENTOS                             ||\n");
        printf("||1. -> LIMPIEZA                              ||\n");
        printf("||2. -> ROPA                                  ||\n");
        printf("||3. -> ELECTRODOMESTICOS                     ||\n");
        printf("||4. -> BEBIDAS                               ||\n");
        printf("||5. -> SNACKS                                ||\n");
        printf("||6. -> HERRAMIENTAS                          ||\n");
        printf("||--------------------------------------------||\n");
        printf("||  INGRESAR NUMERO DE CATEGORIA:  ||\n");
        scanf(" %d",&i);
        printf("||--------------------------------------------||\n");
        if(i < 0 || i >6)
        {
            system("CLS");
            printf("\n=Numero incorrecto=\n");
        }
        else
        {
            strcpy(cat,categoria[i]);
        }
    }
}

void CargarArchivo()
{
    stRegistro art;
    FILE *buff;
    int j = 1, flag=0;
    buff = fopen(archivo, "ab");

    if (buff != NULL)
    {
        while (j != 0)
        {
            system("CLS");
            art = PedirDatos(&flag);
            if(flag == -1)
            {
                fwrite(&art, sizeof(stRegistro), 1, buff);
                printf("||--------------------------------------------||\n");
                printf("|| INGRESAR 0 para no cargar mas datos:  ");
                scanf("%d", &j);
                printf("||--------------------------------------------||\n");
            }
            else
            {
                j=0;
            }
        }
        fclose(buff);
    }
    else
    {
        printf("=ERROR=");
    }
}

void MostrarArchivo()
{
    stRegistro art;
    FILE *buff;

    buff = fopen(archivo, "rb");

    if (buff != NULL)
    {
        while (fread(&art, sizeof(stRegistro), 1, buff) > 0)
        {
            MostrarDatos(art);
        }
        fclose(buff);
    }
    else
    {
        printf("=ERROR=");
    }
}

int BuscarCodigo()//Buscamos un codigo aleatorio para asignarle verificando que no se repita
{
    stRegistro art;
    int codigo = 0;
    FILE *buff;

    srand(time(NULL));

    codigo = rand() %10000;

    buff = fopen(archivo, "rb");

    if (buff != NULL)
    {
        while (fread(&art, sizeof(stRegistro), 1, buff) > 0)
        {
            if(codigo == art.codigo)
            {
                fseek(buff, 0, SEEK_SET);
                codigo = rand() %10000;
            }
        }
        fclose(buff);
    }
    else
    {
        printf("=ERROR=");
    }

    return codigo;
}

void MostrarDatos(stRegistro art)
{
    printf("||--------------------------------------------||\n");
    printf("||----------    DATOS PRODUCTO    ------------||\n");
    printf("||--------------------------------------------||\n");
    printf("|| CODIGO: %d                                 ||\n", art.codigo);
    printf("|| NOMBRE: %s                                 ||\n", art.nombre);
    printf("|| CATEGORIA: %s                              ||\n", art.categoria);
    printf("|| MARCA: %s                                  ||\n", art.marca);
    printf("|| PRECIO: %.2f                               ||\n", art.precio);
    printf("|| STOCK: %d                                  ||\n", art.stock);
    printf("|| ESTADO: ");
    if(art.estado == 1)
    {
        printf("  |ACTIVO|                                    ||\n");
    }
    else
    {
        printf("  |INACTIVO|                                  ||\n");
    }
    printf("||--------------------------------------------||\n");
}

void ModificarRegistro(stProducto producto)
{
    FILE *buff;
    stRegistro datos, datos2;
    int flag = 0, pos = 0;

    buff = fopen(archivo, "rb");

    if (buff != NULL)
    {
        while (fread(&datos, sizeof(stRegistro), 1, buff) > 0 && flag == 0)
        {
            // Comprobar si el ID del registro coincide con el ID buscado
            if (datos.codigo == producto.codigo)
            {
                pos = ftell(buff)/sizeof(stRegistro);//Guardamos la posicion del registro
                pos--;
                datos2 = ModificarDatosRegistro(datos,producto);//Modificamos el regidstro
                flag = 1;
            }
        }
        fclose(buff);
        if(flag == 1)
        {
            SobreescribirRegistro(datos2,pos);//Lo soobreescribimos en el archivo
        }
    }
    else
    {
        printf("=Error al abrir el archivo=\n\n");
    }
}

void SobreescribirRegistro(stRegistro datos, int pos)//Soobreescribimos el registro del archivo modificado
{
    FILE*buff = fopen(archivo,"r+b");

    if(buff != NULL)
    {
        fseek(buff, (pos*sizeof(stRegistro)), SEEK_SET);
        fwrite(&datos, sizeof(stRegistro), 1, buff);
        fclose(buff);
    }
    else
    {
        printf("\n=Error al abrir el archivo=\n");
    }
}

stRegistro ModificarDatosRegistro(stRegistro datos, stProducto producto)//Hacemos las modificaciones
{
    strcpy(datos.nombre,producto.nombre);
    strcpy(datos.marca,producto.marca);
    datos.precio = producto.precio;
    datos.stock = producto.stock;
    datos.estado = producto.estado;

    return datos;
}
