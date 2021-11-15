/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

void printThreeDigitsOpenMessage();
void printResults(int avg,int rootOfMinNum,int avgPowTwoRootOfMinNum);
void printCharactersOpenMessage();
void printDataPerGivenCharAsInput(char ch,int numberOfTimesAppeared);
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared);
void characterAnalysis ();
//this function return the average of 3 numbers
int average(int a, int b, int c){
    int answer=(a+b+c)/3;
    return answer;
}

//this function return the minimal of two numbers
int min (int a, int b){
    if(a>b) return b;
    else return a;
}

//this function return the absolute of the number
int absolute (int a){
    if (a<0) return -a;
    else return a;
}

//this function return the square root of the number if he is integer,
//else it will return -1
int root (int a){
    //the variable sq will check for each i if the square of i is bigger
    //than a or equal to a
    int sq=0;
    int i=0;
    while (sq<a){
        i++;
        sq=i*i;
    }
    if (sq==a) return i;
    else return -1;
}

//the function return the b in power of p
int power (int p, int b){
    if(p<0||b<0) return -1;
    int answer=1;
    for(int i=0; i<p; i++){
        answer=answer*b;
        if(answer>1000000000) return -1;
    }

    return answer;
}


/*------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -----------------------------------------------------------------------*/
int main()
{
    printThreeDigitsOpenMessage();
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    //aver - the average of a b and c
    int aver=average(a,b,c);
    //minimum - the minimum of a b and c
    int minimum=min(a,min(b,c));
    //absolute_of_minimum - absolute of minimum of a b and c
    int absolute_of_minimum=absolute(minimum);
    //rot - the root of absolute of minimum of a b and c
    int rot=root(absolute_of_minimum);
    //pow - the average in power of absolute of minimum of a b and c
    int pow=power(absolute_of_minimum, aver);

    printResults(aver,rot,pow);
    characterAnalysis();
    return 0;
}

void characterAnalysis(){
    printCharactersOpenMessage();
    //OutOfAlphabet will count how many digitals out of
    //alphabet(small digitals) will be in the string
    int OutOfAlphabet=0;
    //TheString will include every entered letter
    char TheString[]={0};
   // scanf("%s", TheString);

    int countt=0;
    while(scanf("%c", &TheString[countt])!=EOF) countt++;
    for (int i=97; i<123; i++){
        int sum=0;
        //the variable letter will check every letter in the string
        int letter=0;
        while (TheString[letter]){
            if(TheString[letter]==i){ sum++;}
            letter++;

        }
        printDataPerGivenCharAsInput(i,sum);

    }
    // variable count will count every digital in the string
    int count=0;
    while (TheString[count]){
        if((TheString[count]<'a')||(TheString[count]>'z')) OutOfAlphabet++;

        count++;
    }
    printNumberOfOtherCharsAppeared(OutOfAlphabet-1);
}

void printThreeDigitsOpenMessage()
{
    printf("Please enter three integers:\n");
}

void printResults(int avg,int rootOfMinNum,int avgPowTwoRootOfMinNum){
    printf("%d %d %d\n",avg,rootOfMinNum,avgPowTwoRootOfMinNum);
}


void printCharactersOpenMessage(){
    printf("Please enter your character set:\n");
}

void printDataPerGivenCharAsInput(char ch,int numberOfTimesAppeared){
    printf("letter %c appeared %d time in the given set of characters\n",ch,numberOfTimesAppeared);
}
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared){
    printf("number of other characters in the given set was: %d\n",numberOfOtherCharsAppeared);
}
