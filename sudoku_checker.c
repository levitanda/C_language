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
#define MAX_ARRAY 25
void printOpenMessageForSodokoSize();
void printOpenMessageForSodokoSolution();
void printValidSolution();
void printBadSolution();
bool check_size();
bool check_squarts();
bool check_rows();
bool check_lines();
bool check_numbers();
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
	printOpenMessageForSodokoSize();
	//size will safe the size of the sudoku desk (size*size)
	int size=0;
	//this while scans the sudoku size till it will be suitable
	//for our question
	while (check_size(size)){
        scanf("%d", &size);
    }
    printOpenMessageForSodokoSolution();
    int sudoku[MAX_ARRAY][MAX_ARRAY]={{0}};
    //this for scans the sudoku and put it into array
    for(int i=0; i<size; i++){
        for (int k=0; k<size; k++){
            scanf("%d", &sudoku[i][k]);
        }
    }
    if(check_lines(sudoku, size)
       &&check_rows(sudoku, size)
       &&check_squarts(sudoku, size)){
        printValidSolution();
    }
    else printBadSolution();
    return 0;
}

//this function count the squart of a number
int squart(int x){
    int sq=0;
    int i=0;
    while (sq<x){
        i++;
        sq=i*i;
    }
    if (sq==x) return i;
    else return -1;
}

//this function check every row and send the data to check_numbers function
bool check_rows(int sudoku[][MAX_ARRAY], int size){
    for(int row=0; row<size;row++){
        int numbers[MAX_ARRAY]={0};
        for(int line=0;line<size;line++){
            numbers[sudoku[row][line]-1]++;
        }
        if (!check_numbers(numbers, size)) return false;
    }
    return true;
}

//this function check every line and send the data to
//check_numbers function
bool check_lines(int sudoku[][MAX_ARRAY], int size){
    for(int line=0; line<size;line++){
        int numbers[MAX_ARRAY]={0};
        for(int row=0;row<size;row++){
            numbers[sudoku[row][line]-1]++;
        }
        if (!check_numbers(numbers, size)) return false;
    }
    return true;
}

//this function check every squart and send the data
//to check_numbers function
bool check_squarts(int sudoku[][MAX_ARRAY], int size){
    for(int i=0; i<squart(size); i++){
        for(int k=0; k<squart(size);k++){
            int numbers[MAX_ARRAY]={0};
            for(int row=0;row<squart(size);row++){
                for(int line=0;line<squart(size); line++){
                    numbers[sudoku[row+i*squart(size)][line+k*squart(size)]-1]++;
                }
            }
            if (!check_numbers(numbers, size)) return false;
        }
    }
    return true;
}

//this function checks if there is all different numbers and they in
//maximum 1 time in chosen seqment (line, squart, row)
bool check_numbers(int numbers[], int maxnum){
    for (int i=0; i<maxnum;i++){
        if(numbers[i]!=1) return false;
    }
    return true;
}

//this function checks if entered number is full squart and not 0
bool check_size(int size){
    if (size==0) return 1;
    int sq=0;
    int i=0;
    while (sq<size){
        i++;
        sq=i*i;
    }
    if (sq==size) return 0;
    else return 1;
}
void printOpenMessageForSodokoSize(){
    printf("Please enter the size of your soduko:\n");
}
void printOpenMessageForSodokoSolution(){
    printf("Please enter your solution:\n");
}
void printValidSolution(){
    printf("Valid solution!\n");
}
void printBadSolution(){
    printf("Bad solution!\n");
}
