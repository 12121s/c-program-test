#include <stdio.h>
#include <string.h>

int main()
{
    char origin[] = "BlockDMask";
    char dest4_1[20];
    char dest4_2[20];
    strncpy(dest4_1, origin, 8);
    strncpy(dest4_2, origin, 4);
    printf(" case4_1 : %s\n", dest4_1);
    dest4_2[4] = '\0';
    printf(" case4_2 : %s\n", dest4_2);

    return 0;
}


