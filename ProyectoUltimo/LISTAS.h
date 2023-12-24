#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#define archi2 "empleados.bin"
#define sueldoFijo  800

///ESTRUCTURAS:

typedef struct{
    char calle[20];
    int altura;//POR EJEMPLO: "1870"
} direccion;

typedef struct{
    int Legajo;
    char NombreYape[40];//NOMBRE Y APELLIDO
    int edad;
    int DNI;
    char tipoEmpleado[40]; //CAJERO
    direccion A;
    long int sueldo;
    int estado;//1 ACTIVO Y 0 INACTIVO
    char FechadeReg[30]; //FECHA DE REGISTRO
    char contrasenia[20]; //CONTRASEÑA
} empleado;

typedef struct nodoEmpleado{
    empleado dato;
    struct nodoEmpleado* sig;
    struct nodoEmpleado* ant;
} nodoEmpleado;

typedef struct nodoListaD{
    empleado dato;
    struct nodoListaD* sig;
    struct nodoListaD* ant;
}nodoListaD;


///PROTOTIPADOS:
///CARGAR DATOS EMPLEADOS
void cargarDatosEmpleado(empleado *nuevoEmpleado);
int CargarLegajos(empleado A);
int validarDNI(int dni);
void agregarEmpleadoArchivo();

///MOSTRAR EMPLEADOS
void mostrarEmpleadosArchivo();
void mostrarEmpleados(empleado e);

///BUSCAR EMPLEADOS
int buscarEmpleadoPorLegajo(int legajo, empleado *encontrado);
void buscarYMostrarEmpleadoPorLegajo();

empleado ModificarDatosEmpleado(empleado datos, empleado datosModificar);
void mostrarEmpleadoPorLegajoLD(nodoListaD* lista);
nodoListaD* buscarPorLegajoLD(nodoListaD* lista, int legajo);
nodoListaD*inicLD();
nodoListaD* agregarAlFinalLD(nodoListaD* lista, empleado nuevoEmpleado);
void mostrarLD(nodoListaD* lista);
nodoListaD* darDeAltaPorLegajoLD(nodoListaD* lista, int legajo);
void borrarLD(nodoListaD*lista);
nodoListaD* archivoToLD();
void modificarEmpleadoPorLegajo(nodoListaD* lista, int op, int legajoModificar);
void modificarRegistroEmpleado(empleado nuevoEmpleado);
void SobreescribirEmpleado(empleado datos, int pos);



#endif // LISTAS_H_INCLUDED
