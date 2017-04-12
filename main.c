#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Assignment3Header.h"

int main(void) {
	srand(time(NULL));
	Player players[PLAYER_MAX]; 
	
     
    Slot **corners ==malloc(4); //not sure what your asking me to do here modify if neccesary
    int i;
	int alivePlayers;
	int playersCount; 
	
	createBoard(Slot ***boardCorners); //
	InputPlayerInfo(playersCount, players);
	playersCount=NumberOfPlayers();
	PlayerAction( playerCount, slotCount, players, slots);
	PlayersInSlots(player); //dont think we need this one anymore didnt remove just incase?
	PlacePlayersInRandomSlots(playerCount, *players, **corners)
	   
	while (alivePlayers>=2) {
		alivePlayers= playersCount;
	    if(players[i].lifePoints==0) {
	      printf("The %s is dead \n",players[i]);
	      players[i].lifepoints=-1;	
		  alivePlayers--; 
	}
	else {
		GameRound( alivePlayers, Player);//function call
	}
	 
	}
	Print(players, numberOfPlayers);	 
}
		
			
	
	
