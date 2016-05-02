// libtable.h
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

/* polozka z tabulky zaznamov */
typedef struct htab_listitem_s
{
    unsigned int data;              /* počet vyskytov */
    struct htab_listitem_s *next;   /* ukazatel na další záznam */
    char *key;                      /* ukazatel na dynamicky alokovany retazec */
} htab_listitem;

/* tabulka zaznamov */
typedef struct htab_t_s
{
    unsigned int n;                                         /* pocet zaznamov */
    unsigned int (*hash_fun_ptr)(const char*, unsigned);    /* ukazatel na hashovaciu funkciu */
    unsigned int htab_size;                                 /* velkost  pola ukazatelov */
    struct htab_listitem_s *list[];                         /* pole ukazatelov na zaznamy */
} htab_t;

/* defaultna hashovacia funkcia */
unsigned int hash_function(const char *str, unsigned htab_size);

/* inicializacia tabulky */
htab_t *htab_init(unsigned int size);

/* inicializacia tabulky s urcenim hashovacej funkcie */
htab_t *htab_init2(unsigned int size, unsigned int (*hashfn)(const char*, unsigned));

/* pridavanie slova/poctu vyskytov slova do tabulky */
htab_listitem *htab_lookup_add(htab_t *t, const char *key);

/* pre kazdu polozku v tabulke sa zavola funkcia pouzita v druhom parametre tejto funkcie */
void htab_foreach(htab_t *t, void (*function)(const char*, unsigned));

/* vyhladava polozku v tabulke podla hladaneho kluca, v pripade zhody ju zmaze */
void htab_remove(htab_t *t, char *key);

/* vymaze vsetky zoznamy zaznamov z tabulky */
void htab_clear(htab_t *t);

/* vymaze/uvolni tabulku z pamati */
void htab_free(htab_t *t);