#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stddef.h>

typedef struct Str *String;

/**
 * @brief Tworzy nową strukturę typu String.
 *
 * @param chars zawartość
 * @param length długość
 * @return Nowy String o danej zawartości i danej długości.
 */
String sCreate_freeOnFail(char const *chars, size_t length);

/* Usuwa Stringa */
void sDelete(String string);

/* Zwraca zawartość Stringa. */
const char *sChars(String string);

/* Zwraca długość Stringa */
size_t sLength(String value);

#endif