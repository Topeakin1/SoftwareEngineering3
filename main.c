#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Assignment3Header.h"


int main(void) {
	srand(time(NULL));
    
    // Array that stores all the players.
	Player players[PLAYER_MAX]; 
    
	// Array of size 4 to hold 4 pointers to the corners of the board.
    Slot **corners = malloc(sizeof(Slot*) * 4); 
    int i;
	int alivePlayers;
	int playersCount; 
	
	CreateBoard(&corners); // Creates a 7x7 board and returns the four corners through 
    
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
