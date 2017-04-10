#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Assignment2Header.h"


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
            board[row][column].slotType, board[row][column + 1].slotType);
        }
    }
    
    // Stores the four corners.
    (*boardCorners)[0] = &board[0][0];
    (*boardCorners)[1] = &board[0][BOARD_SIZE - 1];
    (*boardCorners)[2] = &board[BOARD_SIZE - 1][BOARD_SIZE - 1];
    (*boardCorners)[3] = &board[BOARD_SIZE - 1][0];
}


// Returns a pointer to a slot on the board based on it's coordinates.
Slot *findSlot(Position *slotPosition, Slot ** boardCorners)
{
    // Creates a new pointer to a slot and sets it to the corner closest to the slot we are looking for.
    Slot * currentSlot;
    if(slotPosition->row < BOARD_SIZE/2)
    {
        if(slotPosition->column < BOARD_SIZE/2)
        {
            currentSlot = boardCorners[0];
        }
        else
        {
            currentSlot = boardCorners[1];
        }
    }
    else
    {
        if(slotPosition->column < BOARD_SIZE/2)
        {
            currentSlot = boardCorners[3];
        }
        else
        {
            currentSlot = boardCorners[2];
        }
    }
    
    // Goes through the slots of the board until it finds the slot corresponding to the correct position.
    while(slotPosition->row != currentSlot->slotPosition->row || slotPosition->column != currentSlot->slotPosition->column)
    {
        if(slotPosition->row < currentSlot->slotPosition->row)
        {
            currentSlot = currentSlot->up;  
        }
        
        if(slotPosition->row > currentSlot->slotPosition->row)
        {
            currentSlot = currentSlot->down; 
        }
        
        if(slotPosition->column < currentSlot->slotPosition->column)
        {
            currentSlot = currentSlot->left; 
        }
        
        if(slotPosition->column > currentSlot->slotPosition->column)
        {
            currentSlot = currentSlot->right; 
        }
    }
    // Returns a pointer to the slot we found.
    return currentSlot;
}
