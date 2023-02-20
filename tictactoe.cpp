/*
    TIC-TAC-TOE - 24/10/2022
*/ 


#include <iostream>
#include "ai.h"

using namespace std;


// GAME
bool GetGameMode();
void DrawBoard();
void PlayerInput(int p);
bool CheckLines(int p);
bool CheckHorizontalLines(int p);
bool CheckVerticalLines(int p);
bool CheckDiagonalLines(int p);


Board board;
char pSymbols[2] = {'X', 'O'};

int main(int argc, char *argv[])
{
    system("CLS");
    bool singleplayer = GetGameMode();

    // MAIN LOOP
    int moves = 0;
    while (board.playing)
    {
        for (int p = 0; p < 2; p++) // iterate on players
        {
            DrawBoard();
            
            if (!singleplayer || p == 0) PlayerInput(p);
            else AiInput(board, pSymbols[1]);
            moves++;

            if (CheckLines(p))
            {
                DrawBoard();
                cout << "Player " << p+1 << " wins!" << endl << endl;
                board.playing = false;
                break;
            }
            if (moves > 8)
            {
                DrawBoard();
                cout << "Draw!" << endl << endl;
                board.playing = false;
                break;
            }
        }
    }
    return 0;
}

bool GetGameMode()
{
    char mode;
    while (tolower(mode) != 's' && tolower(mode) != 'm')
    {
        cout << "(S)ingleplayer or (M)ultiplayer? ";
        cin >> mode;
        if (tolower(mode) != 's' && tolower(mode) != 'm') 
        {
            system("CLS");
            cout << "Only 's' and 'm' are valid inputs" << endl;
        }
    }
    
    if (tolower(mode) == 's') return true;    
    return false;
}

void DrawBoard()
{
    system("CLS");
    cout << "Tic-Tac-Toe v 0.2" << endl << endl;
    string borderString = "  -+-+-";
    cout << "  A B C" << endl;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
                cout << j+1 << " ";
            cout << board.tiles[i][j];
            if (i != 2) 
            {
                cout << '|';
            }
            else if (j != 2)
            {
                cout << endl << borderString << endl;
            }
        }
    }
    cout << endl << endl;
    return;
}

void PlayerInput(int p)
{
    string input;
    bool validMove = false;
    int col, row;
    while (!validMove)
    {
        cout << "Player " << p+1 << ", enter your move: ";
        cin >> input;
        if (input.length() != 2 || !isalpha(input[0])|| !isdigit(input[1])) // one letter, one digit
        {
            cout << "Must be 1 letter followed by 1 digit" << endl;
            continue;
        }    

        col = tolower(input[0]) - 97;
        if (col < 0 || col > 2)
        {
            cout << "Letter must be A, B or C" << endl;
            continue;
        }

        row = int(input[1]) - 49;
        if (row < 0 || row > 2)
        {
            cout << "Number must be 1, 2 or 3" << endl;
            continue;
        }

        if (board.tiles[col][row] != ' ')
        {
            cout << "Tile must be empty" << endl;
            continue;
        }

        break;
    }
    board.tiles[col][row] = pSymbols[p];
    return;
}

bool CheckLines(int p)
{
    if (CheckHorizontalLines(p) ||
        CheckVerticalLines(p) ||
        CheckDiagonalLines(p))
        return true;
    return false;
}

bool CheckHorizontalLines(int p)
{
    int sequence = 0;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board.tiles[i][j] == pSymbols[p]) sequence++;
            if (sequence == 3) return true;
        }
        sequence = 0;
    }
    return false;
}

bool CheckVerticalLines(int p)
{
    int sequence = 0;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.tiles[i][j] == pSymbols[p]) sequence++;
            if (sequence == 3) return true;
        }
        sequence = 0;
    }
    return false;
}

bool CheckDiagonalLines(int p)
{
    if (board.tiles[0][0] == pSymbols[p] && board.tiles[1][1] == pSymbols[p] && board.tiles[2][2] == pSymbols[p]) 
        return true;
    if (board.tiles[0][2] == pSymbols[p] && board.tiles[1][1] == pSymbols[p] && board.tiles[2][0] == pSymbols[p]) 
        return true;
    return false;
}
