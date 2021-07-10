#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string i = get_string("i: ");
    string j = i;
    j[0] = toupper(i[0]);
    
    printf("%s\n", i);
    printf("%s\n", j);
    
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1);
    
    strcpy(t, s);
    
    t[0] = toupper(s[0]);
    printf("%s\n", t);
    printf("%s\n", s);
    
    free(t);

}