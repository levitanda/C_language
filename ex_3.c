/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define quantity 3


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
bool check_sum(int array[], int length, int sum, int current_sum,
               int count);
int index_of_max(int a[], int n);
void max_sort(int a[], int n);
void swap(int *a, int *b);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int length, sum, current_sum=0;
    printf("Please enter length:\n");
    scanf("%d", &length);
    int array[length];
    printf("Please enter array:\n");
    for(int i=0; i<length;i++){
        scanf("%d", &array[i]);
    }
    printf("Please enter sum:\n");
    scanf("%d", &sum);
   // max_sort(array, length);
    for(int i=0; i<length;i++){
        current_sum=current_sum+array[i];
    }
    if(check_sum(array, length, sum, current_sum, 1))
        printf("Such elements do exist.");
    else printf("Such elements do not exist.");


  return 0;
}

bool check_sum(int array[], int length, int sum, int current_sum,
               int count){
    if(count>quantity) return false;
    if((current_sum==sum)&&(count==quantity)) return true;
    if(current_sum<sum) return false;
    for(int i=length-1; i>=0; i++){
        int tmp=array[i];
        array[i]=0;
        max_sort(array, length);
        if(check_sum(array+1, length-1, sum, current_sum-array[i],
                     count++)) {
            array[i]=tmp;
            return true;
        }
        array[i]=tmp;
    }
    return false;
}

int index_of_max(int a[], int n) {
    int i, i_max = 0;
    for(i = 1; i < n; i++){
        if(a[i] > a[i_max])
            i_max = i;
    }
    return i_max;
}

void max_sort(int a[], int n) {
    int length;
    for(length = n ; length > 1; length--) {
        int i_max = index_of_max(a, length);
        swap(&a[length-1], &a[i_max]);
    }
}

void swap(int *a, int *b)
{
   int t;
   t  = *b;
   *b = *a;
   *a = t;
}
