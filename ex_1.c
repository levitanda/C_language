/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/

int second_greatest(int numbers[], int length, int greatest);
int greatest(int numbers[], int length);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int length;
    printf("Please enter length:\n");
    scanf("%d", &length);
    int numbers[length];
    printf("Please enter array:\n");
    for(int i=0; i<length; i++){
        scanf("%d",&numbers[i]);
    }
    printf("The second-greatest is:\n");
    printf("%d", second_greatest(numbers, length, greatest(numbers,
                                                           length)));
  return 0;
}

int second_greatest(int numbers[], int length, int greatest){
    if(length==0) return 0;
    int k=second_greatest(numbers+1, length-1, greatest);
    if((numbers[0]>k)
       &&(numbers[0]<greatest)) return numbers[0];
    else return k;
}

int greatest(int numbers[], int length){
    if(length==0) return 0;
    if(numbers[0]>greatest(numbers+1, length-1)) return numbers[0];
    else return greatest(numbers+1, length-1);
}

