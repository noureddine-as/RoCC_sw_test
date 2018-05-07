/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/

char text[] = "Vafgehpgvba frgf jnag gb or serr!";

#define ENABLE_DEBUG 1

#if ENABLE_DEBUG
    volatile int wait = 1;
#endif

int main(int argc, char** argv)
{
#if ENABLE_DEBUG
    while (wait)
        ;
#else
    printf("Old text: %s \n", text);
#endif

    int i = 0;
    while (text[i]) {
        char lower = text[i] | 32;
        if (lower >= 'a' && lower <= 'm')
            text[i] += 13;
        else if (lower > 'm' && lower <= 'z')
            text[i] -= 13;
        i++;
    }

#if ENABLE_DEBUG
    while (!wait)
        ;
#else
    printf("New text: %s \n", text);
#endif
    return 0;
}
