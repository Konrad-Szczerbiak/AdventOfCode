#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CALIBNUM_DIGITS_CNT 2
#define NULLTERM_CHARS_CNT 1
/*
"
two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

result 281
"
*/
#define MAXLINE 1000

int findFirstDigitInLine(char* strSrc, int lastIndex)
{
    static const char* LUT[] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };
    int minDigitOffset = -1;
    int maxDigitOffset = MAXLINE;
    int retMin = 0;
    int retMax = 0;
    
    for (int digit = 0; digit <= 9; digit++)
    {
        char* pFirstOccurence = strstr(strSrc, LUT[digit]);
        char* pLastOccurence = pFirstOccurence;
        if (pFirstOccurence == NULL)
        {
            continue;
        }
        char* pTmp = pLastOccurence;
        while (pTmp)
        {
            pTmp = strstr(pLastOccurence+1, LUT[digit]);
            if (pTmp) pLastOccurence = pTmp;
        }

        if (-1 == minDigitOffset || minDigitOffset > (pFirstOccurence - strSrc))
        {
            minDigitOffset = (pFirstOccurence - strSrc);
            retMin = digit;
        }
        if (MAXLINE == maxDigitOffset || maxDigitOffset < (pLastOccurence - strSrc))
        {
            maxDigitOffset = (pLastOccurence - strSrc);
            retMax = digit;
        }
    }
    minDigitOffset = (-1 == minDigitOffset) ? lastIndex : minDigitOffset;
    maxDigitOffset = (MAXLINE == maxDigitOffset) ? 0 : maxDigitOffset;
    while (minDigitOffset-- > 0)
    {
        if(isdigit(strSrc[minDigitOffset])) retMin = strSrc[minDigitOffset] - '0';
    }
    while (maxDigitOffset++ < lastIndex)
    {
        if(isdigit(strSrc[maxDigitOffset])) retMax = strSrc[maxDigitOffset] - '0';
    }
    if (retMax == 0 && retMin != 0) retMax = retMin;
    else if (retMin == 0 && retMax != 0) retMin = retMax;
    return 10*retMin+retMax;
}

int main(__attribute__((unused))int argc, __attribute__((unused))char** argv)
{
    FILE *calibFile = fopen("srcCalib.txt", "r");
    char calibNum[CALIBNUM_DIGITS_CNT + NULLTERM_CHARS_CNT] = {'x','x','\0'};
    char line[MAXLINE] = {0};
    int index = 0;
    int calibSums = 0;
    do  
    {
        line[index] = fgetc(calibFile);
        if ('\n' == line[index] || EOF == line[index])
        {   
            if (strstr(line, "eightsix4twofoursgdlfkjonefoureight"))
            {
                int test = 1;
            }
            int firstLineDigit = findFirstDigitInLine(line, index);
            printf("\nNumber in line: %d\n", firstLineDigit);
            calibSums += firstLineDigit;
            memset(line, 0, sizeof(char)*index);
            if (EOF != line[index]) index = -1;
        }

    } while (index != MAXLINE && line[index++] != EOF);
    printf("\n\nSum of numbers: %d\n", calibSums);
    return 0;
}
