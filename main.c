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
		if(players[i].lifePoints>0) {
			printf("Enter 1 to attack 2 to quit 3 to move\n");
			scanf(%d,&choice);
			if(choice==1) {
				//attack function
			} 
			else if(choice==3) {
				//move function
			} 
			else(choice==2) {
				//quit
			}
		}
		
			puts(" ");
		}
	}
}
	
