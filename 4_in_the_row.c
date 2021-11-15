#include <stdio.h>
#include <stdbool.h>
#include <assert.h>


//------------------------------- Constants ----------------------------//
#define BOARD_MAX_SIDE  25

#define MSG_WELCOME_MESSAGE  0
#define MSG_GET_BOARD_ROWS   1
#define MSG_GET_BOARD_COLS   2
#define MSG_GET_COLOR        3
#define MSG_PLAYER_MOVE      4
#define MSG_WINNER           5
#define MSG_GET_COLUMN       6
#define MSG_COLUMN_FULL      7
#define MSG_NO_WINNER        8

char const* const game_messages[];
//---------------------------- Predeclarations -------------------------//

/*
 * Outputs game board.
 *
 * board - contains spaces for empty cells, 'Y' or 'R' for
 *         respective player cells.
 * board_side - contains board dimensions {rows, cols}
 */
void print_board(char board[][BOARD_MAX_SIDE], int board_side[]);
//The function "enter_columns" will return the number of columns if the
//number is truly.
int enter_columns();
//The function "enter_rows" will return the number of columns if the
//number is truly.
int enter_rows();
//The function "welcome_and_enter_first_color" will print the welcome
//phrase and enter the color of the first player
//
//players_colors - array with 2 variables - color of first gamer and
//color of the second gamer
//
void welcome_and_enter_first_color(char players_colors[]);

//The function "check_tie" will check if it's tie on the board and if yes,
//will print a message about it
bool check_tie(char board[][BOARD_MAX_SIDE], int board_side[]);
//The function "check_win" will check if somebody already won
bool check_win(char board[][BOARD_MAX_SIDE], int board_side[],
               char players_colors[]);
//The function "check_rows" will check if there is already 4-in-a-row
//in some row
bool check_rows(char board[][BOARD_MAX_SIDE], int board_side[],
                char play_col[]);
//The function "check_columns" will check if there is already 4-in-a-row
//in some column
bool check_columns(char board[][BOARD_MAX_SIDE], int board_side[],
                   char play_col[]);
//The function "check_diagonal_UD" will check if there is already
//4-in-a-row in some diagonal from left up to right down
bool check_diagonal_UD(char board[][BOARD_MAX_SIDE], int board_side[],
                       char players_colors[]);
//The function will check if some diagonal from down to up which starts at
// left column will include 4-in-a-row
//
//play_col -array with 2 variables - color of first gamer and
//color of the second gamer
//
bool check_diagonal_DU_first_col(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                                 char play_col[]);
//The function will check if some diagonal from up to down which starts at
// left column will include 4-in-a-row
bool check_diagonal_UD_first_col(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                                 char play_col[]);
//The function will check if some diagonal from down to up which starts at
//down row will include 4-in-a-row
bool check_diagonal_DU_down_row(char board[][BOARD_MAX_SIDE],
                                int board_side[],
                                char play_col[]);
//The function will check if some diagonal from up to down which starts at
//upper row will include 4-in-a-row
bool check_diagonal_UD_up_row(char board[][BOARD_MAX_SIDE], int board_side[],
                       char play_col[]);
//The function "check_diagonal_DU" will check if there is already
//4-in-a-row in some diagonal from left down to right up
bool check_diagonal_DU(char board[][BOARD_MAX_SIDE], int board_side[],
                       char players_colors[]);
//The function "winner_num" will return the number of won player
//
//color - the current color which won
//
char winner_num (char color, char players_colors[]);
//the function "enter_column" will ask player to enter the column he wants
//to play and return the column in array that we need to put the color of
//a player
//
//stroke_number - the stroke number of the game. We need it to know who
//won the game
//
int enter_column(int board_side[], char board[][BOARD_MAX_SIDE],
                 int stroke_number);
//the function "get_row" will check how many chips already in the column
//and will return a row we have to past the color in array
int get_row(char board[][BOARD_MAX_SIDE], int column, int board_side[]);
// The function "player_color" will give the color uses the user
char player_color(int stroke_number, char players_colors[]);
//The function "player_num" will check the stroke number and return the
// player
int player_num (int stroke_number);
//the function will return the color of the same place on the board
char color(char board[][BOARD_MAX_SIDE], char clr, int col, int row);
//the function will return how many times the color was straight in the
//board
int count_color(int count, char board[][BOARD_MAX_SIDE],
                int row, int col, char clr);
//the function will print the message if somebody won
void print_result(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                       char play_col[], char clr);
//the function will print messages at the beggining of every stroke
void print_stroke(int stroke_number);
//the function will put spaces in the beggining table
void initialize_board(char board[][BOARD_MAX_SIDE]);
//the function will do all functions to check if the game is already
//finished or not
int check_game(char board[][BOARD_MAX_SIDE], int board_side[],
         char players_colors[], int stroke_number[]);

//--------------------------- Main Program -----------------------------//
//15 rows
int main()
{
    char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE], players_colors[2]={0, 0};
    initialize_board(board);
    welcome_and_enter_first_color(players_colors);
    int rows=enter_rows();
    if(rows==-1)
        return -1;
    int columns=enter_columns();
    if (columns==-1)
        return -1;
    int board_side[2]={rows, columns}, stroke_number[1]={1};
    if(check_game(board, board_side, players_colors, stroke_number) == -1) {
        return -1;
    }
    return 0;
}




//---------------------- Printing Functions ----------------------------//


// Inclusive check in range
#define IS_IN_RANGEI(VAL, MIN, MAX) (((VAL)>=(MIN)) && ((VAL)<=(MAX)))

char const* const game_messages[] = {
        "Welcome to 4-in-a-row game! \n",
        "Please enter number of rows: ",
        "Please enter number of columns: ",
        "Please choose starting color (Y)ellow or (R)ed: ",
        "Your move, player %d. ",
        "Player %d won! \n",
        "Please enter column: ",
        "Column full. ",
        "That's a tie. \n"
};

enum {BOARD_VERT_SEP=(int)'|',
    BOARD_LEFT_ANG=(int)'\\',
    BOARD_RIGHT_ANG=(int)'/',
    BOARD_BOTTOM=(int)'-',
    BOARD_BOTTOM_SEP=(int)'-'};

    //10 rows
void print_board(char board[][BOARD_MAX_SIDE], int board_side[])
{
    assert(IS_IN_RANGEI(board_side[0], 0, BOARD_MAX_SIDE)
           && IS_IN_RANGEI(board_side[1], 0, BOARD_MAX_SIDE));

    for (int row=0; row<board_side[0]; ++row)
    {
        printf("\n%c", (char)BOARD_VERT_SEP);
        for (int col = 0; col < board_side[1]; ++col)
            printf("%c%c", board[row][col], (char)BOARD_VERT_SEP);
    }
    printf("\n%c", (char)BOARD_LEFT_ANG);
    for (int ii=0; ii<board_side[1]-1; ++ii)
        printf("%c%c", (char)BOARD_BOTTOM, (char)BOARD_BOTTOM_SEP);
    printf("%c%c\n", (char)BOARD_BOTTOM, (char)BOARD_RIGHT_ANG);
}

//12 rows
int check_game(char board[][BOARD_MAX_SIDE], int board_side[],
         char players_colors[], int stroke_number[]) {
    while ((check_win(board, board_side, players_colors))&&
           check_tie(board, board_side)){
        print_board(board, board_side);
        int column=enter_column(board_side, board, stroke_number[0]);
        if(column==-1)
            return -1;
        board[get_row(board, column, board_side)][column]=
        player_color(stroke_number[0], players_colors);

        stroke_number[0]++;
    }
    return 0;
}

//3 rows
void initialize_board(char board[][BOARD_MAX_SIDE]) {
    for(int i=0; i<BOARD_MAX_SIDE;i++){
        for(int k=0; k<BOARD_MAX_SIDE;k++){
            board[i][k]=' ';
        }
    }
}

//6 rows
int enter_rows(){
    int rows=-1;
    while (IS_IN_RANGEI(rows, 1, BOARD_MAX_SIDE)!= true){
        printf(game_messages[MSG_GET_BOARD_ROWS]);
        if(!scanf("%d", &rows)){
            return -1;
        }
    }
    return rows;
}

//7 rows
int enter_columns(){
    int columns=-1;
    while (IS_IN_RANGEI(columns, 1, BOARD_MAX_SIDE)!= true){
        printf(game_messages[MSG_GET_BOARD_COLS]);
        if(!scanf("%d", &columns))
            return -1;
    }
    return columns;
}

//3 rows
char winner_num(char color, char players_colors[]){
    if (players_colors[0]==color)
        return 1;
    else return 2;
}

//10 rows
void welcome_and_enter_first_color(char players_colors[]){
    printf(game_messages[MSG_WELCOME_MESSAGE]);
    char color='0';
    while((color!='R')&&(color!='Y')){
        printf(game_messages[MSG_GET_COLOR]);
        scanf (" %c", &color);
    }
    players_colors[0]=color;
    if(players_colors[0]=='Y')
        players_colors[1]='R';
    else players_colors[1]='Y';
}

//8 rows
bool check_tie(char board[][BOARD_MAX_SIDE], int board_side[]){
    for (int row=0; row<board_side[0]; ++row)
    {
        for (int col = 0; col < board_side[1]; ++col){
            if((board[row][col]!='R')&&(board[row][col]!='Y')){
               return true;
               }
        }
    }
    print_board(board, board_side);
    printf(game_messages[MSG_NO_WINNER]);
    return false;
}

//6 rows
bool check_win(char board[][BOARD_MAX_SIDE], int board_side[],
               char players_colors[]){
    if (check_rows(board, board_side, players_colors)||
        check_columns(board, board_side,players_colors)||
        check_diagonal_DU(board, board_side,players_colors)||
        check_diagonal_UD(board, board_side,players_colors))
            return false;
    else return true;
}

//12 rows
bool check_rows(char board[][BOARD_MAX_SIDE], int board_side[],
                char play_col[]){
    for (int row=0; row<board_side[0]; row++)
    {
        //the variable "count" will check how many times was same color
        //in the row
        int count=1;
        char clr='T';
        for (int col = 0; col < board_side[1]; col++){
            count=count_color(count, board, row, col, clr);
            clr=color(board, clr, col, row);
            if(count==4) {
               print_result(board, board_side, play_col, clr);
               return true;
            }
        }
    }
    return false;
}

//12 rows
bool check_columns(char board[][BOARD_MAX_SIDE], int board_side[],
                   char play_col[]){
    for (int col=0; col<board_side[1]; col++)
    {
        //the variable "count" will check how many times was same color
        //in the column
        int count=1;
        char clr='T';
        for (int row = 0; row < board_side[0]; row++){
            count=count_color(count, board, row, col, clr);
            clr=color(board, clr, col, row);
            if(count==4) {
               print_result(board, board_side, play_col, clr);
               return true;
            }
        }
    }
    return false;
}

//4 rows
bool check_diagonal_DU(char board[][BOARD_MAX_SIDE], int board_side[],
                       char players_colors[]){
    //variable "diagonal" is the number of column where the diagonal starts
    if(check_diagonal_DU_first_col(board, board_side, players_colors)||
       check_diagonal_DU_down_row(board, board_side, players_colors)){
           return true;
       }
    return false;
}

//6 rows
int count_color(int count, char board[][BOARD_MAX_SIDE],
                int row, int col, char clr){
    if((board[row][col]==clr)){
                    count++;
                }
            else {if((board[row][col]=='Y')||(board[row][col]=='R')){
                    count=1;
                }}
    return count;
}

//5 rows
char color(char board[][BOARD_MAX_SIDE], char clr, int col, int row){
    if((board[row][col]!=clr)&&((board[row][col]=='Y')||
                                (board[row][col]=='R'))){
                clr=board[row][col];
            }
    return clr;
}

//3 rows
void print_result(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                       char play_col[], char clr){
    print_board(board, board_side);
    printf(game_messages[MSG_WINNER],winner_num(clr, play_col));
}

//15 rows
bool check_diagonal_DU_first_col(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                       char play_col[]){
    for(int diagonal=0; diagonal<board_side[0]; diagonal++){
        char clr='T';
        int row=diagonal, col=0, count=1;
        while((row>=0)&&(col<=board_side[1])){
            count=count_color(count, board, row, col,clr);
            clr=color(board, clr, col, row);
            if(count==4) {
               print_result(board, board_side, play_col, clr);
               return true;
            }
            col++;
            row--;
        }
    }
    return false;
}

//15 rows
bool check_diagonal_DU_down_row(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                       char play_col[]){
    for(int diagonal=0; diagonal<board_side[1]; diagonal++){
        char clr='T';
        int col=diagonal, row=board_side[0]-1, count=1;
        while((row>=0)&&(col<=board_side[1])){
            count=count_color(count, board, row, col, clr);
            clr=color(board, clr, col, row);
            if(count==4) {
                print_result(board, board_side, play_col, clr);
                return true;
            }
            col++;
            row--;
        }
    }
    return false;
}

//4 rows
bool check_diagonal_UD(char board[][BOARD_MAX_SIDE], int board_side[],
                       char players_colors[]){
    if(check_diagonal_UD_first_col(board, board_side, players_colors)||
       check_diagonal_UD_up_row(board, board_side, players_colors)){
        return true;
       }
    return false;
}

//15 rows
bool check_diagonal_UD_first_col(char board[][BOARD_MAX_SIDE],
                                 int board_side[],
                       char play_col[]){
    for(int diagonal=0; diagonal<board_side[0]; diagonal++){
        char clr='T';
        int row=diagonal, col=0, count=1;
        while((row<=board_side[0])&&(col<=board_side[1])){
            count=count_color(count, board, row, col, clr);
            clr=color(board, clr, col, row);
            if(count==4) {
                print_result(board, board_side, play_col, clr);
                return true;
            }
            col++;
            row++;
        }
    }
    return false;
}

//15 rows
bool check_diagonal_UD_up_row(char board[][BOARD_MAX_SIDE], int board_side[],
                       char play_col[]){
    for(int diagonal=0; diagonal<board_side[1]; diagonal++){
        char clr='T';
        int col=diagonal, row=0, count=1;
        while((row<=board_side[0])&&(col<=board_side[1])){
            count=count_color(count, board, row, col, clr);
            clr=color(board, clr, col, row);
            if(count==4) {
                print_result(board, board_side, play_col, clr);
                return true;
            }
            col++;
            row++;
        }
    }
    return false;
}
//3 rows
void print_stroke(int stroke_number){
    printf(game_messages[MSG_PLAYER_MOVE], player_num(stroke_number));
    printf(game_messages[MSG_GET_COLUMN]);
}
//15 rows
int enter_column(int board_side[], char board[][BOARD_MAX_SIDE],
                 int stroke_number){
    print_stroke(stroke_number);
    int col=0;
    if(!scanf("%d", &col))
        return -1;
    if(get_row(board, col-1,board_side)==-1)
        col=-1;
    while((col<=0)||(col>board_side[1])){
        printf(game_messages[MSG_GET_COLUMN]);
        if(!scanf("%d", &col))
            return-1;
        if(get_row(board, col-1,board_side)==-1)
            col=-1;
    }
    return (col-1);
}

//8 rows
int get_row(char board[][BOARD_MAX_SIDE], int column, int board_side[]){
    int row=board_side[0]-1;
    while((board[row][column]!=' ')&&(row>0)){
        row--;
    }
    if(board[row][column]==' ')
        return row;
    else{
        printf(game_messages[MSG_COLUMN_FULL]);
        return (-1);
    }
}

//3 rows
char player_color(int stroke_number, char players_colors[]){
    if(stroke_number%2==1)
        return players_colors[0];
    else return players_colors[1];
}

//3 rows
int player_num(int stroke_number){
    if (stroke_number%2==0)
        return 2;
    else return 1;
}
