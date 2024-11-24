#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <string.h>

char human = 'O';
char ai = '#';
char board[3][3];
int score_arr[] = {1,0,-1};

int min(int a,int b){
    if(a>b){
        return b;
    }
    return a;
}

int max(int a,int b){
    if(a>b){
        return a;
    }
    return b;
}

int checkTie(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == '_'){
                return 0;
            }
        }
    }
    return 1;
}

int checkWin(char player){
    int ans =  -1;
    int flag = 1;
    // row
    for(int i=0;i<3;i++){
        flag = 1;
        for(int j=0;j<3;j++){
            if(board[i][j] != player){
                flag = -1;
            }
        }
        if(flag == 1){
            return 1;
        }
    }
    // cols
    for(int i=0;i<3;i++){
        flag = 1;
        for(int j=0;j<3;j++){
            if(board[j][i] != player){
                flag = -1;
            }
        }
        if(flag == 1){
            return 1;
        }
    }
    // diagonals
    // main diagonal
    flag = 1;
    for(int i=0;i<3;i++){
        if(board[i][i] != player){
            flag = -1;
        }
    }
    if(flag == 1) return 1;

    // reverse diagonal
    flag = 1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i+j == 2 && board[i][j] != player){
                flag = -1;
            }
        }
    }
    if(flag == 1) return 1;

    return 0;
}


int minimax(int depth,int isMaximizing){
    
    if(checkWin(ai)){
        return 1;
    }else if(checkWin(human)){
        return -1;
    }else if(checkTie()){
        return 0;
    }

   if(isMaximizing){
    int bestScore = INT_MIN;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == '_'){
                board[i][j] = ai;
                int score = minimax(depth+1,0);
                board[i][j] = '_';
                bestScore = max(score,bestScore);
            }
        }
    }
    return bestScore;
   }else{
    int bestScore = INT_MAX;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == '_'){
                board[i][j] = human;
                int score = minimax(depth+1,1);
                board[i][j] = '_';
                bestScore = min(score,bestScore);
            }
        }
    }
    return bestScore;
   }
}

void bestMove(){
    int bestScore = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == '_'){
                board[i][j] = ai;
                int score = minimax(0,0);
                board[i][j] = '_';
                if(score > bestScore){
                    bestScore = score;
                    bestMoveRow = i;bestMoveCol = j;
                }
            }
        }
    }
    if(bestMoveRow != -1 && bestMoveCol != -1){
        board[bestMoveRow][bestMoveCol] = ai;
    }
};



void printBoard(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
           printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

int main(){

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            board[i][j] = '_';
        }
    }

    printf("\nYour Symbol : %c",human);
    printf("\nAI Symbol : %c\n",ai);

    while (1) {
        int row, col;
        printf("\nEnter row (0-2): ");
        scanf("%d", &row);
        printf("Enter col (0-2): ");
        scanf("%d", &col);

        if (board[row][col] == '_') {
            board[row][col] = human; 

            printf("\nYour Move\n");
            printBoard();

            if (checkWin(human)) {
                printf("\nHuman wins!\n");
                break;
            }
            if (checkTie()) {
                printf("\nIt's a tie!\n");
                break;
            }

            bestMove();
            printf("\nAI Move\n");
            printBoard();

            if (checkWin(ai)) {
                printf("\nAI wins!\n");
                break;
            }
            if (checkTie()) {
                printf("\nIt's a tie!\n");
                break;
            }
        } else {
            printf("\nCell is already occupied. Try again.\n");
        }
    }
}