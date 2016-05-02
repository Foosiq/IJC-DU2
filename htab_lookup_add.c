// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include <string.h>
#include <stdlib.h>
#include "libtable.h"
#include "stdio.h"

/* pridavanie slova/poctu vyskytov slova do tabulky */
htab_listitem *htab_lookup_add(htab_t *t, const char *key)
{
    /* zistime ci sa uz "key" nenachadza v tabulke */
    unsigned index = t->hash_fun_ptr(key, t->htab_size);

    htab_listitem *item = t->list[index];
    htab_listitem *tmp = NULL;

    /* ak zaznam neexistuje, vytvori sa */
    if (item == NULL)
    {
        /* alokujeme pamat */
        item = malloc(sizeof(htab_listitem));
        /* ak sa nepodari alokovat */
        if (item == NULL)
            return NULL;

        item->key = malloc(+strlen(key)+1/* \'0' */);
        /* ak sa nepodari alokovat */
        if (item->key == NULL)
        {
            free(item);
            return NULL;
        }

        /* pretoze sa pridal novy zaznam, inkrementujeme pocet zaznamov */
        t->n++;
        t->list[index] = item;

        /* nastavime jednotlive polozky struktury */
        item->data = 0;
        strcpy(item->key, key);
        item->next = NULL;
    }
    /* nasla sa potencionalna zhoda */
    else
    {
        /* hladame v zozname */
        while (item != NULL)
        {
            /* ak sa retazec zo struktury zhoduje s "key" -> zhoda */
            if (strcmp(item->key, key) == 0)
            {
                tmp = item;
                break;
            }
            /* v pripade ze sa nerovnaju sa hlada v dalsich zaznamoch */
            else
            {
                /* sucasna polozka sa ulozi do pomocneho ukazatela na polozku v zozname */
                tmp = item;
                /* do ukazatela na polozku v zozname sa ulozi ukazatel na dalsiu polozku zo zoznamu */
                item = item->next;
            }
        }

        /* ak sa v zozname nenasiel ziaden zaznam tak sa vytvori novy */
        if (tmp != item)
        {
            /* alokujeme pamat */
            item = malloc(sizeof(htab_listitem));
            /* ak sa nepodari alokovat */
            if (item == NULL)
                return NULL;

            item->key = malloc(+strlen(key)+1/* \'0' */);
            /* ak sa nepodari alokovat */
            if (item->key == NULL)
            {
                free(item);
                return NULL;
            }

            /* pretoze sa pridal novy zaznam, inkrementujeme pocet zaznamov */
            t->n++;

            tmp->next = item;
            /* nastavime jednotlive polozky struktury */
            item->data = 0;
            strcpy(item->key,key);
            item->next = NULL;
        }
    }

    return item;
}
