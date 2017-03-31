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
