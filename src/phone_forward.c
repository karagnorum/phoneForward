#include "phone_forward.h"
#include "vector.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/**
 * Struktura zawierająca przekierowania.
 * I-ty prefiks w Vectorze przekierowanych prefiksów jest przekierowany na
 * i-ty prefiks w Vectorze zastępników.
 */
typedef struct PhoneForward
{
    Vector *forwarded;    ///< przekierowane prefiksy
    Vector *replacements; ///< zastępniki
} PhoneForward;

/**
 * @brief Struktura reprezentująca ciąg numerów.
 *
 */
typedef struct PhoneNumbers
{
    Vector *elements; ///< numery
} PhoneNumbers;

static const char CHAR10 = '9' + 1;
static const char CHAR11 = '9' + 2;

static char isAllowedInCovertedNumber(char c)
{
    return isdigit(c) || c == CHAR10 || c == CHAR11;
}

static void assertConvertedNumber(char const *chars)
{
    assert(chars != NULL && chars[0] != 0);
    int i = 0;
    while (isAllowedInCovertedNumber(chars[i]))
    {
        i++;
    }
    assert(chars[i] == 0);
}

PhoneForward *phfwdNew(void)
{
    PhoneForward *result = (PhoneForward *)malloc(sizeof(PhoneForward));
    if (result != NULL)
    {
        result->forwarded = vCreate(vDEFAULT_INITIAL_CAPACITY);
        if (result->forwarded == NULL)
            goto vectorCreationFailed;
        result->replacements = vCreate(vDEFAULT_INITIAL_CAPACITY);
        if (result->replacements == NULL)
        {
            vDestruct(result->forwarded);
            goto vectorCreationFailed;
        }
    }

    return result;

vectorCreationFailed:
    free(result);
    return NULL;
}

static char isAllowedInNumber(char c)
{
    return isdigit(c) || c == '*' || c == '#';
}

static bool isNumber(char const *chars, size_t *length)
{
    if (chars == NULL || chars[0] == 0)
        return false;

    size_t i = 0;
    while (isAllowedInNumber(chars[i]))
    {
        i++;
    }
    if (chars[i] != 0)
        return false;
    *length = i;

    assert(*length == strlen(chars));
    return true;
}

/**
 * @brief Zastępuje wystąpienia * i # w danym numerze przez odpowiednio '9' + 1 i '9' + 2.
 *
 * @param[in] num dany numer
 * @return Nowy numer uzyskany poprzez podmienienie * i # lub NULL, jeśli nie udało się zaalokować pamięci.
 */
static String convertNumber(char const *num, size_t numLength)
{
    assert(numLength == strlen(num));

    char *resultString = (char *)malloc(numLength + 1);
    if (resultString == NULL)
        return NULL;

    for (size_t i = 0;; i++)
    {
        if (isdigit(num[i]))
            resultString[i] = num[i];
        else if (num[i] == '*')
            resultString[i] = CHAR10;
        else if (num[i] == '#')
            resultString[i] = CHAR11;
        else if (num[i] == 0)
        {
            resultString[i] = 0;
            break;
        }
        else
        {
            assert(false);
            return NULL;
        }
    }

    assert(strlen(resultString) == numLength);
    assertConvertedNumber(resultString);
    String result = sCreate_freeOnFail(resultString, numLength);
    return result;
}

static String unconvertNumber(String converted)
{
    const char *num = sChars(converted);
    assertConvertedNumber(num);
    char *resultString = (char *)malloc(sLength(converted) + 1);
    if (resultString == NULL)
        return NULL;

    for (size_t i = 0;; i++)
    {
        if (isdigit(num[i]))
            resultString[i] = num[i];
        else if (num[i] == CHAR10)
            resultString[i] = '*';
        else if (num[i] == CHAR11)
            resultString[i] = '#';
        else if (num[i] == 0)
        {
            resultString[i] = 0;
            break;
        }
        else
        {
            assert(false);
            return NULL;
        }
    }

    assert(strlen(resultString) == sLength(converted));
    String result = sCreate_freeOnFail(resultString, sLength(converted));
    return result;
}

/* Zgłasza błąd, jeśli Vector nie jest posortowany. */
static void assertSorted(Vector *vector)
{
    // for (size_t i = 0; i < vSize(vector); i++)
    //     assertConvertedNumber(vGetCharsAtI(vector, i));

    for (size_t i = 0; i != SIZE_MAX && (i + 1 < vSize(vector)); i++)
    {
        assert(strcmp(vGetCharsAtI(vector, i), vGetCharsAtI(vector, i + 1)) < 0);
    }
}

#define eq(x, y) strcmp(x, y) == 0

/**
 * @brief Wstawia numer do posortowanego Vectora tak, żeby Vector pozostał posortowany.
 *
 * @param[in] sortedVector wskaźnik na posortowany leksykograficznie Vector
 * @param[in] num numer do wstawienia
 * @param[out] numAlreadyPresent prawda, jeśli numer był już w wektorze
 * @return Indeks, pod którym znajduje się numer po wykonaniu procedury lub SIZE_MAX, jeśli wystąpił błąd.
 */
static size_t insertSorted(Vector *sortedVector, String num, bool *numAlreadyPresent)
{
    assertSorted(sortedVector);
    assert(num != NULL && sChars(num) != NULL);

    int comparison = 1;
    size_t i = -1;
    *numAlreadyPresent = false;

    while (comparison > 0)
    {
        i++;
        if (i == vSize(sortedVector))
            break;
        comparison = strcmp(sChars(num), vGetCharsAtI(sortedVector, i));
    }
    *numAlreadyPresent = comparison == 0;

    if (*numAlreadyPresent || vInsertBeforeI(sortedVector, num, i))
    {
        assertSorted(sortedVector);
        assert(eq(vGetCharsAtI(sortedVector, i), sChars(num)));
        return i;
    }
    return SIZE_MAX;
}

void phfwdDelete(PhoneForward *pf)
{
    if (pf != NULL)
    {
        vDestruct(pf->forwarded);
        vDestruct(pf->replacements);
        free(pf);
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2)
{
    size_t num1Length, num2Length;
    if (pf == NULL || !isNumber(num1, &num1Length) || !isNumber(num2, &num2Length) || eq(num1, num2))
        return false;

    String convertedNum1 = convertNumber(num1, num1Length);
    if (convertedNum1 == NULL)
        return false;
    String convertedNum2 = convertNumber(num2, num2Length);
    if (convertedNum2 == NULL)
    {
        sDelete(convertedNum1);
        return false;
    }

    bool num1AlreadyPresent;
    size_t i = insertSorted(pf->forwarded, convertedNum1, &num1AlreadyPresent);
    if (i == SIZE_MAX)
    {
        sDelete(convertedNum1);
        goto fail;
    }

    if (num1AlreadyPresent)
    {
        sDelete(convertedNum1);
        vSetI(pf->replacements, i, convertedNum2);
        return true;
    }
    if (!vInsertBeforeI(pf->replacements, convertedNum2, i))
    {
        vDeleteElements(pf->forwarded, i, i + 1);
        goto fail;
    }
    return true;

fail:
    sDelete(convertedNum2);
    return false;
}

/**
 * @brief Tworzy pustą strukturę PhoneNumbers.
 *
 * @return Wskaźnik na utworzoną strukturę.
 */
static PhoneNumbers *phnumNew(void)
{
    PhoneNumbers *result = (PhoneNumbers *)malloc(sizeof(PhoneNumbers));

    if (result != NULL)
    {
        result->elements = vCreate(1);
        if (result->elements == NULL)
        {
            free(result);
            return NULL;
        }
    }

    return result;
}

/* Zwraca wartość logiczną zdania "napis A jest prefiksem napisu B". */
static bool AIsPrefixOfB(char const *A, char const *B)
{
    assert(A != NULL && B != NULL);

    size_t i = 0;

    for (; A[i] != 0 && A[i] == B[i]; i++)
    {
    }

    return A[i] == 0;
}

/**
 * @brief Znajduje przedział indeksów, na którym elementy danego posortowanego Vectora mają prefiks A.
 *
 * @param[in] sortedStrings posortowany leksykograficznie Vector
 * @param[in] A dany prefiks
 * @param[out] firstIdx najmniejszy indeks ze znalezionego przedziału
 * @param[out] endIdx (największy indeks ze znalezionego przedziału) + 1
 */
static void findStringsWithPrefixA(Vector *sortedStrings,
                                   String A, size_t *firstIdx, size_t *endIdx)
{
    assertSorted(sortedStrings);

    size_t i = 0;
    while (i < vSize(sortedStrings) && !AIsPrefixOfB(sChars(A), vGetCharsAtI(sortedStrings, i)))
    {
        i++;
    }
    *firstIdx = i;
    while (i < vSize(sortedStrings) && AIsPrefixOfB(sChars(A), vGetCharsAtI(sortedStrings, i)))
    {
        i++;
    }
    *endIdx = i;
}

void phfwdRemove(PhoneForward *pf, char const *num)
{
    if (pf == NULL)
        return;

    size_t length;
    if (!isNumber(num, &length))
        return;
    String converted = convertNumber(num, length);
    if (converted == NULL)
        return;

    size_t i, j;
    findStringsWithPrefixA(pf->forwarded, converted, &i, &j);
    sDelete(converted);
    assert(i <= j);
    if (i != j)
    {
        vDeleteElements(pf->forwarded, i, j);
        assertSorted(pf->forwarded);
        vDeleteElements(pf->replacements, i, j);
    }
}

/**
 * @brief Zastępuje prefiks dlugości n danego napisu przez nowy prefiks.
 *
 * @param[in] num numer, którego prefiks zostaje zastąpiony
 * @param[in] n długość prefiksu do zastąpienia
 * @param[in] newPrefix nowy prefiks
 * @return Nowy numer powstały poprzez zastąpienie danego prefiksu przez nowy prefiks lub NULL, jeśli nie udało się zaalokować pamięci.
 */
static String replacePrefix(String num, size_t n, String newPrefix)
{
    char const *chars = sChars(num), *newChars = sChars(newPrefix);

    assertConvertedNumber(chars);
    assertConvertedNumber(newChars);
    assert(sLength(num) == strlen(chars) && sLength(newPrefix) == strlen(newChars));

    size_t resultLength = sLength(num) - n + sLength(newPrefix);
    assert(resultLength > 0);
    char *resultChars = (char *)malloc((resultLength + 1) * sizeof(char));
    if (resultChars == NULL)
        return NULL;

    size_t i = 0;
    for (; newChars[i] != 0; i++)
    {
        resultChars[i] = newChars[i];
    }
    char const *unchangedPart = chars + n;
    strcpy(resultChars + i, unchangedPart);

    assert(resultChars == NULL || AIsPrefixOfB(newChars, resultChars));
    return sCreate_freeOnFail(resultChars, resultLength);
}

/**
 * @brief Znajduje najdłuższy prefiks numeru w posortowanym Vectorze.
 *
 * @param[in] sortedVector posortowany leksykograficznie Vector
 * @param[in] num dany numer
 * @return Największy indeks, na którym znajduje się prefix numeru @p num lub SIZE_MAX, jeśli takiego nie ma.
 */
static size_t findLongestPrefixOfNumber(Vector *sortedVector, char const *num)
{
    assertConvertedNumber(num);
    assertSorted(sortedVector);

    size_t i = vSize(sortedVector) - 1;

    while (i != SIZE_MAX && !AIsPrefixOfB(vGetCharsAtI(sortedVector, i), num))
    {
        i--;
    }

    return i;
}

static bool unconvertElements(Vector *vector)
{
    for (size_t i = 0; i < vSize(vector); i++)
    {
        String unconverted = unconvertNumber(vGetI(vector, i));
        if (unconverted == NULL)
            return false;
        vSetI(vector, i, unconverted);
    }
    return true;
}

static PhoneNumbers *memFail(PhoneNumbers *pnum)
{
    phnumDelete(pnum);
    return NULL;
}

static bool getStr(PhoneForward const *pf, String number, PhoneNumbers *resultSequence)
{

    String result = number, changedNumber = NULL;

    size_t i = findLongestPrefixOfNumber(pf->forwarded, sChars(number));
    if (i != SIZE_MAX)
    {
        String prefix = vGetI(pf->forwarded, i), newPrefix = vGetI(pf->replacements, i);
        changedNumber = replacePrefix(result, sLength(prefix), newPrefix);
        result = changedNumber;
    }

    if (result == NULL)
        goto fail;
    String unconverted = unconvertNumber(result);
    if (unconverted == NULL)
        goto fail;
    vAdd(resultSequence->elements, unconverted);
    if (changedNumber != NULL)
        sDelete(changedNumber);
    return true;

fail:
    if (changedNumber != NULL)
        sDelete(changedNumber);
    return false;
}

PhoneNumbers *phfwdGet(PhoneForward const *pf, char const *num)
{
    if (pf == NULL)
        return NULL;

    size_t numLength;
    PhoneNumbers *resultSequence = phnumNew();
    if (resultSequence == NULL || !isNumber(num, &numLength))
        return resultSequence;

    String number = convertNumber(num, numLength);
    if (number == NULL)
        goto fail;

    bool success = getStr(pf, number, resultSequence);
    sDelete(number);
    if (!success)
        goto fail;
    return resultSequence;

fail:
    phnumDelete(resultSequence);
    return NULL;
}

static bool tryReplacement(int i, PhoneForward const *pf, String convertedNum2, Vector *result, char const *num2)
{
    String replacement = vGetI(pf->replacements, i);
    if (AIsPrefixOfB(sChars(replacement), sChars(convertedNum2)))
    {
        String num1 = replacePrefix(convertedNum2, sLength(replacement), vGetI(pf->forwarded, i));
        if (num1 == NULL)
            return false;

        PhoneNumbers *pnum = phnumNew();
        if (pnum == NULL || !getStr(pf, num1, pnum))
        {
            phnumDelete(pnum);
            sDelete(num1);
            return false;
        }
        bool good = eq(phnumGet(pnum, 0), num2);
        phnumDelete(pnum);
        if (!good)
        {
            sDelete(num1);
            return true;
        }

        bool num1AlreadyPresent;
        size_t idx = insertSorted(result, num1, &num1AlreadyPresent);
        if (num1AlreadyPresent)
            sDelete(num1);
        if (idx == SIZE_MAX)
        {
            sDelete(num1);
            return false;
        }
    }
    return true;
}

PhoneNumbers *phfwdGetReverse(PhoneForward const *pf, char const *num2)
{
    if (pf == NULL)
        return NULL;

    size_t num2Length;
    PhoneNumbers *resultSequence = phnumNew();
    if (resultSequence == NULL || !isNumber(num2, &num2Length))
        return resultSequence;

    Vector *result = resultSequence->elements;
    String convertedNum2 = convertNumber(num2, num2Length);
    if (convertedNum2 == NULL)
        return memFail(resultSequence);

    bool selfForwarded = false;
    PhoneNumbers *pnum = phfwdGet(pf, num2);
    if (pnum == NULL)
        goto fail;
    selfForwarded = eq(phnumGet(pnum, 0), num2);
    if (selfForwarded)
        vAdd(result, convertedNum2);
    phnumDelete(pnum);

    for (size_t i = 0; i < vSize(pf->replacements); i++)
    {
        if (!tryReplacement(i, pf, convertedNum2, result, num2))
            goto fail;
    }

    assertSorted(result);
    if (!unconvertElements(result))
        return memFail(resultSequence);
    if (!selfForwarded)
        sDelete(convertedNum2);
    return resultSequence;

fail:
    if (!selfForwarded)
        sDelete(convertedNum2);
    return memFail(resultSequence);
}

PhoneNumbers *phfwdReverse(PhoneForward const *pf, char const *num2)
{
    if (pf == NULL)
        return NULL;

    size_t num2Length;
    PhoneNumbers *resultSequence = phnumNew();
    if (resultSequence == NULL || !isNumber(num2, &num2Length))
        return resultSequence;

    Vector *result = resultSequence->elements;
    String convertedNum2 = convertNumber(num2, num2Length);
    if (convertedNum2 == NULL)
        return memFail(resultSequence);
    vAdd(result, convertedNum2);

    for (size_t i = 0; i < vSize(pf->replacements); i++)
    {
        String replacement = vGetI(pf->replacements, i);
        if (AIsPrefixOfB(sChars(replacement), num2))
        {
            String num1 = replacePrefix(convertedNum2, sLength(replacement), vGetI(pf->forwarded, i));
            if (num1 == NULL)
                return memFail(resultSequence);

            bool num1AlreadyPresent;
            size_t idx = insertSorted(result, num1, &num1AlreadyPresent);
            if (num1AlreadyPresent)
                sDelete(num1);
            if (idx == SIZE_MAX)
            {
                sDelete(num1);
                return memFail(resultSequence);
            }
        }
    }

    assertSorted(result);
    if (!unconvertElements(result))
        return memFail(resultSequence);
    // printVector(result);
    return resultSequence;
}

void phnumDelete(PhoneNumbers *pnum)
{
    if (pnum != NULL)
    {
        vDestruct(pnum->elements);
        free(pnum);
    }
}

char const *phnumGet(PhoneNumbers const *pnum, size_t idx)
{
    if (pnum != NULL && idx < vSize(pnum->elements))
        return vGetCharsAtI(pnum->elements, idx);
    return NULL;
}
