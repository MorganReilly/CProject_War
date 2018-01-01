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
}player;

player card_player[10];

void displayPlayerHand(int playerNumber);
int getPlayerCardSelection(int playerNumber);
void dispenseCards();
void displayAllCards();

int runningTotalScore; //While game is underway

void main() {
	//Structs=====================================================================================================
	

	//Variables===================================================================================================
	int numberOfUsers;
	int i, j;
	int roundCounter;
	//int deckOfCards[52] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int highestCard = 0, newHighestCard;
	int playerWithHighestCard;

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
	printf("Please enter number of players [2-10 players]: ");
	scanf("%d", &numberOfUsers);
	printf("\n");

	if (numberOfUsers >= minPlayers && numberOfUsers <= maxPlayers) {

		//Initial for counter used for 13 game rounds
		for (i = 0; i < 2; i++) {
			printf("**** Current Game Round: %d ****\n", i);
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
			}

			//Show highest card at end of round
			printf("===============================\n\n");
			printf("Highest Card: %d\n", highestCard);
			printf("Player with highest card: %d\n\n", playerWithHighestCard);
			printf("===============================\n\n");

			//Reset highest card for end of round
			highestCard = 0;
		}
	}
	else {
		printf("Invalid player count!");
	}

	printf("\n\n===============================\n\n");
	//Print end score for each active player
	for (i = 0; i < numberOfUsers; i++) {
		printf("Player %2d score: %4d", i, card_player[i].playerScore);
		printf("\n");
	}
}

void displayPlayerHand(int playerNumber) {
	int i, j;

	printf(" --- Current player: %d ---\n\n", playerNumber);
	for (i = 0; i < 13; i++) {
			printf("Card: %2d\tIndex: %2d",card_player[playerNumber].playerHand[i],i);
			printf("\n");
	}
	printf("\n");
}

int getPlayerCardSelection(int playerNumber) {
	int cardValue, cardChoice;

	displayPlayerHand(playerNumber);

	printf("--> Select a card [Use index value!]: ");
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
			card_player[i].playerHand[j] = rand() % 13 + 1;
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

