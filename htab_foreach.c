// TODO INFO

#include "libtable.h"
#include "stdio.h"

/* pre kazdu polozku v tabulke sa zavola funkcia pouzita v druhom parametre tejto funkcie */
void htab_foreach(htab_t *t, void (*function)(const char*, unsigned))
{
    htab_listitem *item;

    /* cyklime v poli ukazatelov na jednotlive polia zaznamov */
    for (unsigned i = 0; i < t->htab_size; ++i)
    {
        item = t->list[i];

        /* volame funkciu na jednotlive polozky pola zaznamov */
        while(item != NULL)
        {
            function(item->key, item ->data);
            item = item->next;
        }
    }
}

