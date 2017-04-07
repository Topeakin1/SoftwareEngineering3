#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Assignment2Header.h"


void PlayersNSlots(struct Slot Slots[],int NumberOfSlots)
{
	int i, j;
	for(i=0; i<NumberOfSlots; i++) 
	{
		Slots[i].currentPlayer=0;
	}
	
	for(i=1; i<NumberOfSlots; i++)
	{
        do
        {
		j=rand() % NumberOfSlots;
        }while(Slots[j].currentPlayer != 0);
		Slots[j].currentPlayer = i;
	}
}


/* Functiion to create the game board. 
 I am thinking we store the four corners in an array that we pass into the 
 function through a three dimentional pointer.
 */
void createBoard(Slot ***boardCorners)
{
    // Alocates the board to store one column.
    Slot ** board = malloc(BOARD_SIZE * sizeof(Slot *));
    // Stores possible slot types.
    char *slotTypes[3] = {"Level Ground","Hill","City"};
    
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        board[row] = malloc(BOARD_SIZE * sizeof(Slot));
        // Alocates each element in the column to store a row.
        
        for(int column = 0; column < BOARD_SIZE; column++)
        {
            board[row][column].slotPosition = malloc(sizeof(Position));
            *(board[row][column].slotPosition) = (Position){row, column};
            strcpy(board[row][column].slotType, slotTypes[RandInt(0, 2)]);
            // Gives every slot the correct position.
        }
    }
    
    // Connects each element of a each row except the last with the element directly below it. 
    for(int row = 0; row < BOARD_SIZE - 1; row++)
    {
        for(int column = 0; column < BOARD_SIZE; column++)
        {
            board[row][column].down = &board[row + 1][column];
            board[row + 1][column].up = &board[row][column];
            printf("(%d, %d) %s\n   ^\n   |\n(%d, %d) %s\n", board[row][column].slotPosition->row, board[row][column].slotPosition->column,\
            board[row][column].slotType, board[row + 1][column].slotPosition->row, board[row + 1][column].slotPosition->column, board[row + 1][column].slotType);
        }
    }
    
    // Connects each element of a each column except the last with the element directly to the right of it. 
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int column = 0; column < BOARD_SIZE - 1; column++)
        {
            board[row][column].right = &board[row][column + 1];
            board[row][column + 1].left = &board[row][column];
            printf("(%d, %d) -> (%d, %d)\n %s -> %s\n", board[row][column].slotPosition->row, board[row][column].slotPosition->column, board[row][column + 1].slotPosition->row, board[row][column + 1].slotPosition->column,\
            board[row][column].slotType, board[row][column + 1].slotType);
        }
    }
    
    // Stores the four corners.
    (*boardCorners)[0] = &board[0][0];
    (*boardCorners)[1] = &board[0][BOARD_SIZE - 1];
    (*boardCorners)[2] = &board[BOARD_SIZE - 1][BOARD_SIZE - 1];
    (*boardCorners)[3] = &board[BOARD_SIZE - 1][0];
}

