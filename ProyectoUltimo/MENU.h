#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "LDA.h"
#include "ADL.h"
#include "LISTAS.h"
#include "FILAS.h"
#include "LDL.h"

#define archi2 "empleados.bin"
#define NombreAdmin "juan"
#define ContraAdmin 1234


//Prototipados

int ValidacionAdmin();
int ValidacionUsuario();
void MenuAdmin();
void MenuUsuario();
void MenuBuscar();
void MenuMostrar();
void MenuModificar();
void MenuEmpleados();

#endif // MENU_H_INCLUDED
