#include <stdio.h>
#include <time.h>
#include "Assignment3.h"

int main(void) {
	srand(time(NULL));
	Player players[PLAYER_MAX]; 
    Slot slots[SLOT_MAX];
    
	int slotsCount;
	int playersCount;    
	
	for(i=0; i<playersCount; i++) {
		if(players[i].lifePoints == 0) {
			printf("Unfortunately this player is dead\n");
		}
		else {
			puts(" ")
		}
	}
}
	
