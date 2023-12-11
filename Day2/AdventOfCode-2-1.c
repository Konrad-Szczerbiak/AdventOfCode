#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RED_CUBES_CNT 12
#define MAX_GREEN_CUBES_CNT 13
#define MAX_BLUE_CUBES_CNT 14

typedef enum {
    eKeyWord_GAME,
    eKeyWord_RED,
    eKeyWord_GREEN,
    eKeyWord_BLUE,
} E_KeywordType;

static const char* keywordsLUT[3] = {
    "Game",
    "red",
    "green",
    "blue"
};

#define MAX_OCCURENCES 100
#define MAX_DIGITS_OF_CNT 2
#define ZERO_TERM_STAND 1


int* getArrayOfCounts(char* pStartPos, E_KeywordType keyType)
{
    int cnts[MAX_OCCURENCES] = {0};
    int occurs = 0;
    char* pTmp = pStartPos;
    char stringCnt[MAX_DIGITS_OF_CNT + ZERO_TERM_STAND] = {'0','0','\0'};  
    while(pTmp) {
        if (NULL == (pTmp = strstr(pTmp, keywordsLUT[keyType])))
        {
            break;
        }
        pTmp--; // we discard the first letter of keyword;
        int actDigitsOfCnt = 1; // max cnt is 2 digit long, min cnt - 1 digit long
        while (isdigit(*--pTmp))
        {            
            stringCnt[MAX_DIGITS_OF_CNT - actDigitsOfCnt++] = *pTmp;
        }
        cnts[occurs++] = atoi(stringCnt);
        memset(stringCnt, '0', 2*sizeof(char));
        pTmp+= actDigitsOfCnt + ZERO_TERM_STAND + 1;
    }
}

#define MAXLINE 1000
int main(__attribute((unused))int argc, __attribute((unused))char* argv)
{
    FILE* gamesInputs = fopen("games.txt", "r");
    char c[MAXLINE] = {0};
    int index = 0;
    while (EOF != (c[index] = fgetc(gamesInputs)))
    {
        if (c[index] == '\n')
        {
            getArrayOfCounts(c, eKeyWord_RED);
        }
        index++;
    }
}