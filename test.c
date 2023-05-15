#include <stdio.h>
#include <string.h>

int main()
{
    char s[100] = "hello";
    char t[100] = "hello";

    printf("%d\n", (int)memcmp(s, t, 100));
    char *v = s + 5;
    if (*v == '\0')
        printf("v is null\n");

    char *w[100];
    for (int i = 0; i < 100; i++)
        w[i] = NULL;
    
    char *x = w[i];

    
    return 0;
}