// htab_remove.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include <stdlib.h>
#include "string.h"
#include "libtable.h"
#include "stdio.h"

/* vyhladava polozku v tabulke podla hladaneho kluca, v pripade zhody ju zmaze */
void htab_remove(htab_t *t, char *key)
{
    htab_listitem *item;
    htab_listitem *tmp_item;

    /* cyklus v poli ukazatelov na jednotlive polia zaznamov */
    for (unsigned i = 0; i < t->htab_size; ++i)
    {
        tmp_item = item = t->list[i];

        /* cyklus jednotlivych poloziek v poli zaznamov */
        while(item != NULL)
        {
            /* ak sa nasla zhoda */
            if (strcmp(item->key, key) == 0)
            {
                /* ak sa polozka nachadza na zaciatku pola */
                if (item == tmp_item)
                    /* zaciatok pola sa nastavi na dalsiu polozku v zozname */
                    t->list[i] = item->next;

                /* nastavime aby predosla polozka, ktora ukazovala na polozku ktoru ideme zmazat,
                 * bude ukazovat az na nasledujucu polozku v zozname */
                tmp_item->next = item->next;

                /* uvolnenie dynamicky alokovane pamate v polozke ktoru chceme odstranit */
                free(item->key);
                free(item);

                break;
            }
            /* ak sa nezhoduje, hladame dalej */
            else
            {
                /* pomocny ukazatel na zaznam nastavime na prave pouzivanu polozku */
                tmp_item = item;
                /* ukazatel na polozku v poli zaznamov nastavime na dalsiu polozku v poli zaznamov */
                item = item->next;
            }
        }
    }
}
