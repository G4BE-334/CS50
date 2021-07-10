#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }
    
    unsigned char bytes[3];
    fread(bytes, 3, 1, file);
    
    // Check if bites are 0xff 0xd8 0xff
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("Maybe a jpeg\n");
    }
    else
    {
        printf("Not a jpeg\n");
    }
}