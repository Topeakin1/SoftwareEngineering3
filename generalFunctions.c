#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Assignment3Header.h"

// Generates a random integer from min to max inclusive.
int RandInt(int min, int max)
{
    max -= min;
    int upperBound = RAND_MAX - RAND_MAX % max;
    int randInt;

    do
    {
        randInt = rand();
    }while(randInt >= upperBound);

    randInt %= max + 1;
    
    randInt += min;

    return randInt;
}

// Takes a string input of a specified max length and returns it through returnString.
void UserInput(int maxLength, char *returnString)
{
    char *tempInput = malloc((maxLength + 1));
    do
    {
        printf("\n : ");
        
        tempInput[maxLength - 1] = '\0';
        fgets(tempInput, maxLength + 1, stdin);
        
        int i = 0;
        while(tempInput[i] != '\n' && tempInput[++i]);
        
        if(!tempInput[i])
        {
            while(getchar() != '\n');
            printf(" Input must be less than %d characters.", maxLength);
        }
        else
        {
            tempInput[i] = '\0';
        }
    }while(tempInput[maxLength - 1]);
    
    strcpy(returnString, tempInput);
}

// Uses UserInput to take a string input then converts it to a number that is then returned.
int NumberInput(int maxDigits)
{
    char *tempInput = malloc(maxDigits);
    char *endPtr;
    int returnNumber;
    
    do
    {
        UserInput(maxDigits + 1, tempInput);
    } while(!(returnNumber = strtol(tempInput, &endPtr, 10)) || *endPtr);
    
    return returnNumber;
}

// Prints the winner og the game, if any.
void EndOfGame(int playerCount, Player * players) 
{
	int i = 0;
	printf(" The game is over!\n");
	while(players[i].lifePoints<0 && ++i < playerCount);
        
    if(i < playerCount)
    {
        printf(" %s wins!\n",players[i].name);
    }
    else
    {
        printf(" Nobody is alive\n");
    }
    getchar();
}