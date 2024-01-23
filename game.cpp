#include <iostream>
#include <vector>
using namespace std;

//Global variables
vector<char> board(9);
const char PLAYER = 'X';
const char COMPUTER = 'O';

//Functions
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
int minimax(bool isMaximizing);

int main(){

    char response = ' ';

    do{
        //resetting the board at the begining of every game
        resetBoard();

        //choosing the starting side
        char startingSide;
        cout << "Choose starting side (1 for player, 2 for computer) or anywhere else to exit: ";
        cin >> startingSide;

        char winner = ' ';

        //loop in which the game is taking place untill any side wins or there are no blank spaces left
        while (winner == ' ' && checkFreeSpaces() != 0){
            
            if (startingSide == '1' || startingSide == '2'){

                if (startingSide == '1'){
                    printBoard();
                    playerMove();
                }
                else {computerMove();}
            }
            else{
                cout << "Thanks for playing!" << endl;
                return 0;
            }

            winner = checkWinner();
            if (winner != ' ') {break;}

            if (startingSide == '2' && checkFreeSpaces() > 0){

                printBoard();
                playerMove();
                winner = checkWinner();
                if (winner != ' ') {break;}
            }
            else if (checkFreeSpaces() > 0) {computerMove();}

            winner = checkWinner();
            if (winner != ' ') {break;}

        }

        printBoard();
        printWinner(winner);

        cout << endl
        << "Do you want to play again? 'Y' to continue or anywhere else to exit: ";
        cin >> response;
        response = toupper(response);
    } while (response == 'Y');

    cout << "Thanks for playing!" << endl;

    return 0;
}

//Setting all cells to ' ' at the beggining of the game
void resetBoard(){
   for(int i = 0; i < 9; i++) {board[i] = ' ';}
}

//Printing current state of game
void printBoard(){

    cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "--|---|--" << endl;
    cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "--|---|--" << endl;
    cout << board[6] << " | " << board[7] << " | " << board[8] << endl;    
}

//Checking how many blank spaces left
int checkFreeSpaces(){

   int freeSpaces = 9;

   for(int i = 0; i < 9; i++){ 
        if(board[i] != ' ') {freeSpaces--;}
   }

   return freeSpaces;
}

//Function allowing user to make a move on board
void playerMove(){
    int x;

    do{
        cout << "Enter place (1-9): ";
        if (cin >> x){

            x--;

            if (x < 0 || x >= 9 || board[x] != ' ') {cout << "Invalid move!" << endl;}
            else{
                board[x] = PLAYER;
                break;
            }
        }
        else{
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while (true);
}

//Function responsible for computer move 
void computerMove(){

    int bestMove = -1;
    int bestScore = numeric_limits<int>::min();

    for (int i = 0; i < 9; i++){

        if (board[i] == ' '){
        
            board[i] = COMPUTER;
            int score = minimax(false);
            board[i] = ' ';

            if (score > bestScore){
                bestScore = score;
                bestMove = i;
            }
        }
    }

    if (bestMove != -1){
        board[bestMove] = COMPUTER;
    }
    else{
        printWinner(' '); // Gra zakończona remisem
    }
}

//Implementation of an algorithm used for 'no-loss' strategy of a computer
int minimax(bool isMaximizing){

    char winner = checkWinner();
    if (winner == COMPUTER) {return 1;}
    else if (winner == PLAYER) {return -1;}
    else if (checkFreeSpaces() == 0) {return 0;}


    int bestScore;
    if (isMaximizing){

        bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++){
            if (board[i] == ' '){
                board[i] = COMPUTER;
                bestScore = max(bestScore, minimax(false));
                board[i] = ' ';
            }
        }
    }
    else{

        bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++){
            if (board[i] == ' '){
                board[i] = PLAYER;
                bestScore = min(bestScore, minimax(true));
                board[i] = ' ';
            }
        }
    }

    return bestScore;
}

//Checking if the game has been won by any side
char checkWinner(){
   
    //horizontally
    if (board[0] == board[1] && board[1] == board[2] && board[0] != ' ') {return board[0];}
    else if (board[3] == board[4] && board[4] == board[5] && board[3] != ' ') {return board[3];}
    else if (board[6] == board[7] && board[7] == board[8] && board[6] != ' ') {return board[6];}

    //vertically
    else if (board[0] == board[3] && board[3] == board[6] && board[0] != ' ') {return board[0];}
    else if (board[1] == board[4] && board[4] == board[7] && board[1] != ' ') {return board[1];}
    else if (board[2] == board[5] && board[5] == board[8] && board[2] != ' ') {return board[2];}

    //diagonally
    else if (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') {return board[0];}
    else if (board[2] == board[4] && board[4] == board[6] && board[2] != ' ') {return board[2];}

    //no winner
    else {return ' ';}
}

//Printing the information about the ruslt of a game
void printWinner(char winner){

   if(winner == PLAYER) {cout << "You win" << endl;}

   else if(winner == COMPUTER) {cout << "You lose" << endl;}

   else {cout << "It's a tie" << endl;}
}

