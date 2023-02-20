/*
    AI FOR TIC-TAC-TOE
*/

#include "board.h"



void AiInput(Board &board, char aiSymbol);
bool CheckCenter(Board &board, char aiSymbol);
bool CheckSelf(Board &board, char aiSymbol);
bool CheckOpponent(Board &board, char aiSymbol);
bool CheckSingle(Board &board, char aiSymbol);
int CheckTile(char symbol, int pSymbol);

void AiInput(Board &board, char aiSymbol)
{
    if (!CheckSelf(board, aiSymbol))
        if (!CheckOpponent(board, aiSymbol))
            if (!CheckCenter(board, aiSymbol))
                if(!CheckSingle(board, aiSymbol))
                    return;
}

// PLACE TILE IN CENTER OF BOARD IF EMPTY
bool CheckCenter(Board &board, char aiSymbol)
{
    if (board.tiles[1][1] == ' ')
    {
        board.tiles[1][1] = aiSymbol;
        return true;
    }    
    return false;
}

// CHECK IF AI CAN PLACE A SINGLE TILE TO WIN THE GAME
bool CheckSelf(Board &board, char aiSymbol) 
{
    // VERTICAL
    int sequence = 0;
    for (int i = 0; i < 3; i++)
    {
        int empty = -1;
        for (int j = 0; j < 3; j++)
        {
            if (board.tiles[i][j] == aiSymbol) sequence++;
            else
            {
                if (board.tiles[i][j] == ' ') empty = j;
                else break;
            }

            if (sequence == 2)
            {
                if (empty == -1 && board.tiles[i][2] == ' ') empty = 2;
                else if (empty == -1) break;
                board.tiles[i][empty] = aiSymbol;
                return true;
            }
        }
        sequence = 0;
    }

    // HORIZONTAL
    sequence = 0;
    for (int j = 0; j < 3; j++)
    {
        int empty = -1;
        for (int i = 0; i < 3; i++)
        {
            if (board.tiles[i][j] == aiSymbol) sequence++;
            else
            {
                if (board.tiles[i][j] == ' ') empty = j;
                else break;
            }

            if (sequence == 2)
            {
                if (empty == -1 && board.tiles[2][j] == ' ') empty = 2;
                else if (empty == -1) break;
                board.tiles[empty][j] = aiSymbol;
                return true;
            }
        }
        sequence = 0;
    }
    
    // DIAGONAL
    if (board.tiles[0][0] == aiSymbol && board.tiles[1][1] == aiSymbol && board.tiles[2][2] == ' ') 
    {
        board.tiles[2][2] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][0] == ' ' && board.tiles[1][1] == aiSymbol && board.tiles[2][2] == aiSymbol) 
    {
        board.tiles[0][0] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][2] == aiSymbol && board.tiles[1][1] == aiSymbol && board.tiles[2][0] == ' ') 
    {
        board.tiles[2][0] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][2] == ' ' && board.tiles[1][1] == aiSymbol && board.tiles[2][0] == aiSymbol) 
    {
        board.tiles[0][2] = aiSymbol;
        return true;
    }

    return false;
}

// CHECK IF AI CAN PLACE A SINGLE TILE TO PREVENT PLAYER FROM WINNING
bool CheckOpponent(Board &board, char aiSymbol)
{
    // VERTICAL
    int sequence = 0;
    for (int i = 0; i < 3; i++)
    {
        int empty = -1;
        for (int j = 0; j < 3; j++)
        {
            if (board.tiles[i][j] != aiSymbol && board.tiles[i][j] != ' ') sequence++;
            else
            {
                if (board.tiles[i][j] == ' ') empty = j;
                else break;
            }

            if (sequence == 2)
            {
                if (empty == -1 && board.tiles[i][2] == ' ') empty = 2;
                else if (empty == -1) break;
                board.tiles[i][empty] = aiSymbol;
                return true;
            }
        }
        sequence = 0;
    }

    // HORIZONTAL
    sequence = 0;
    for (int j = 0; j < 3; j++)
    {
        int empty = -1;
        for (int i = 0; i < 3; i++)
        {
            if (board.tiles[i][j] != aiSymbol && board.tiles[i][j] != ' ') sequence++;
            else
            {
                if (board.tiles[i][j] == ' ') empty = i;
                else break;
            }

            if (sequence == 2)
            {
                if (empty == -1 && board.tiles[2][j] == ' ') empty = 2;
                else if (empty == -1) break;
                board.tiles[empty][j] = aiSymbol;
                return true;
            }
        }
        sequence = 0;
    }

    // DIAGONAL
    if (board.tiles[0][0] != aiSymbol && board.tiles[0][0] != ' ' && 
        board.tiles[1][1] != aiSymbol && board.tiles[1][1] != ' ' && 
        board.tiles[2][2] == ' ') 
    {
        board.tiles[2][2] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][0] == ' ' && 
        board.tiles[1][1] != aiSymbol && board.tiles[1][1] != ' ' && 
        board.tiles[2][2] != aiSymbol && board.tiles[2][2] != ' ') 
    {
        board.tiles[0][0] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][2] != aiSymbol && board.tiles[0][2] != ' ' && 
        board.tiles[1][1] != aiSymbol && board.tiles[1][1] != ' ' && 
        board.tiles[2][0] == ' ') 
    {
        board.tiles[2][0] = aiSymbol;
        return true;
    }
    else if (board.tiles[0][2] == ' ' && 
        board.tiles[1][1] != aiSymbol && board.tiles[1][1] != ' ' && 
        board.tiles[2][0] != aiSymbol && board.tiles[2][0] != ' ') 
    {
        board.tiles[0][2] = aiSymbol;
        return true;
    }
    return false;
}

// PLACES IT IN THE FIRST EMPTY TILE IT FINDS
bool CheckSingle(Board &board, char aiSymbol)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.tiles[i][j] == ' ')
            {
                board.tiles[i][j] = aiSymbol;
                return true;
            }
        }
    }
    return false;
}

int CheckTile(char symbol, int pSymbol) 
{
    if (symbol == ' ') return 0;  // empty tile
    else if (symbol == pSymbol) return 1;  // own symbol
    else return -1;  // opponent's symbol
}
