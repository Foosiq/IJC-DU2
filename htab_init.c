// htab_init.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include "libtable.h"
#include "stdlib.h"
#include "stdio.h"


/* defaultna hashovacia funkcia */
unsigned int hash_function(const char *str, unsigned htab_size)
{
    unsigned int h=0;
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h % htab_size;
}

/* po uspesnej inicializacii funkcia vracia ukazatel na tabulku */
htab_t *htab_init(unsigned int size)
{
    /* dynamicka alokacia pamate pre strukturu, resp. tabulku */
    htab_t *table = malloc(sizeof(htab_t) + sizeof(htab_listitem)*size);

    /* v pripade ze sa nepodari alokovat pamat, funkcia vracia NULL */
    if (table == NULL)
        return NULL;

    /* nastavime size */
    table->htab_size = size;

    /* implicitne bude nastavena defaultna hashovacia funkcia */
    table->hash_fun_ptr = &hash_function;

    /* inicializacia jednotlivych poloziek zoznamu */
    for (unsigned i = 0; i < size; ++i)
        table->list[i] = NULL;

    return table;
}