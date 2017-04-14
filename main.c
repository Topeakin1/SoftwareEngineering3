#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Assignment3Header.h"

int main(void) {
	srand(time(NULL));
	Player players[PLAYER_MAX]; 
	
    Slot **corners = malloc(4); 
    int i;
	int alivePlayers;
	int playersCount; 
	
	CreateBoard(&corners); //
    
	playersCount = NumberOfPlayers();
	alivePlayers = playersCount;
	InputPlayerInfo(playersCount, players);
    
	PlacePlayersInRandomSlots(playersCount, players, corners);
    
	PrintAllPlayers(players, playersCount);	
    
	while (alivePlayers>=2) 
    {
        GameRound(playersCount, &alivePlayers, players, corners);
	}
	PrintAllPlayers(players, playersCount);	 
    EndOfGame(playersCount, players);
}
