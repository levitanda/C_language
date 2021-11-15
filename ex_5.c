/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define MAX_STRINGS 10
#define MAX_STR_LEN 50
#define A_a_diference 32
#define a_ASCII 97
#define z_ASCII 122

int readPalindromes(char* palindromes[],int maxSize,int maxStrLen);
int  minimizedPalindromes(char* palindromes[],int size,char* miniOddPali[],
                          int *sizeOdd,char* miniEvenPali[],int *sizeEven);
void printPalindromes(char* miniOddPali[],int sizeOdd,
                      char* miniEvenPali[],int sizeEven);
void freeMemory(char* palindromes[],int size,char* miniOddPali[],
                int sizeOdd,char* miniEvenPali[],int sizeEven);
void printAllocationError();
bool if_palindrome(char* word);
void make_big_letters(char* miniPali[], int size);
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    char* words[MAX_STRINGS], *paliOdd[MAX_STRINGS],
    *paliEven[MAX_STRINGS];

    int sizeOdd=0, sizeEven=0;
    int numberOfPali=readPalindromes(words,MAX_STRINGS,MAX_STR_LEN);
    if(numberOfPali==0)return 0;
    if(minimizedPalindromes(words, numberOfPali, paliOdd, &sizeOdd, paliEven,
                         &sizeEven)==0) return 0;
    printPalindromes(paliOdd, sizeOdd, paliEven, sizeEven);
    freeMemory(words,numberOfPali,paliOdd, sizeOdd, paliEven, sizeEven);
  return 0;
}

int readPalindromes(char* palindromes[],int maxSize,int maxStrLen){
    int how_much_words=0;
    char word[maxStrLen];
    while((scanf("%s", word)!=EOF)&&(how_much_words<maxSize)){
        if(if_palindrome(word)){
           if((palindromes[how_much_words] =
               (char*)malloc(sizeof(char)*strlen(word)))==NULL){
                printAllocationError();
                for(int i=0; i<=how_much_words;i++){
                    free(palindromes[i]);
                }
                return 0;
           }
           strcpy(palindromes[how_much_words],word);
           how_much_words++;

        }
    }
    return how_much_words;
}

bool if_palindrome(char* word){
    for(int i=0; i<(int)strlen(word); i++){
        if((word[i]!=word[strlen(word)-1-i])&&
           abs((int)word[i]-(int)word[strlen(word)-1-i])!=A_a_diference)
            return false;
    }
    return true;
}

void make_big_letters(char* miniPali[], int size){
    for(int i=0; i<size; i++){
        for(int k=0; k<(int)strlen(miniPali[i]); k++){
            if(miniPali[i][k]>=a_ASCII&&miniPali[i][k]<=z_ASCII){
                miniPali[i][k]=miniPali[i][k]-A_a_diference;
            }
        }
    }
}

int  minimizedPalindromes(char* palindromes[],int size,char* miniOddPali[],
                          int *sizeOdd,char* miniEvenPali[],int *sizeEven){
    int minimized_words=0;
    int even=0, odd=0;
    while(minimized_words<size){
        if((strlen(palindromes[minimized_words])%2)==0){
            if((miniEvenPali[even]=(char*)malloc(sizeof(char)*
                (strlen(palindromes[minimized_words])/2)))==NULL) {
                    printAllocationError();
                    freeMemory(palindromes,size,miniOddPali,*sizeOdd,
                               miniEvenPali,*sizeEven);
                    return 0;
                }
          for(int i=0; i<(int)strlen(palindromes[minimized_words])/2; i++){
                miniEvenPali[even][i]=palindromes[minimized_words][i];
            }
            even++;
            minimized_words++;
        }
        else{
            if((miniOddPali[odd]=(char*)malloc(sizeof(char)*
                ((strlen(palindromes[minimized_words])+1)/2)))==NULL) {
                    printAllocationError();
                    freeMemory(palindromes,size,miniOddPali,*sizeOdd,
                               miniEvenPali,*sizeEven);
                    return 0;
                }
      for(int i=0; i<(int)(strlen(palindromes[minimized_words])+1)/2; i++){
                miniOddPali[odd][i]=palindromes[minimized_words][i];
            }
            odd++;
            minimized_words++;
        }
    }
    *sizeOdd=odd;
    *sizeEven=even;
    return minimized_words;
}


void printPalindromes(char* miniOddPali[],int sizeOdd,
                      char* miniEvenPali[],int sizeEven){
    make_big_letters(miniOddPali, sizeOdd);
    make_big_letters(miniEvenPali, sizeEven);
    for(int word_odd=0; word_odd<sizeOdd; word_odd++){
        printf("%s", miniOddPali[word_odd]);
        for(int letter=((int)strlen(miniOddPali[word_odd])-2); letter>=0;
        letter--){
            printf("%c", miniOddPali[word_odd][letter]);
        }
        printf("\n");
    }
    for(int word=0; word<sizeEven; word++){
        printf("%s", miniEvenPali[word]);
        for(int letter=(int)strlen(miniEvenPali[word])-1; letter>=0;
        letter--){
            printf("%c", miniEvenPali[word][letter]);
        }
        printf("\n");
    }
}

void freeMemory(char* palindromes[],int size,char* miniOddPali[],
                int sizeOdd,char* miniEvenPali[],int sizeEven){
    for(int i=0; i<size; i++){
        free(palindromes[i]);
    }
    for(int i=0; i<sizeOdd; i++){
        free(miniOddPali[i]);
    }
    for(int i=0; i<sizeEven; i++){
        free(miniEvenPali[i]);
    }
}

void printAllocationError(){
        printf("Memory Allocation Failed\n");
}
