#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Create a stirng variable to save the name of the user
    string name = get_string("What's your name? ");
    
    // Print out "hello, user"
    printf("Hello, %s!\n", name);
}