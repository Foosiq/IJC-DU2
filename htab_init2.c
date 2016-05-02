// htab_init2.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include "libtable.h"
#include "stdlib.h"
#include "stdio.h"

/* inicializacia tabulky s urcenim hashovacej funkcie */
htab_t *htab_init2(unsigned int size, unsigned int (*hashfn)(const char*, unsigned))
{
    /* dynamicka alokacia pamate pre strukturu, resp. tabulku */
    htab_t *table = malloc(sizeof(htab_t) + sizeof(htab_listitem)*size);

    /* v pripade ze sa nepodari alokovat pamat, funkcia vracia NULL */
    if (table == NULL)
        return NULL;

    /* nastavime size */
    table->htab_size = size;

    /* nastavenie hashovacej funkcie */
    table->hash_fun_ptr = hashfn;

    /* inicializacia jednotlivych poloziek zaznamu */
    for (unsigned i = 0; i < size; ++i)
        table->list[i] = NULL;

    return table;
}


