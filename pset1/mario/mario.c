#include <stdio.h>
#include <cs50.h>

// Calling the function before main (C is old)
void obstacleMaker(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    // ^^ Just to make sure that the input is a positive integer
    obstacleMaker(n);
}

void obstacleMaker(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        // Previously tried "  "(double space) but it does not match the answer
        printf(" ");
        printf(" ");
        // This way did not work as well
        
        for (int m = 0; m < i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
    printf("\n");
}