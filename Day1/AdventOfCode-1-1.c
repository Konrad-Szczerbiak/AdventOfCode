#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define CALIBNUM_DIGITS_CNT 2
#define NULLTERM_CHARS_CNT 1

int main(__attribute__((unused))int argc, __attribute__((unused))char** argv)
{
    FILE *calibFile = fopen("srcCalib.txt", "r");
    int c = 0;
    char calibNum[CALIBNUM_DIGITS_CNT+NULLTERM_CHARS_CNT] = {'x','x','\0'};
    int calibSums = 0;
    do  
    {
        c = fgetc(calibFile);
        if ('\n' == c || EOF == c)
        {   
            if ('x' == calibNum[1]) (calibNum[1] = calibNum[0]);
            calibSums += atoi(calibNum);
            calibNum[0] = calibNum[1] = 'x';
        }
        else if (0 != isdigit(c))
        {
            ('x' == calibNum[0]) ? 
            (calibNum[0] = c) : 
            (calibNum[1] = c);              
        } 
    } while (c != EOF);
    printf("\n\n%d\n", calibSums);
    return 0;
}
