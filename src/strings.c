#include "strings.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Struktura przechowująca ciąg znaków i jego długość.
 *
 */
struct Str
{
    char const *chars; ///< ciąg znaków
    size_t length;     ///< długość
};

void sDelete(String string)
{
    assert(string != NULL);
    free((void *)string->chars);
    free(string);
}

size_t sLength(String string)
{
    return string->length;
}

char const *sChars(String string)
{
    return string->chars;
}

static String sCreate(char const *chars, size_t length)
{
    String result = (String)malloc(sizeof(struct Str));
    if (result != NULL)
    {
        result->chars = chars;
        result->length = length;
    }
    return result;
}

String sCreate_freeOnFail(char const *chars, size_t length)
{
    String result = sCreate(chars, length);
    if (result == NULL)
        free((void *)chars);
    return result;
}