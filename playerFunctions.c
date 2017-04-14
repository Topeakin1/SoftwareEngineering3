#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Assignment3Header.h"

//  Takes user input for the amount of players and returns that as a number.
int NumberOfPlayers()
{
    int numberOfPlayers;
    char tempInput[MAX_STRING_LENGTH];
    
    printf(" Input number of players");
    numberOfPlayers = NumberInput(1);
    // Takes a string as input and stores it as a nummber.
    
    while(numberOfPlayers < 2 || numberOfPlayers > PLAYER_MAX)
    {
        printf(" Number of players has to be between 2 and %d", PLAYER_MAX);
        numberOfPlayers = NumberInput(1);
    }
    // Makes sure the input is a number between 2 and the max amount of players.
    
    return numberOfPlayers;
}

/* 
 * Functions for generating player charactersistics.
 * Uses the RandInt(int x, int y) function to generate 
 * numbers from x to y inclusive.
 * Stores thexe numbers in the current player's characteristics.
*/
void ElfPlayer(Player *currentPlayer)
{
    currentPlayer->luck = RandInt(60, 100);
    currentPlayer->smartness = RandInt(70, 100);
    currentPlayer->strength = RandInt(1, 50);
    currentPlayer->magicSkill = RandInt(50, 80);
    currentPlayer->dexterity = RandInt(1, 100);
}

void HumanPlayer(Player *currentPlayer)
{
    unsigned int sum;
    do
    {
        sum = 0;
        currentPlayer->luck = RandInt(1, 100);
        currentPlayer->smartness = RandInt(1, 100);
        currentPlayer->strength = RandInt(1, 100);
        currentPlayer->magicSkill = RandInt(1, 100);
        currentPlayer->dexterity = RandInt(1, 100);
        sum = \
        currentPlayer->luck +\
        currentPlayer->smartness +\
        currentPlayer->strength +\
        currentPlayer->magicSkill +\
        currentPlayer->dexterity;
    }while(sum > 300);
}

void OgrePlayer(Player *currentPlayer)
{
    currentPlayer->smartness = RandInt(0, 20);
    currentPlayer->luck = RandInt(0, 50 - currentPlayer->smartness);
    currentPlayer->strength = RandInt(80, 100);
    currentPlayer->magicSkill = 0;
    currentPlayer->dexterity = RandInt(80, 100);
}

void WizardPlayer(Player *currentPlayer)
{
    currentPlayer->luck = RandInt(50, 100);
    currentPlayer->smartness = RandInt(90, 100);
    currentPlayer->strength = RandInt(1, 20);
    currentPlayer->magicSkill = RandInt(80, 100);
    currentPlayer->dexterity = RandInt(1, 100);
}

//   Takes input for each player and stores their info in the players array.
void InputPlayerInfo(int playerCount, Player * players)
{
    void (*playerTypes[4])(Player *currentPlayer) = \
    {ElfPlayer, HumanPlayer, OgrePlayer, WizardPlayer};
    // Array of pointers to functions for each player type. 
    
    char tempInput[MAX_STRING_LENGTH];
    int j;
    
    for(int i = 0; i < playerCount; i++)
    {
        do{
            printf("\n Player %d \n\n Input player name", i + 1);
            UserInput(MAX_STRING_LENGTH, players[i].name);
        }while(!players[i].name[0]);
        // Take a string as input and assign it to the name of the current player.
        
        
        printf("\n Chose a player type: \
                    \n 1. Elf\
                    \n 2. Human\
                    \n 3. Ogre\
                    \n 4. Wizard ");
                    
        do
        {
            players[i].type = NumberInput(1) - 1;
        }while(players[i].type < 0 || players[i].type > 3);
        // Player choses a number between 1 and 4 and if it is valid, that player type gets chosen.
        
        playerTypes[players[i].type](&players[i]);
        players[i].lifePoints = 100;
        // Calls the player type function and sets player life to 100;
    }
}

void PlayersInSlots(Player *player) {
	player->playerPosition = malloc(sizeof(Position)); 
	player->playerPosition->row=RandInt(0, 6);
	player->playerPosition->column= RandInt(0,6);
	
}

void PlacePlayersInRandomSlots(int playerCount, Player *players, Slot **corners)
{
    Player * currentPlayer;
    for(int i = 0; i <  playerCount; i++)
    {
        currentPlayer = &players[i];
        PlayersInSlots(currentPlayer);
        AddPlayerToSlot(currentPlayer, FindSlot(currentPlayer->playerPosition, corners));
    }
}


void PrintOnePlayer(Player *currentPlayer)
{
    char *playerTypes[4] = {"Elf", "Human", "Ogre", "Wizard"};
    
    printf(" %s\n", currentPlayer->name); 
    if(currentPlayer->lifePoints > 0)
    {
        printf(" Life: %d", currentPlayer->lifePoints);
    }
    else if(currentPlayer->lifePoints == -1)
    {
        printf(" Dead");
    }
    else if(currentPlayer->lifePoints == -2)
    {
        printf(" Quit");
    }
    printf("\n Type: %s\n", playerTypes[currentPlayer->type]);
    printf(" Smartness: %d\n", currentPlayer->smartness);
    printf(" Strength: %d\n", currentPlayer->strength);
    printf(" Magic Skill: %d\n", currentPlayer->magicSkill);
    printf(" Luck: %d\n", currentPlayer->luck);
    printf(" Dexterity: %d\n\n", currentPlayer->dexterity);
}


void PrintAllPlayers(Player *players, int numberOfPlayers) {
    
    char *playerTypes[4] = {"Elf", "Human", "Ogre", "Wizard"};
    
    puts("");
	for(int i=0; i<numberOfPlayers; i++) {
		PrintOnePlayer(&(players[i]));
	}
}



enum Direction GetMoveDirection()
{
    int inputNumber;
    do
    {
        printf("\n Where do you want to move?\n 1. Up\n 2. Down\n 3. Left\n 4. Right\n 5. Back");
        inputNumber = NumberInput(1) - 1;
    }while(inputNumber < 0 || inputNumber > 4);
    return inputNumber;
}

// Swaps player position and adjusts their capabilities.
int MovePlayer(Player *player, Slot *currentSlot)
{
    Slot *tempSlot;
    enum Direction moveDirection = GetMoveDirection();
    switch(moveDirection)
    {
        case up:
        tempSlot = currentSlot->up;
        break;
        case down:
        tempSlot = currentSlot->down;
        break;
        case left:
        tempSlot = currentSlot->left;
        break;
        case right:
        tempSlot = currentSlot->right;
        break;
        default:
        return 0;
        break;
    }
    
    
    if(tempSlot)
    {
        RemovePlayerFromSlot(player, currentSlot);
        currentSlot = tempSlot;
        AddPlayerToSlot(player, currentSlot);
        
        if(!strcmp(currentSlot->slotType, "Hill"))
        {
            if(player->dexterity < 50)
            {
                if(player->strength < 10)
                {
                    player->strength = 0;
                    printf(" You lost all of your strength!\n");
                }
                else
                {
                    player->strength -= 10;
                    printf(" You lost 10 of your strength!\n");
                }
            }
            else if(player->dexterity >= 60)
            {
                if(player->strength > 90)
                {
                    player->strength = 100;
                    printf(" You gained maximum strength!\n");
                }
                else
                {
                    player->strength += 10;
                    printf(" You gained 10 strength!\n");
                }
            }
            else
            {
                puts("");
            }
        }
        else if(currentSlot->slotType, "City")
        {
            if(player->smartness <= 50)
            {
                if(player->magicSkill < 10)
                {
                    player->magicSkill = 0;
                    printf(" You lost all of your magic skill!\n");
                }
                else
                {
                    player->magicSkill -= 10;
                    printf(" You lost 10 of your magic skill!\n");
                }
            }
            else if(player->smartness > 60)
            {
                if(player->magicSkill > 90)
                {
                    player->magicSkill = 100;
                    printf(" You gained maximum magic skill!\n");
                }
                else
                {
                    player->magicSkill += 10;
                    printf(" You gained 10 magic skill!\n");
                }
            }
            else
            {
                puts("");
            }
        }
        else
        {
            puts("");
        }
        return 1;
    }
    else
    {
        printf("Unable to move in that direction.\n");
        return 0;
    }
}




void DealDamage(Player * player, int damage, Slot **corners)
{
    if(player->lifePoints > damage)
    {
        player->lifePoints -= damage;
        
        printf("\n %s lost %d life points!\n", player->name, damage);
    }
    else
    {
        printf("\n %s lost %d life points!\n", player->name, player->lifePoints);
        player->lifePoints = 0;
        printf(" %s has died!\n", player->name);
        RemovePlayerFromSlot(player, FindSlot(player->playerPosition, corners));
    }
}

int NearAttack(Player * player, Slot *playerPosition, Slot **corners)
{
    int nearbyPlayers = 0;
    int explored[BOARD_SIZE][BOARD_SIZE];
    Slot ** foundSlots = malloc(PLAYER_MAX);
    int attackOptions = 0;
    Player **playersToAttack = malloc(PLAYER_MAX);
    int playerChoice;
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            explored[i][j] = 0;
        }
    }
    
    AttackSearch(1, 0, playerPosition, foundSlots, &nearbyPlayers, explored);
    
    
    for(int i = 0; i < nearbyPlayers; i++)
    {
        for(int j = 0; j < foundSlots[i]->currentPlayerCount; j++)
        {
            if(foundSlots[i]->currentPlayers[j] != player)
            {
                playersToAttack[attackOptions++] = foundSlots[i]->currentPlayers[j];
                printf(" %d Attack %s \n", attackOptions, foundSlots[i]->currentPlayers[j]->name);
            }
        }
    }
    
    if(attackOptions > 0)
    {
        printf(" %d Back", ++attackOptions);
        do
        {
            playerChoice = NumberInput(1);
        }while(playerChoice <= 0 || playerChoice > attackOptions);
        
        if(playerChoice != attackOptions)
        {
            if(playersToAttack[--playerChoice]->strength <= 70)
            {
                DealDamage(playersToAttack[playerChoice], player->strength / 2, corners);
            }
            else
            {
                DealDamage(player, playersToAttack[playerChoice]->strength * 3 / 10, corners);
            }
            return 1;
        }
    }
    else
    {
        puts(" No players in range.");
        getchar();
    }
    return 0;
}

int DistantAttack(Player * player, Slot *playerPosition, Slot **corners)
{
    int nearbyPlayers = 0;
    int explored[BOARD_SIZE][BOARD_SIZE];
    Slot ** foundSlots = malloc(PLAYER_MAX);
    int attackOptions = 0;
    Player **playersToAttack = malloc(PLAYER_MAX);
    int playerChoice;
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            explored[i][j] = 0;
        }
    }
    
    AttackSearch(4, 0, playerPosition, foundSlots, &nearbyPlayers, explored);
    
    
    for(int i = 0; i < nearbyPlayers; i++)
    {
        for(int j = 0; j < foundSlots[i]->currentPlayerCount; j++)
        {
            if(foundSlots[i]->currentPlayers[j] != player)
            {
                playersToAttack[attackOptions++] = foundSlots[i]->currentPlayers[j];
                printf(" %d Attack %s \n", attackOptions, foundSlots[i]->currentPlayers[j]->name);
            }
        }
    }
    
    if(attackOptions > 0)
    {
        printf(" %d Back", ++attackOptions);
        do
        {
            playerChoice = NumberInput(1);
        }while(playerChoice <= 0 || playerChoice > attackOptions);
        
        if(playerChoice != attackOptions)
        {
            if(playersToAttack[--playerChoice]->dexterity < player->dexterity)
            {
                DealDamage(playersToAttack[playerChoice], player->strength * 3 / 10, corners);
            }
            else
            {
                printf(" %s dodged!\n", playersToAttack[playerChoice]->name);
            }
            return 1;
        }
    }
    else
    {
        puts(" No players in range.");
        getchar();
    }
    return 0;
}

int MagicAttack(Player * players, int playerCount, Player * currentPlayer, Slot *playerPosition, Slot **corners)
{
    int playerChoice;
    int attackOptions = 0;
    Player ** aliveOtherPlayers = malloc(5);
    if(aliveOtherPlayers)
    {
        for(int i = 0; i < playerCount; i++)
        {
            if(&(players[i]) != currentPlayer && players[i].lifePoints > 0)
            {
                aliveOtherPlayers[attackOptions++] = &(players[i]);
                printf(" %d Attack %s\n", attackOptions, aliveOtherPlayers[attackOptions - 1]->name);
            }
        }
        
        
        if(attackOptions > 0)
        {
            printf(" %d Back", ++attackOptions);
            do
            {
                playerChoice = NumberInput(1);
            }while(playerChoice <= 0 || playerChoice > attackOptions);
            
            
            if(playerChoice != attackOptions)
            {
                DealDamage(aliveOtherPlayers[playerChoice - 1], currentPlayer->magicSkill / 2 + currentPlayer->smartness / 5, corners);
                return 1;
            }
        }
        else
        {
            puts(" No other players alive\n");
            getchar();
        }
    }
    return 0;
}

int AttackChoice(Player * players, int playerCount, Player * currentPlayer, Slot *playerPosition, Slot **corners)
{
    int magicAttackAvailable = (currentPlayer->magicSkill + currentPlayer->smartness) >150;
    int choice;
    
    printf("\n 1 Near Attack\n 2 Distant Attack\n");
    if(magicAttackAvailable)
    {
        printf(" 3 Magic Attack\n 4 Back");
    }
    else
    {
        printf(" 3 Back");
    }
    
    do
    {
        choice = NumberInput(1);
    }while(choice <= 0 || choice > 3 + magicAttackAvailable);
    
    switch(choice)
    {
        case 1:
        return NearAttack(currentPlayer, playerPosition, corners);
        break;
        case 2:
        return DistantAttack(currentPlayer, playerPosition, corners);
        break;
        case 3:
        if(magicAttackAvailable)
        {
            return MagicAttack(players, playerCount, currentPlayer, playerPosition, corners);
            break;
        }
        default:
        break;
    }
    return 0;
}


void GameRound(int playerCount, int *alivePlayers, Player * players, Slot **corners) 
{ 
    int choice;
    Slot * playerPosition;
	for(int i=0; i < playerCount; i++) 
    {
	    if(players[i].lifePoints>0) 
        {
            choice = 0;
            playerPosition = FindSlot(players[i].playerPosition, corners);
            while(choice == 0)
            {
                printf("\n Player %d (%d, %d)\n %s\n 1 to attack\n 2 to move\n 3 to quit", i + 1, players[i].playerPosition->row + 1, players[i].playerPosition->column + 1, players[i].name);
                choice = NumberInput(1);
                switch(choice)
                {
                    case 1:
                    choice = AttackChoice(players, playerCount, &players[i], playerPosition, corners);
                    break;
                    case 2:
                    choice = MovePlayer(&players[i], playerPosition);
                    break;
                    case 3:
                    printf(" %s has quit the game.\n",players[i].name);
                    players[i].lifePoints = -2;
                    (*alivePlayers)--;
                    RemovePlayerFromSlot(&players[i], playerPosition);
                    break;
                    default:
                    choice = 0;
                    break;
                }
            }
		}
        else if(players[i].lifePoints==0)
        {
            printf("\n %s is dead \n",players[i].name);
        }
        
        if(players[i].lifePoints==0) 
        {
	      players[i].lifePoints=-1;	
		  (*alivePlayers)--; 
        }
	}
}


