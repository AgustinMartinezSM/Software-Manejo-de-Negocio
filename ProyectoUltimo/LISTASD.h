#ifndef LISTASD_H_INCLUDED
#define LISTASD_H_INCLUDED

#define archi2 "empleados.bin"

///ESTRUCTURAS:

typedef struct{
    char calle[20];
    int altura;//POR EJEMPLO: "1870"
} direccion;

typedef struct{
    int Legajo;
    char NombreYape[40];//NOMBRE Y APELLIDO
    int edad;
    char DNI[20];
    char tipoEmpleado[40]; //CAJERO
    direccion A;
    long int sueldo;
    int estado;//1 ACTIVO Y 0 INACTIVO
    char FechadeReg[30]; //FECHA DE REGISTRO
    int contrasenia; //CONTRASEÑA
} empleado;

typedef struct nodoListaD{
    empleado dato;
    struct nodoListaD* sig;
    struct nodoListaD* ant;
}nodoListaD;



///PROTOTIPADOS:
//CASE 1
nodoListaD* agregarAlFinalLD(nodoListaD* lista, empleado nuevoEmpleado);
//CASE 1

//CASE 2
void mostrarEmpleadoPorLegajoLD(nodoListaD* lista);
//CASE 2

//CASE 3
void mostrarLD(nodoListaD* lista);
//CASE 3

//CASE 4
void modificarEmpleadoPorLegajo(nodoListaD* lista, int op, int legajoModificar);
void modificarRegistroEmpleado(empleado nuevoEmpleado);
void SobreescribirEmpleado(empleado datos, int pos);
//CASE 4
nodoListaD*inicLD();
nodoListaD* buscarPorLegajoLD(nodoListaD* lista, int legajo);
nodoListaD* darDeBajaPorLegajoLD(nodoListaD* lista, int legajo);
void borrarLD(nodoListaD*lista);
nodoListaD* archivoToLD();


#endif // LISTASD_H_INCLUDED
