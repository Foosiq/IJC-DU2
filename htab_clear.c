// htab_clear.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include <stdlib.h>
#include "libtable.h"

void htab_clear(htab_t *t)
{
    htab_listitem *item;

    /* cyklus v poli ukazatelov na zaznamy */
    for (unsigned i = 0; i < t->htab_size; ++i)
    {
        /* nastavenie na prvy prvok v poli zaznamov */
        item = t->list[i];

        /* cyklus pre vsetky polozky v jednotlivych poliach zaznamov */
        while (item != NULL)
        {
            htab_remove(t,item->key);
            item = item->next;
        }
    }
}