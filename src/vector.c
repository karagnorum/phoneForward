#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define RESIZE_AMOUNT 128

/**
 * @brief Struktura przechowaująca napisy.
 * Sruktura analogiczna do Vectora w STL
 * z funkcjami wstawiania (jak do listy) oraz usuwania
 * elementów.
 */

typedef struct Vector
{
    String *arr;     ///< tablica z wartościami
    size_t capacity; ///< długość tablicy
    size_t size;     ///< liczba elementów
} Vector;

String vGetI(Vector const *vector, size_t i)
{
    assert(i < vSize(vector));
    return vector->arr[i];
}

char const *vGetCharsAtI(Vector const *vector, size_t i)
{
    return sChars(vGetI(vector, i));
}

void vSetI(Vector *vector, size_t i, String value)
{
    assert(i < vSize(vector));
    sDelete(vector->arr[i]);
    vector->arr[i] = value;
    assert(vGetI(vector, i) == value);
}

static bool resize(Vector *vector)
{
    size_t newCapacity = vector->capacity + RESIZE_AMOUNT;
    String *longerArr = realloc(vector->arr, sizeof(String) * newCapacity);
    if (longerArr == NULL)
        return false;
    vector->capacity = newCapacity;
    vector->arr = longerArr;
    return true;
}

void vDestruct(Vector *vector)
{
    for (size_t i = 0; i < vSize(vector); i++)
    {
        sDelete(vGetI(vector, i));
    }
    free(vector->arr);
    free(vector);
}

bool vInsertBeforeI(Vector *vector, String value, size_t i)
{
    if (vector->size == vector->capacity)
    {
        bool resizeSuccessful = resize(vector);
        if (!resizeSuccessful)
            return false;
    }

    String *placeForValue = vector->arr + i;
    if (i < vector->size)
        memcpy(placeForValue + 1, placeForValue, (vector->size - i) * sizeof(String));
    vector->size++;

    assert(i < vector->size);
    vector->arr[i] = value;

    return true;
}

bool vAdd(Vector *vector, String value)
{
    return vInsertBeforeI(vector, value, vector->size);
}

void vDeleteElements(Vector *vector, size_t firstIdx, size_t endIdx)
{
    assert(firstIdx < vSize(vector));
    assert(endIdx > 0 && endIdx <= vSize(vector));
    assert(firstIdx < endIdx);
    assert(vector->size >= endIdx - firstIdx);

    for (size_t i = firstIdx; i < endIdx; i++)
    {
        sDelete(vector->arr[i]);
    }
    String *source = vector->arr + endIdx;
    String *destination = vector->arr + firstIdx;
    memcpy(destination, source, (vector->size - endIdx) * sizeof(String));
    vector->size -= endIdx - firstIdx;
}

size_t vSize(Vector const *vector)
{
    return vector->size;
}

bool vIsEmpty(Vector const *vector)
{
    return vector->size == 0;
}

Vector *vCreate(size_t initialCapacity)
{
    assert(initialCapacity != 0);

    Vector *result = (Vector *)malloc(sizeof(Vector));
    if (result != NULL)
    {
        result->size = 0;
        result->capacity = initialCapacity;
        result->arr = (String *)malloc(initialCapacity * sizeof(String));
        if (result->arr == NULL)
        {
            free(result);
            result = NULL;
        }
    }

    return result;
}
