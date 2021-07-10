#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i = get_int("i: ");
    int j = get_int("j: ");
    
    if (i == j)
    {
        printf("Same\n"); // works because int are stored in the same location
    }
    else
    {
        printf("Different\n");
    }
    
    string s = get_string("s: ");
    string t = get_string("t: ");
    if (s == t)
    {
        printf("Same\n"); // Does not work because they are not stored in the same location
    }
    else
    {
        printf("Different\n");
    }
    printf("%p\n", s);
    printf("%p\n", t);
    
}