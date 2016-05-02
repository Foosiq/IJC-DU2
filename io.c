// io.c
// Řešení IJC-DU2, příklad 2), 28.4
// Autor: Andrej Dzilský, FIT
// Přeloženo: gcc 5.3.1

#include <stdio.h>
#include <ctype.h>

int word_is_longer = 0;

/* nacita slovo zo suboru, vracia pocet nacitanych znakov alebo EOF */
int get_word(char *s, int max, FILE *f)
{
    /* osetrenie, v pripade chyby funkcia vracia -1 */
    if (s == NULL || f == NULL || max > 254)
        return -1;

    int character = 0;
    int index = 0;

    /* nacitavame znaky po EOF
     * 1. podmienka cyklu je vytvorena kvoli zahadzovaniu znakov
     * vo vnorenom cykle zo slova dlhsieho ako "max" pocet znakov */
    while(/*isspace(character) == 0 && */(character = fgetc(f)) != EOF)
    {
        /* ak znak nie je white-space */
        if (isspace(character) == 0)
        {
            /* a ak sme neprekrocili "max" pocet znakov */
            if (index < max)
            {
                /* nacitame ho do pola */
                s[index] = character;
                index++;
                /* vzdy predcasne nastavime null-terminating znak na konci slova */
                s[index] = '\0';
            }
            /* ak sme prekrocili "max" pocet znakov */
            else
            {
                /* zahodime vsetky ostatne znaky po najblizsi white-space */
                while (isspace(character = fgetc(f)) == 0) ;
                /* algoritmus ktory vypise chybovu hlasku na stderr iba 1x, potom ako sa vyskytne slovo, ktore prekroci
                 * "max" pocet znakov */
                word_is_longer++;
                if (word_is_longer == 1)
                    fprintf(stderr, "Some word(s) must be truncated ...\n");
            }
        }
        /* ak nacitavany znak je white-space */
        else
        {
            /* cyklus konci */
            break;
        }
    }

    /* ak je posledny nacitany znak EOF, funkcia vrati EOF */
    if (character == EOF)
        return EOF;

    /* funkcia vrati pocet nacitanych znakov ak sa nevyskytla ziadna vynimka */
    return index;
}
