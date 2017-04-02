#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Assignment2Header.h"

void FillSlotArray(int NumberOfSlots,struct Slot Slots[]) {
	char SlotTypes[3][15] = {"Level Ground","Hill","City"};
	int i, random;
	srand(time(NULL));
	
	for(i=0; i<NumberOfSlots; i++) {
		random=rand() %3;
		strcpy(Slots[i].slotType,SlotTypes[random]); //assigning my slots
	}
	for(i=0; i<NumberOfSlots; i++) {
		printf("| %s |\n", Slots[i].slotType); //printing out to check
	}
	
}

int NumberOfSlots(int PlayersCount) {
	int reply;
    char tempInput[MAX_STRING_LENGTH];
	
	printf("Please enter the number of slots between %d and 20\n", PlayersCount);
	do
    {
        printf("  : ");
        fgets(tempInput, MAX_STRING_LENGTH - 1, stdin);
        reply = strtol(tempInput, NULL, 10);
	}while(reply < PlayersCount || reply > SLOT_MAX);
	return reply;
}

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
    
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        board[row] = malloc(BOARD_SIZE * sizeof(Slot));
        // Alocates each element in the column to store a row.
        
        for(int column = 0; column < BOARD_SIZE; column++)
        {
            board[row][column].slotPosition = malloc(sizeof(Position));
            *(board[row][column].slotPosition) = (Position){row, column};
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
        }
    }
    
    // Connects each element of a each column except the last with the element directly to the right of it. 
    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int column = 0; column < BOARD_SIZE - 1; column++)
        {
            board[row][column].right = &board[row][column + 1];
            board[row][column + 1].left = &board[row][column];
        }
    }
    
    
    // Stores the four corners.
    (*boardCorners)[0] = &board[0][0];
    (*boardCorners)[1] = &board[0][BOARD_SIZE - 1];
    (*boardCorners)[2] = &board[BOARD_SIZE - 1][BOARD_SIZE - 1];
    (*boardCorners)[3] = &board[BOARD_SIZE - 1][0];
}

