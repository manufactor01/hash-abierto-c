#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stddef.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos*/
struct lista;
typedef struct lista lista_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista
// Post: devuelve una lista nueva vacía
lista_t *lista_crear(void);

// Devuelve true o false, si la lista tiene o no elementos
// Pre: la lista fue creda
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// principio de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al principio de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// final de la lista
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, saca el primero
// de la lista, se devuelve el valor del primero, si está vacía devuelve NULL
// Pre: la lista fue creada
// Post: se devolvió e primer elementos de la lista, cuando no está vacía
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene elementos
// se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada
// Post: se devolvió el primer elemento de la lista, cuando no está vacía
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene elementos
// se devuelve el valor del último, si está vacía devuelve NULL.
// Pre: la lista fue creada
// Post: se devolvió el primer elemento de la lista, cuando no está vacía
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista
// Pre: la lista fue creada
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Primitiva del iterador interno
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Primitivas del iterador externo
typedef struct lista_iter lista_iter_t;

// Recibe la referencia de una lista y devuelve el iterador a esa lista
// Pre: la lista fue creada
// Post: se devolvió el iterador
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador, si está al final, devuelve false
// Pre: el iterador fue creado
// Pos: devuelve true si puede actualizar el actual
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato del actual elemento al que apunta el iterador
// Pre: el iterador fue creado
// Post: devuelve el dato del actual, NULL si el iterador está al final
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve false si el actual no es NULL, true en caso contrario
// Pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: el iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista, en la posición en la que se encuentra el iterador. Si
// el iterador fue creado, es equivalente a lista insertar primero (actualiza el primer
// elemento de la lista). Si está al final, es equivalente a lista insertar último (actualiza
// el último elemento de la lista). En caso de resolverse correctamente, devuelve true, false
// si hay errores.
// Pre: el iterador fue creado
// Post: devuelve true si se insertó correctamente, false en caso contrario
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el elemento al que apunta el iterador, y devuelve el dato almacenado. Si el iterador
// fue creado, es equivalente a lista borrar primero. Si el iterador está al final
// devuelve NULL
// Pre: el iterador fue creado
// Post: devolvió el dato que tenía almacenado el actual, la lista tiene un elemento menos
void *lista_iter_borrar(lista_iter_t *iter);

// Pruebas del alumno
void pruebas_lista_alumno();

#endif 