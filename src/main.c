/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/


char text[] = "Vafgehpgvba frgf jnag gb or serr!";

volatile int wait = 1;

int main(int argc, char** argv)
{

    while (wait)
        ;

    int i = 0;
    while (text[i]) {
        char lower = text[i] | 32;
        if (lower >= 'a' && lower <= 'm')
            text[i] += 13;
        else if (lower > 'm' && lower <= 'z')
            text[i] -= 13;
        i++;
    }

    while (!wait)
        ;

    return 0;
}
