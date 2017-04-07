#ifndef ASSIGNMENT3HEADER_H_
#define ASSIGNMENT3HEADER_H_

// Defined constant variables
#define PLAYER_MAX 6
#define MAX_STRING_LENGTH 20
#define BOARD_SIZE 7

enum playerTypes{
    Elf,
    Human,
    Ogre,
    Wizard
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
    enum playerTypes type;
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

// Player functions
int NumberOfPlayers();
void InputPlayerInfo(int playerCoutn, Player * players);
void ElfPlayer(Player *currentPlayer);
void HumanPlayer(Player *currentPlayer);
void OgrePlayer(Player *currentPlayer);
void WizardPlayer(Player *currentPlayer);
void PlayerAction(int playerCount, int slotCount, Player *players, Slot *slots);
void movePlayer(Player *player, Slot *slots, int currentPosition, int newPosition);
void attackPlayer(Player *attacker, Player *attacked);
void Print(Player *players, int numberOfPlayers);

// Slot functions
void createBoard(Slot ***boardCorners);
void PlayersNSlots(struct Slot Slots[],int NumberOfSlots);


#endif