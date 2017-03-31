#ifndef ASSIGNMENT2HEADER_H_
#define ASSIGNMENT2HEADER_H_

// Defined constant variables
#define PLAYER_MAX 6
#define SLOT_MAX 20
#define MAX_STRING_LENGTH 20

enum playerTypes{
    Elf,
    Human,
    Ogre,
    Wizard
};

// Structs for players and slots.
typedef struct Player{
    enum playerTypes type;
    char name[MAX_STRING_LENGTH];
    int lifePoints;
    int smartness;
    int strength;
    int magicSkill;
    int luck;
    int dexterity;
} Player;

typedef struct Slot{
    char slotType[MAX_STRING_LENGTH];
    int currentPlayer;
} Slot;



// Function prototypes.
int RandInt(int min, int max);

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
void FillSlotArray(int NumberOfSlots,struct Slot Slots[]);
int NumberOfSlots(int PlayersCount);
void PlayersNSlots(struct Slot Slots[],int NumberOfSlots);


#endif