# Software-Manejo-de-Negocio
En este trabajo diseño un programa que se encarga del manejo de datos de una Tienda. Utilizando una cuenta única de administrador con variedad de opciones y otra de empleados.
PROYECTO SOFTWARE PARA NEGOCIO
En este trabajo se diseño un programa que se encarga del manejo de datos de un supermercado.
Utilizando una cuenta única de administrador para poder agregar, buscar, mostrar o modificar productos y acceder a los datos de los empleados.
Disponemos de distintas cuentas de usuario, que funcionan como empleados, donde el usuario/empleado puede realizar ventas y ver el stock. estas cuentas pueden ser modificadas por el admin.

Struct Registro:
Es la estructura donde guardamos todos los datos del producto, su nombre, su categoría, la marca, el código del producto que es generado al azar cuando se carga un producto por primera vez y verificado que no se repita, el precio, el stock, que sería la cantidad de unidades de dicho producto que dispone el inventario y el 
estado del registro que si es estado==0 significa que el producto está de baja en el inventario.

Struct producto:
Esta estructura es similar a stRegistro, con la particularidad de que no tiene el campo de categoría, esto es porque en algunas estructuras compuestas que utilizamos, el campo categoría se encuentra en las estructuras principales, mientras el resto de datos en las estructuras secundarias

Arreglo de listas simples:
Utilizamos el ADL para cuando el administrador quiere modificar un producto, la estructura compuesta se carga ni bien se selecciona en el menú de administrador la opción de modificar un producto, utilizando la celda del arreglo para guardar las categorías y la lista en la celda para guardar todos los productos que pertenezcan a la respectiva categoría.

Lista simple de árboles:
Al igual que el ADL, acá utilizamos la estructura principal, que sería la lista simple, para guardar el dato de la categoría y la estructura secundaria para guardar los otros datos del producto, pero la función de esta estructura compuesta es la de mostrar datos de forma ordenada y la búsqueda de los mismos, la busqueda de estos datos se facilitan con los árboles binarios de busqueda que se implementan como estructura secundaria

Listas dobles con Filas:
Con el uso de la nueva estructura stProductoFilas que recorta la cantidad de datos de la estructura original stRegistro implementamos una lista doblemente enlazada con el uso de filas para manejar las ventas de los empleados

Lista de Listas:
La lista de listas será utilizada con el fin de poder mostrar y buscar las ventas de cada empleado con respecto al día y el total vendido en el respectivo día, la lista principal está compuesta por el legajo del cajero y su nombre, y a este cajero se le asigna una sublista que guarda las ventas

Problemas presentados:
Al principio cuando ya tenia la idea concreta de lo que queria hacer para el proyecto, se me presentó un problema que fue tema de discusión, que es el uso de los archivos ¿como guardamos los productos, en un solo archivo que tenga todos los productos, o en muchos archivos que guarden los productos de una categoría en específico? Esta duda surgió al principio de todo, a los pocos dias me dimos cuenta que lo más cómodo para poder implementar las estructuras compuestas que iba a necesitar, era utilizar un archivo que contenga todos los productos.
Ahora una vez ya decidió que iba a utilizar un solo archivo que guarde todos los productos teniamos la duda de como hacer para abrir el archivo e ir guardando los datos en las estructuras filtrándose por la categoria, la solucion a ello llego bastante rapido, pensé en implementar un arreglo de strings como constante que guarde las categorías que utilizamos
Ya habiendo codeado casi todo el programa, llegaba la hora de testear que ande todo bien, y acá es donde muchas problemas empezaron a surgir, tenia loops en los menús, donde no entraba a alguna función y volvia al menu, por ejemplo. Y también se presentaron problema con la carga de los archivos, estaba cargando el archivo, pero a la hora de mostrarlos o de buscarlos, no había nada, esto se debia a pequeños errores donde no entraba a algunos bucles en las funciones de
carga de archivos o algunos errores de sintaxis, que no solo los hubo en la parte de archivos, en la de fila estuve cerca de olvidarme del uso del “*” en las funciones. en resumen, errores de sintaxis que hacían que el programa no se comporte como queria, luego de una amplia prueba pude determinar que el programa anda en su totalidad y está listo para ser utilizado. Y, tambien, para ser mejorado.
