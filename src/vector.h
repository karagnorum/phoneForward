#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "strings.h"
#include <stdbool.h>

struct Vector;
typedef struct Vector Vector;

#define vDEFAULT_INITIAL_CAPACITY 10

char const *vGetCharsAtI(Vector const *vector, size_t i);

/* Zwraca napis znajdujący się pod indeksem i. */
String vGetI(Vector const *vector, size_t i);

/* Ustawia napis na indeksie i */
void vSetI(Vector *vector, size_t i, String value);

/**
 * @brief Dodaje napis na koniec wektora.
 *
 * @param vector dany Vector
 * @param value napis do wstawienia
 * @return Prawda, gdy operacja się powiodła (nie wystąpił błąd).
 */
bool vAdd(Vector *vector, String value);

/* Zwraca rozmiar Vectora (największy indeks + 1). */
size_t vSize(Vector const *vector);

/* Zwraca Vector rozmiaru 0 o danej początkowej pojemności. */
Vector *vCreate(size_t initialCapacity);

/*
 * Usuwa z pamięci wszystkie arr[i], takie że i jest z przedziału [firstIdx, endIdx - 1]
 * (indeksy elementów o indeksie co najmniej endIdx zostają zmiejszone o długość przedziału).
 */
void vDeleteElements(Vector *vector, size_t firstIdx, size_t endIdx);

/**
 * @brief Wstawia dany napis przed indeksem i (po wstawieniu jest on na indeksie i).
 *
 * @param[out] vector Vector, do którego wstawiamy
 * @param[in] value dany napis
 * @param[in] i indeks na którym ma się znaleźć dany napis
 * @return Prawda, gdy operacja się powiodła (nie wystąpił błąd).
 */
bool vInsertBeforeI(Vector *vector, String value, size_t i);

/* Usuwa Vector. */
void vDestruct(Vector *vector);

/* Zwraca true, gdy Vector jest pusty. */
bool vIsEmpty(Vector const *vector);

#endif