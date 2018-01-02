#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define minPlayers 2
#define maxPlayers 10
#define gameRounds 13

typedef struct {
	int playerScore;
	int playerHand[13];
	int currentChoice;
	char playerInitials[2];
}player;

player card_player[10];

void displayPlayerHand(int playerNumber);
int getPlayerCardSelection(int playerNumber);
void dispenseCards();
void displayAllCards();
void clearScreen();
void runGame(int numberOfUsers);
char initialsInput(int playerNumber, int numberOfUsers);

int runningTotalScore; //While game is underway

void main() {
	//Variables

	int numberOfUsers;
	int i, j;
	int roundCounter;
	//int deckOfCards[52] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14 };

	//Setting up the game=========================================================================================
	//Header output

	printf("-------WAR-------\n");
	printf("   -----------\n\n\n");


	//Main game options here


	//Populate player decks --> Generate random numbers 1-13 --> Use as card score
	dispenseCards();

	//Display all player hands --> Made to check if working
	//displayAllCards();

	//Playing the game============================================================================================
	printf("[2-10 players]\n--> ");
	scanf("%d", &numberOfUsers);
	
	printf("-------WAR-------\n");
	printf("   -----------\n");

	runGame(numberOfUsers);

	printf("\n\n===============================\n\n");
	//Print end score for each active player
	for (i = 0; i < numberOfUsers; i++) {
		printf("*** Player%2d\n*** Score: %4d", i, card_player[i].playerScore);
		printf("\n");
	}
}

void displayPlayerHand(int playerNumber) {
	int i, j;

	printf(" --- Current player: %d ---\n\n", playerNumber);
	printf("Idx. | Card Value\n");
	for (i = 0; i < 13; i++) {
			printf("[%-2d] ==> %-4d",i,card_player[playerNumber].playerHand[i]);
			printf("\n");
	}
	printf("\n");
}

int getPlayerCardSelection(int playerNumber) {
	int cardValue, cardChoice;

	displayPlayerHand(playerNumber);

	printf("--> Select a card [Use index value!]\n--> ");
	scanf("%d", &cardChoice);
	printf("\n");

	printf("--> Card choice: %d", card_player[playerNumber].playerHand[cardChoice]);
	printf("\n\n");

	cardValue = card_player[playerNumber].playerHand[cardChoice];

	runningTotalScore += cardValue;

	card_player[playerNumber].playerHand[cardChoice] = 0; //Sets value to 0 --> used instead of removing value from array

	return cardValue;
}

void dispenseCards() {
	int i, j;

	srand(time(NULL));
	for (i = 0; i < 13; i++) {

		for (j = 0; j < 13; j++) {

			//Random cards between 1-13 --> find value of card by using random value with deckOfCards array location
			card_player[i].playerHand[j] = rand() % (14 + 1 - 2) + 2;
		}
	}
}

void displayAllCards() {
	int i, j;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 13; j++) {
			printf("Player: %d\tCard: %d", i, card_player[i].playerHand[j]);
			printf("\n");
		}
		printf("\n");
	}
}

void clearScreen() {
	printf("-------WAR-------\n");
	printf("   -----------\n\n\n\n\n");
}

void runGame(int numberOfUsers) {
	int i, j;
	int highestCard = 0, newHighestCard;
	int playerWithHighestCard;
	int gameRoundOutput;

	if (numberOfUsers >= minPlayers && numberOfUsers <= maxPlayers) {
		/*
		//Input player initials
		for (i = 0; i < numberOfUsers; i++) {
			card_player[i].playerInitials[i] = initialsInput(i,numberOfUsers);
		}
		*/
		//Initial for counter used for n game rounds
		for (i = 0; i < 2; i++) {
			gameRoundOutput = 1;
			printf("**** Current Game Round: %d ****\n", gameRoundOutput++);
			printf("\n");

			//Inner for used for player turns
			for (j = 0; j < numberOfUsers; j++) {

				newHighestCard = getPlayerCardSelection(j);

				//Check who has highest card
				if (newHighestCard > highestCard) {
					highestCard = newHighestCard;
					playerWithHighestCard = j;
					card_player[playerWithHighestCard].playerScore += runningTotalScore;
				}
				clearScreen();
			}

			//Show highest card at end of round
			printf("===============================\n\n");
			printf("** Highest Card: %d\n", highestCard);
			printf("** Player with highest card: %d\n\n", playerWithHighestCard);
			printf("===============================\n\n");
			clearScreen();

			//Reset highest card for end of round
			highestCard = 0;
		}
	}
	else {
		printf("Invalid player count!");
	}
}

char initialsInput(int playerNumber, int numberOfUsers) {
	char initials[2];
	
	printf("Player[%d] ", playerNumber);
	printf("Enter initials\n--> ");
	scanf("%s", initials);
	printf("\n\n");

	return  initials;
}

