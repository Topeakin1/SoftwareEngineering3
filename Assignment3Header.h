#ifndef ASSIGNMENT3HEADER_H_
#define ASSIGNMENT3HEADER_H_

// Defined constant variables
#define PLAYER_MAX 6
#define MAX_STRING_LENGTH 20
#define BOARD_SIZE 7

enum PlayerTypes{
    Elf,
    Human,
    Ogre,
    Wizard
};

enum Direction{
    up,
    down,
    left,
    right
};

// Struct for board positions.
typedef struct Position
{
    int row;
    int column;
} Position;

// Structs for players and slots.
typedef struct Player
{
    enum PlayerTypes type;
    char name[MAX_STRING_LENGTH];
    int lifePoints;
    int smartness;
    int strength;
    int magicSkill;
    int luck;
    int dexterity;
    
    Position *playerPosition;
} Player;

typedef struct Slot
{
    Player ** currentPlayers;
    int currentPlayerCount;
    char slotType[MAX_STRING_LENGTH];
    
    Position *slotPosition;
    
    struct Slot * up;
    struct Slot * down;
    struct Slot * left;
    struct Slot * right;
} Slot;



// Function prototypes.
int RandInt(int min, int max);
void UserInput(int maxLength, char *returnString);
int NumberInput(int maxDigits);
void EndOfGame(int playerCount, Player * players);

// Player functions
int NumberOfPlayers();
void InputPlayerInfo(int playerCoutn, Player * players);
void PlacePlayersInRandomSlots(int playerCount, Player *players, Slot **corners);
void GameRound(int playerCount, int *alivePlayers, Player * players, Slot **corners);
void PrintAllPlayers(Player *players, int numberOfPlayers);

// Slot functions
void CreateBoard(Slot ***boardCorners);
void PlayersNSlots(struct Slot Slots[],int NumberOfSlots);
Slot *FindSlot(Position *slotPosition, Slot ** boardCorners);
void AddPlayerToSlot(Player * player, Slot * slot);
void RemovePlayerFromSlot(Player * player, Slot * slot);
void AttackSearch(int reqDist, int currDist, Slot * currentSlot, Slot ** foundSlots, int * count, int explored[BOARD_SIZE][BOARD_SIZE]);

#endif
