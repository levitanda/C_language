/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 4


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
int shortest_path(int roads[N][N], int source, int destination,
                  int min_sum, int sum);
bool print_cities(int roads[N][N], int length, int current_length,
                  int source, int destination);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    printf("Please enter roads matrix:\n");
    int roads[N][N], source, destination;
    for(int i=0; i<N; i++){
        for(int k=0; k<N; k++){
            scanf("%d", &roads[i][k]);
        }
    }
    printf("Please enter source city:\n");
    scanf("%d", &source);
    printf("Please enter destination city:\n");
    scanf("%d", &destination);
    printf("The shortest path is:\n");
    int min_sum=roads[source][destination];
    int sum=0;
    int length=shortest_path(roads, source, destination, min_sum, sum);
    int current_length=0;
    print_cities(roads, length, current_length, source, destination);
  return 0;
}

int shortest_path(int roads[N][N], int source, int destination,
                  int min_sum, int sum){
    if(source==destination) return 0;
    if(sum>min_sum) return 0;
    for(int i=1; i<N; i++){
        if(source!=i){
            if(min_sum>roads[source][i]+shortest_path(roads, i,
                            destination, min_sum, sum+roads[source][i])){
                min_sum=roads[source][i]+shortest_path(roads, i,
                            destination, min_sum, sum+roads[source][i]);
            }
        }
    }
    return min_sum;
}

bool print_cities(int roads[N][N], int length, int current_length,
                  int source, int destination){
    if((current_length==length)&&(source==destination))
        return true;
    if(current_length>length)
        return false;
    for(int i=0; i<N; i++){
        if(destination!=i){
        if(print_cities(roads, length,
                        current_length+roads[i][destination], source, i)){
            printf("%d ", i);
            if(current_length==0)printf("%d ", destination);
            return true;
            }
        }
    }
    return false;
}
