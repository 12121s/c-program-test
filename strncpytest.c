#include <stdio.h>
#include <string.h>

int main()
{
    char *arrString = "Hello world!!";
    char arrDestString[5];
    unsigned int LONG_META;

    strncpy(arrDestString, arrString, LONG_META);
    
    printf("arrString : %s\n", arrString);
    printf("arrDestString : %s\n", arrDestString);

    strncpy(arrDestString, arrString, sizeof(arrDestString));
    
    printf("arrString : %s\n", arrString);
    printf("arrDestString : %s\n", arrDestString);

    return 0;
}