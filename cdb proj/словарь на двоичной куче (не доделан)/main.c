#include <stdio.h>
#include <stdlib.h>

struct DictionaryElementValue
{
    char something[50];
};

struct DictionaryElement
{
    int key;
    struct DictionaryElementValue value;
};

void swap (struct DictionaryElement *Element1, struct DictionaryElement *Element2)
{
    struct DictionaryElement temp;
    temp = *Element1;
    *Element1 = *Element2;
    *Element2 = temp;
}

//добавление элемента в словарь
void InputDictionary (struct DictionaryElement *Dictionary, const size_t DictionarySize,
                      const struct DictionaryElement *value
                      )
{
    Dictionary[DictionarySize] = *value;
    size_t i = DictionarySize, j = (DictionarySize - 1) >> 1;
    while (i > 0 && Dictionary[i].key > Dictionary[j].key)
    {
        swap (&Dictionary[i], &Dictionary[j]);
        i = j;
        j = (i - 1) >> 1;
    }
}

struct DictionaryElement *FindDictionary(const struct DictionaryElement *Dictionary, const size_t DictionarySize,
                                         const int key
                                         )
{
    size_t i = 0;
    while ()
};

//ввод элемента с клавиатуры
void GetDictionaryElement (struct DictionaryElement *Element)
{
    scanf("%i %s", &Element->key, &Element->value.something);
}

//ввод словаря с клавиатуры
void GetDictionary (struct DictionaryElement *Dictionary, const size_t DictionarySize)
{
    size_t i = 0;
    for (i = 0; i < DictionarySize; ++i)
    {
        struct DictionaryElement temp;
        GetDictionaryElement(&temp);
        InputDictionary(Dictionary, i, &temp);
    }
}

void PutDictionaryElement (struct DictionaryElement *Element)
{
    printf("%i %s", Element->key, Element->value.something);
}

void PutDictionary (struct DictionaryElement *Dictionary, const size_t DictionarySize)
{
    size_t i = 0;
    for (i = 0; i < DictionarySize; ++i)
    {
        PutDictionaryElement(&Dictionary[i]);
        printf("\n");
    }
}

int main()
{
    size_t n;
    scanf("%i", &n);
    struct DictionaryElement Dictionary[n];
    GetDictionary(Dictionary, n);
    return 0;
}
