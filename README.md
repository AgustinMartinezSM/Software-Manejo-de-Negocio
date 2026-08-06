# Sistema de gestión de negocio

Sistema de consola en C para administrar los datos de un comercio: productos, stock,
empleados y ventas.

**Proyecto académico.** Es el trabajo práctico final de Programación de la Tecnicatura
Universitaria en Programación (UTN), entregado en 2023. Lo dejo público como registro de esa
etapa: la consigna era implementar estructuras de datos dinámicas a mano, sin librerías, y eso
es lo que explica casi todas las decisiones del código.

## Qué hace

Se entra con una de dos clases de cuenta, y cada una ve un menú distinto:

**Administrador**
- Alta de productos, con código generado al azar y verificado para que no se repita.
- Baja lógica: el producto queda con `estado = 0` en lugar de borrarse.
- Modificación de los datos de un producto.
- Búsqueda por código o por nombre.
- Listados ordenados y agrupados por categoría.
- Gestión de las cuentas de empleado.

**Empleado**
- Registrar ventas.
- Consultar el stock.

Los datos persisten en archivos binarios (`.bin`) que el programa crea y lee con `fread` y
`fwrite` sobre las estructuras.

## Estructuras de datos

Es la parte central del trabajo. Cada estructura se implementó desde cero y se eligió según
lo que se necesitaba hacer con los datos:

| Módulo | Estructura | Para qué se usa |
| --- | --- | --- |
| `LISTAS` | Lista simple | Base del resto de las estructuras |
| `LD` / `LISTASD` | Lista doblemente enlazada | Recorrer las ventas en los dos sentidos |
| `ADL` | Arreglo de listas | Una celda por categoría, y en cada celda la lista de sus productos |
| `LDA` | Lista de árboles binarios de búsqueda | Mostrar ordenado y buscar más rápido dentro de cada categoría |
| `LDL` | Lista de listas | Ventas por cajero: la lista principal guarda legajo y nombre, la sublista sus ventas |
| `FILAS` | Colas | Manejo de las ventas de los empleados |
| `ARCHIVOS` | — | Persistencia en binario |
| `MENU` | — | Interfaz de consola y validación de acceso |

Son unas 2.800 líneas repartidas en 9 módulos, cada uno con su `.h`.

### Las tres estructuras de producto

Hay tres structs parecidos y la diferencia importa:

- `stRegistro`: el completo. Nombre, categoría, marca, código, precio, stock y estado.
- `stProducto`: igual pero sin categoría, porque en las estructuras compuestas la categoría ya
  está en la estructura principal y repetirla en cada nodo sería redundante.
- `stProductoFilas`: una versión recortada, con solo los campos que hacen falta para procesar
  una venta.

## Compilar y ejecutar

El proyecto se armó con Code::Blocks y MinGW; está el `.cbp` para abrirlo directamente.
También compila a mano:

```bash
cd ProyectoUltimo
gcc *.c -o gestion
./gestion
```

Para entrar como administrador, el usuario y la contraseña están definidos en `MENU.h`
(`NombreAdmin` y `ContraAdmin`). Son fijos y están en el código: es un trabajo académico sin
conexión, no un sistema con seguridad real.

La primera vez arranca sin datos y va creando los archivos `.bin` a medida que se cargan
productos y empleados.

## Decisiones

- **Baja lógica en lugar de borrado.** Un producto dado de baja mantiene su registro con
  `estado = 0`. Así el historial de ventas sigue teniendo sentido: si se borrara el producto,
  las ventas viejas quedarían apuntando a algo que ya no existe.
- **Códigos al azar verificados.** Al cargar un producto se genera un código aleatorio y se
  recorre el archivo para asegurarse de que no esté repetido.
- **Una estructura por tipo de consulta.** El arreglo de listas sirve para llegar rápido a una
  categoría; la lista de árboles, para mostrar ordenado dentro de ella. Fue el ejercicio de
  elegir la estructura según la operación, en vez de usar una sola para todo.
- **Persistencia binaria.** Se escribe el struct completo con `fwrite`. Es directo, pero ata el
  archivo al layout exacto de la estructura: cambiar un campo invalida los datos guardados.

## Limitaciones

Anotadas al revisar el proyecto tiempo después:

- **Usa `gets()`** en 16 lugares. Es una función eliminada del estándar C11 porque no controla
  el tamaño del buffer y permite desbordarlo. Lo correcto sería `fgets()`. No lo cambié porque
  no tengo forma de compilar y probar el proyecto ahora, y prefiero no tocar 16 llamadas sin
  poder verificarlo.
- **Credenciales de administrador fijas en el código**, sin cifrar.
- **La persistencia depende del layout de los structs.** Cualquier cambio en un campo rompe la
  compatibilidad con los archivos ya guardados.
- **Sin tests.** La verificación fue manual, recorriendo el menú.
- **`system("PAUSE")` y `fflush(stdin)`** atan el programa a Windows y son comportamiento no
  definido, respectivamente.

## Estado

Terminado y entregado como trabajo práctico. No lo mantengo: queda como referencia de cómo
implementaba estructuras de datos en ese momento. Lo que hoy haría distinto es casi todo lo que
está en la lista de limitaciones.
