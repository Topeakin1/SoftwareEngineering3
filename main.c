#include <stdio.h>
#include <time.h>
#include "Assignment3.h"

int main(void) {
	srand(time(NULL));
	Player players[PLAYER_MAX]; 
    
    
	int alivePlayers;
	int playersCount; 
	   
	while (alivePlayers>=2) {
		alivePlayers= PlayersCount;
	    if(players[i].lifePoints==0) {
		  alivePlayers--;
		  printf("The %s is dead \n",players[i]);
	}
	
	
	      for(i=0; i<playersCount; i++) {
		    if(players[i].lifePoints>0) {
			printf("Enter 1 to attack 2 to quit 3 to move\n");
			scanf(%d,&choice);
			if(choice==1) {
				attackPlayer(*attacker,*attacked);
			} 
			else if(choice==3) {
				 movePlayer(*player,*slots, currentPosition, newPosition);
			} 
			else(choice==2) {
				//quit
			}
		}
		
			puts(" ");
		}
	}
		 
		}
		
			
		}
	}
}
	
