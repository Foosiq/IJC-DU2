#include <stdlib.h>
#include "libtable.h"

void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t);
}

