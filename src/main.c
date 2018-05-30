/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/

char text[] = "Vafgehpgvba frgf jnag gb or serr!";
void foo()
{
    int i = 0;
    while (text[i]) {
        char lower = text[i] | 32;
        if (lower >= 'a' && lower <= 'm')
            text[i] += 13;
        else if (lower > 'm' && lower <= 'z')
            text[i] -= 13;
        i++;
    }
}
int main(int argc, char** argv)
{
    printf("Old text: %s \n", text);
    foo();
    printf("New text: %s \n", text);
    return 0;
}