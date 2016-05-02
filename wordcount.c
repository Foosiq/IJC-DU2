// wordcount.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include <stdio.h>
#include "libtable.h"
#include "io.c"

#define MAX_WORD_SIZE (128)

/* vypisuje slovo a jeho pocet vyskytov */
void print_word(const char *word, unsigned data)
{
        printf("%s\t%d\n", word, data);
}

/*
 * Hashovacia funkcia, pouzita pre otestovanie funkcie htab_init2()
 *
unsigned long hash(unsigned char *str, unsigned htab_size)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; *//* hash * 33 + c *//*

    return hash % htab_size;
}*/

int main()
{
    /* ako zdroj som pouzil diskusiu: http://www.antimoon.com/forum/t14464.htm , kde sa ludia bavili o tom, ze
     * existuju knihy v ktorych sa nachadza aj cez 10 000 roznych slov, najvyssie konkretne cislo v tejto diskusii
     * bolo cislo 10419 -> moje rozhodnutie */
    htab_t *table = htab_init(10419);
    htab_listitem *item;

    /* testoval som funkcnost funkcie s inou nez nasou implicitnou hashovacou funkciou, a zda sa ze funguje */
//    htab_t *table = htab_init2(10419, &hash);

    char buffer[MAX_WORD_SIZE];

    /* nacitavame slova zo standardneho vstupu po EOF */
    while (get_word(buffer, MAX_WORD_SIZE-1, stdin) != EOF)
    {
        /* nacitane slovo spracujeme do tabulky */
        item = htab_lookup_add(table, buffer);
        /* inkrementujeme jeho pocet vyskytov */
        item->data++;
    }

    htab_foreach(table, &print_word);

    htab_free(table);

    return 0;
}