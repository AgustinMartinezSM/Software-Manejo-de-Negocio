#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define archivo "RegistrosNuevo.bin"
#define archi3 "Ventas.bin"
#define ALIMENTO "alimentos"
#define LIMPIEZA "limpieza"
#define ROPA "ropa"
#define ELECTRODOMESTICOS "electrodomesticos"
#define BEBIDAS "bebidas"
#define SNACKS "snacks"
#define HERRAMIENTAS "herramientas"

// Definir un array de constantes
#define categorias {ALIMENTO, LIMPIEZA, ROPA, ELECTRODOMESTICOS, BEBIDAS, SNACKS, HERRAMIENTAS}//Arreglo constante con las diferentes categorias

typedef struct
{
    char nombre[20];
    char categoria[20];
    char marca[20];
    int codigo;
    float precio;
    int stock;
    int estado; // 1 alta 0 baja
} stRegistro;     // Estructura registros

typedef struct
{
    int codigo;
    char nombre[20];
    char marca[20];
    float precio;
    int stock;
    int estado;
} stProducto; // Estructura registros

typedef struct
{
    int codigo;
    char nombre[20];
    char marca[20];
    float precio; // Debe ser float
} stProductoFilas; // Estructura registros


typedef struct
{
    float Ingresos;
    int Legajo;
    char NombreDelCajero[30];
    int Dia;
} Ventas;


// prototipados

int BuscarCodigo();
void CargarArchivo();
void MostrarArchivo();
void MostrarDatos(stRegistro art);
void ModificarRegistro(stProducto producto);
void PedirCategoria(char cat[]);
void SobreescribirRegistro(stRegistro datos, int pos);
int BuscarNombre(char nombre[]);//Buscamos un codigo aleatorio para asignarle verificando que no se repita

stRegistro PedirDatos(int*flag);
stRegistro ModificarDatosRegistro(stRegistro datos, stProducto producto);

#endif // ARCHIVOS_H_INCLUDED
