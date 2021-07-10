#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Missing command-line argument!\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters!\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if ((int) argv[1][i] < 65 || (int) argv[1][i] > 122 || ((int) argv[1][i] > 90 && (int) argv[1][i] < 97))
        {
            printf("Invalid key\n");
            return 1;
        }
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if ((int) argv[1][i] == (int) argv[1][j] && i != j)
            {
                printf("Key cannot contain repeated characters\n");
                return 1;
            }
        }
    }
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] == 'a')
        {
            ciphertext[i] = tolower(argv[1][0]);
        }
        else if (plaintext[i] == 'b')
        {
            ciphertext[i] = tolower(argv[1][1]);
        }
        else if (plaintext[i] == 'c')
        {
            ciphertext[i] = tolower(argv[1][2]);
        }
        else if (plaintext[i] == 'd')
        {
            ciphertext[i] = tolower(argv[1][3]);
        }
        else if (plaintext[i] == 'e')
        {
            ciphertext[i] = tolower(argv[1][4]);
        }
        else if (plaintext[i] == 'f')
        {
            ciphertext[i] = tolower(argv[1][5]);
        }
        else if (plaintext[i] == 'g')
        {
            ciphertext[i] = tolower(argv[1][6]);
        }
        else if (plaintext[i] == 'h')
        {
            ciphertext[i] = tolower(argv[1][7]);
        }
        else if (plaintext[i] == 'i')
        {
            ciphertext[i] = tolower(argv[1][8]);
        }
        else if (plaintext[i] == 'j')
        {
            ciphertext[i] = tolower(argv[1][9]);
        }
        else if (plaintext[i] == 'k')
        {
            ciphertext[i] = tolower(argv[1][10]);
        }
        else if (plaintext[i] == 'l')
        {
            ciphertext[i] = tolower(argv[1][11]);
        }
        else if (plaintext[i] == 'm')
        {
            ciphertext[i] = tolower(argv[1][12]);
        }
        else if (plaintext[i] == 'n')
        {
            ciphertext[i] = tolower(argv[1][13]);
        }
        else if (plaintext[i] == 'o')
        {
            ciphertext[i] = tolower(argv[1][14]);
        }
        else if (plaintext[i] == 'p')
        {
            ciphertext[i] = tolower(argv[1][15]);
        }
        else if (plaintext[i] == 'q')
        {
            ciphertext[i] = tolower(argv[1][16]);
        }
        else if (plaintext[i] == 'r')
        {
            ciphertext[i] = tolower(argv[1][17]);
        }
        else if (plaintext[i] == 's')
        {
            ciphertext[i] = tolower(argv[1][18]);
        }
        else if (plaintext[i] == 't')
        {
            ciphertext[i] = tolower(argv[1][19]);
        }
        else if (plaintext[i] == 'u')
        {
            ciphertext[i] = tolower(argv[1][20]);
        }
        else if (plaintext[i] == 'v')
        {
            ciphertext[i] = tolower(argv[1][21]);
        }
        else if (plaintext[i] == 'w')
        {
            ciphertext[i] = tolower(argv[1][22]);
        }
        else if (plaintext[i] == 'x')
        {
            ciphertext[i] = tolower(argv[1][23]);
        }
        else if (plaintext[i] == 'y')
        {
            ciphertext[i] = tolower(argv[1][24]);
        }
        else if (plaintext[i] == 'z')
        {
            ciphertext[i] = tolower(argv[1][25]);
        }
        else if (plaintext[i] == 'A')
        {
            ciphertext[i] = toupper(argv[1][0]);
        }
        else if (plaintext[i] == 'B')
        {
            ciphertext[i] = toupper(argv[1][1]);
        }
        else if (plaintext[i] == 'C')
        {
            ciphertext[i] = toupper(argv[1][2]);
        }
        else if (plaintext[i] == 'D')
        {
            ciphertext[i] = toupper(argv[1][3]);
        }
        else if (plaintext[i] == 'E')
        {
            ciphertext[i] = toupper(argv[1][4]);
        }
        else if (plaintext[i] == 'F')
        {
            ciphertext[i] = toupper(argv[1][5]);
        }
        else if (plaintext[i] == 'G')
        {
            ciphertext[i] = toupper(argv[1][6]);
        }
        else if (plaintext[i] == 'H')
        {
            ciphertext[i] = toupper(argv[1][7]);
        }
        else if (plaintext[i] == 'I')
        {
            ciphertext[i] = toupper(argv[1][8]);
        }
        else if (plaintext[i] == 'J')
        {
            ciphertext[i] = toupper(argv[1][9]);
        }
        else if (plaintext[i] == 'K')
        {
            ciphertext[i] = toupper(argv[1][10]);
        }
        else if (plaintext[i] == 'L')
        {
            ciphertext[i] = toupper(argv[1][11]);
        }
        else if (plaintext[i] == 'M')
        {
            ciphertext[i] = toupper(argv[1][12]);
        }
        else if (plaintext[i] == 'N')
        {
            ciphertext[i] = toupper(argv[1][13]);
        }
        else if (plaintext[i] == 'O')
        {
            ciphertext[i] = toupper(argv[1][14]);
        }
        else if (plaintext[i] == 'P')
        {
            ciphertext[i] = toupper(argv[1][15]);
        }
        else if (plaintext[i] == 'Q')
        {
            ciphertext[i] = toupper(argv[1][16]);
        }
        else if (plaintext[i] == 'R')
        {
            ciphertext[i] = toupper(argv[1][17]);
        }
        else if (plaintext[i] == 'S')
        {
            ciphertext[i] = toupper(argv[1][18]);
        }
        else if (plaintext[i] == 'T')
        {
            ciphertext[i] = toupper(argv[1][19]);
        }
        else if (plaintext[i] == 'U')
        {
            ciphertext[i] = toupper(argv[1][20]);
        }
        else if (plaintext[i] == 'V')
        {
            ciphertext[i] = toupper(argv[1][21]);
        }
        else if (plaintext[i] == 'W')
        {
            ciphertext[i] = toupper(argv[1][22]);
        }
        else if (plaintext[i] == 'X')
        {
            ciphertext[i] = toupper(argv[1][23]);
        }
        else if (plaintext[i] == 'Y')
        {
            ciphertext[i] = toupper(argv[1][24]);
        }
        else if (plaintext[i] == 'Z')
        {
            ciphertext[i] = toupper(argv[1][25]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}