#include "lista.h"
#include <stdlib.h>

/* Definiciones para el nodo */
typedef struct nodo{
	void *dato;
	struct nodo *siguiente;
}nodo_t;

nodo_t *nodo_crear(void *dato){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(!nodo) return NULL;
	nodo->dato = dato;
	nodo->siguiente = NULL;
	return nodo;
}

/* Primitivas de la lista */
struct lista{
	nodo_t *primero;
	nodo_t *ultimo;
	size_t largo;
};

lista_t *lista_crear(){
	lista_t *lista = malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->primero = lista->ultimo = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->primero == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t *nodo = nodo_crear(dato);
	if(!nodo) return false;
	if(lista_esta_vacia(lista)){
		lista->ultimo = nodo;
	}else{
		nodo->siguiente = lista->primero;
	}
	lista->primero = nodo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t *nodo = nodo_crear(dato);
	if(!nodo) return false;
	if(lista_esta_vacia(lista)){
		lista->primero = nodo;
	}else{
		lista->ultimo->siguiente = nodo;
	}
	lista->ultimo = nodo;
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	nodo_t *ptr = lista->primero;
	void *dato = lista_ver_primero(lista);
	lista->primero = lista->primero->siguiente;
	if(lista_esta_vacia(lista)) lista->ultimo = NULL;
	free(ptr);
	lista->largo--;
	return dato;
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(!lista_esta_vacia(lista)){
		void *dato = lista_borrar_primero(lista);
		if(destruir_dato) destruir_dato(dato);
	}
	free(lista);
}

/* Primitivas del iterador externo */
struct lista_iter{
	lista_t *lista;
	nodo_t *actual;
	nodo_t *anterior;
};

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t *iter = malloc(sizeof(lista_iter_t));
	if(!iter) return NULL;
	iter->lista = lista;
	iter->actual = lista->primero;
	iter->anterior = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->siguiente;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	nodo_t *nodo = nodo_crear(dato);
	if(!nodo) return false;
	if(lista_esta_vacia(iter->lista)){
		iter->lista->primero = nodo;
		iter->lista->ultimo = nodo;
	}else{
		if(!iter->anterior){
			nodo->siguiente = iter->lista->primero;
			iter->lista->primero = nodo;
		}else if(lista_iter_al_final(iter)){
			iter->lista->ultimo->siguiente = nodo;
			iter->lista->ultimo = nodo;
		}else{
			iter->anterior->siguiente = nodo;
			nodo->siguiente = iter->actual;
		}
	}
	iter->actual = nodo;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	nodo_t *ptr = iter->actual;
	void *dato = ptr->dato;
	if(!iter->anterior){
		iter->lista->primero = iter->actual->siguiente;
	}else{
		iter->anterior->siguiente = iter->actual->siguiente;
	}
	iter->actual = iter->actual->siguiente;
	if(lista_iter_al_final(iter)) iter->lista->ultimo = iter->anterior;
	iter->lista->largo--;
	free(ptr);
	return dato;
}

/* Primitiva del iterador interno */
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	nodo_t *ptr = lista->primero;
	while(ptr && visitar(ptr->dato, extra)){
		ptr = ptr->siguiente;
	}
}