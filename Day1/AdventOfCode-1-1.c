#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNUMS 1000
#define CALIBNUM_DIGITS_CNT 2
#define NULLTERM_CHARS_CNT 1
int main(__attribute__((unused))int argc, __attribute__((unused))char** argv)
{
    __attribute__((unused))FILE *calibFile = fopen("srcCalib.txt", "r");
    int c = 0;
    int digits[MAXNUMS] = {0};
    int digitIndex = 0;
    char calibNum[CALIBNUM_DIGITS_CNT + NULLTERM_CHARS_CNT] = {0};
    int calibSums = 0;
    while (c != EOF)
    {
        c = fgetc(calibFile);
        if (MAXNUMS == digitIndex || '\n' == c)
        {            
            calibNum[0] = digits[0];
            calibNum[1] = digits[--digitIndex];            
            calibNum[2] = '\0';            
            printf("%c%c\n", calibNum[0], calibNum[1]);
            calibSums += atoi(calibNum);
            printf("\n\nsum act: %d\n\n", calibSums);
            memset(digits, 0, MAXNUMS);
            digitIndex = 0;
            continue;
        }
        if (0 != isdigit(c))
        {
            (digits[digitIndex++] = c);
        } 
    }
            calibNum[0] = digits[0];
            calibNum[1] = digits[--digitIndex];            
            calibNum[2] = '\0';            
            printf("%c%c\n", calibNum[0], calibNum[1]);
            calibSums += atoi(calibNum);
            printf("\n\nsum act: %d\n\n", calibSums);
            memset(digits, 0, MAXNUMS);
            digitIndex = 0;

    printf("\n\n%d", calibSums);
    return 0;
}