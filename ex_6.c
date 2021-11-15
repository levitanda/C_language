/*------------------------------------------------------------------------
  Include files:
------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

/*========================================================================
  Constants and definitions:
========================================================================*/

/* put your #defines and typedefs here*/


void printGivenParamsToTheOutput(char ch,int asciiCode,int asciiCodePowTwo,
                                 int difference,int unitDigitOfDiff);
void printResults(int digitsCounter,int lettersCounter,int spacesCounter);



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 ------------------------------------------------------------------------*/
int main()
{
    char ch=0;
    scanf("%c", &ch);
    int reserve = 0;
    //reserve will save the ascii number of the previous letter
    int digitsCounter=0, lettersCounter=0, spacesCounter=0;
    while(ch!=';'){
        int asciiCode = (int)ch;
        int asciiCodePowTwo = asciiCode*asciiCode;
        int difference = asciiCode-reserve;
        int unitDigitOfDiff = difference%10;
        printGivenParamsToTheOutput(ch, asciiCode, asciiCodePowTwo,
                                    difference, unitDigitOfDiff);
        reserve= asciiCode;
        if((asciiCode>96&&asciiCode<123)||(asciiCode>64&&asciiCode<91))
            {lettersCounter++;}
        if(asciiCode>47&&asciiCode<58) digitsCounter++;
        if(asciiCode==32) spacesCounter++;
        scanf("%c", &ch);
    }
    printResults(digitsCounter, lettersCounter, spacesCounter);
    return 0;
}

//The function prints the parameters of letter and pass to the next line
void printGivenParamsToTheOutput(char ch,int asciiCode,int asciiCodePowTwo
                                 ,int difference,int unitDigitOfDiff){
    printf("%c%10d%10d%10d%10d\n",ch,asciiCode,asciiCodePowTwo,difference,
           unitDigitOfDiff);
}

//the function prints the common statistics of all letters
void printResults(int digitsCounter,int lettersCounter,int spacesCounter){
    printf("Number of digits received: %d\n",digitsCounter);
    printf("Number of letters received: %d\n",lettersCounter);
    printf("Number of spaces received: %d\n",spacesCounter);
}
