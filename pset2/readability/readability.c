#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get input from the user
    string text = get_string("Text: ");
    // Initiate letters variable
    int letters = 0;
    // Initiate words variable
    int words = 0;
    // Initiate sentences variable
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Verify every char in the text and look for letters
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        // Verify for char ' ' between words to count words
        // Do not count double space as an extra word
        else if (text[i] == ' ' && text[i + 1] != ' ')
        {
            words++;
        }
        // Look for indicators of sentences
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    // Add an extra word because there is no ' ' after the last word
    words ++;
    float L = 100 * (float)letters / words;
    float S = 100 * (float)sentences / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}