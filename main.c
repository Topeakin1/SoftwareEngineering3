#include <stdio.h>
#include <time.h>
#include "Assignment3.h"

int main(void) {
	srand(time(NULL));
	Player players[PLAYER_MAX]; 
    
    
	int alivePlayers;
	int playersCount; 
	
	InputPlayerInfo(playersCount, players);
	NumberOfPlayers();
	Print(players, numberOfPlayers);
	movePlayer(player,slots, currentPosition, newPosition);
	PlayerAction( playerCount, slotCount, players, slots);
	PlayersInSlots(player);
	attackPlayer(attacker, attacked);
	   
	while (alivePlayers>=2) {
		alivePlayers= PlayersCount;
	    if(players[i].lifePoints==0) {
		  alivePlayers--;
		  printf("The %s is dead \n",players[i]);
	}
	GameRound( alivePlayers, Player);//function call
	     
	}
		 
		}
		
			
		}
	}
}
	
