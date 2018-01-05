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

int currentRoundScore; //used for score at n round
int roundScore;

void main() {
	//Variables
	

	int numberOfUsers;
	int i, j;
	int gameChoice;
	//int roundCounter = 0;;
	//int deckOfCards[52] = { 2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	
	//Setting up the game

	//Header output
	printf("-------WAR-------\n");
	printf("   -----------\n\n\n");

	//Populate player decks --> Generate random numbers 1-13 --> Use as card score
	dispenseCards();

	//Display all player hands --> Made to check if working
	//displayAllCards();

	//Main game options here
	printf("--- New game [0] || Load game [1] ---\n--> ");
	scanf("%d", &gameChoice);
	printf("\n");

	//New Game
	if (gameChoice == 0) {
		FILE* filep;
		//Create new file when new game runs
		filep = fopen("warFile.txt", "w");

		//Playing the game
		printf("[2-10 players]\n--> ");
		scanf("%d", &numberOfUsers);

		fprintf(filep, "Number of players --> %d", numberOfUsers);
		fprintf(filep, "\n\n");

		clearScreen();

		//Run game
		int i, j;
		int highestCard = 0, newHighestCard;
		int playerWithHighestCard;
		int gameRoundOutput;		

		//Number of players validation
		if (numberOfUsers >= minPlayers && numberOfUsers <= maxPlayers) {

			/*
			//Input player initials --> May not get around to doing
			for (i = 0; i < numberOfUsers; i++) {
			card_player[i].playerInitials[i] = initialsInput(i,numberOfUsers);
			}
			*/

			//Initial for counter used for n game rounds
			for (i = 0; i < 2; i++) {
				gameRoundOutput = 1;
				printf("**** Current Game Round: %d ****\n", gameRoundOutput++);
				printf("\n");

				fprintf(filep, "**** Current Game Round: %d ****\n", gameRoundOutput);
				fprintf(filep,"\n");

				//Inner for used for player turns
				for (j = 0; j < numberOfUsers; j++) {

					newHighestCard = getPlayerCardSelection(j);

					//Check who has highest card
					if (newHighestCard > highestCard) {
						highestCard = newHighestCard;
						playerWithHighestCard = j;
					}
					clearScreen();
				}

				card_player[playerWithHighestCard].playerScore += currentRoundScore;

				//End of round code below
				//Show highest card at end of round
				printf("===============================\n\n");
				printf("** Highest Card: %d\n", highestCard);
				printf("** Player with highest card: %d\n\n", playerWithHighestCard);

				fprintf(filep,"===============================\n\n");
				fprintf(filep,"** Highest Card: %d\n", highestCard);
				fprintf(filep,"** Player with highest card: %d\n\n", playerWithHighestCard);

				for (j = 0; j < numberOfUsers; j++) {
					printf("--> Player%d score: %-2d\n", j, card_player[j].playerScore);
					printf("\n");

					fprintf(filep,"--> Player%d score: %-2d\n", j, card_player[j].playerScore);
					fprintf(filep,"\n");
				}
				printf("===============================\n\n");

				fprintf(filep, "===============================\n\n");

				clearScreen();

				//Reset highest card for end of round
				highestCard = 0;

				//Reset round score for end of round
				currentRoundScore = 0;
			}
		}
		else {
			printf("Invalid player count!");
			fprintf(filep, "Invalid player count!");
		}
			

		//Print end score for each active player
		printf("\n\n===============================\n\n");
		fprintf(filep, "\n\n===============================\n\n");
		for (i = 0; i < numberOfUsers; i++) {
			printf("*** Player %-2d ***\n--> Score: %-3d\n", i, card_player[i].playerScore);
			printf("\n");

			fprintf(filep,"*** Player %-2d ***\n--> Score: %-3d\n", i, card_player[i].playerScore);
			fprintf(filep,"\n");
		}

		//Close file
		fclose(filep);
	}

	//Load game
	else if (gameChoice == 1) {
		FILE* filep;
		//Append file
		if (filep == NULL) {
			printf("File not found!");
		}
		else {
			filep = fopen("warFile.txt", "a");

			//Retrieve number of players
			fscanf(filep, "%d", &numberOfUsers);

			printf("Number of users --> %d", numberOfUsers);
			printf("\n");

			//Retrieve round number
			//Retrieve players scores
			//Run game

			//Close file
			fclose(filep);
		}		
	}	
}

void runGame(int numberOfUsers) {
	//Modify this and make more efficient
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

	cardValue = card_player[playerNumber].playerHand[cardChoice]; //Assigning card value to return
	card_player[playerNumber].currentChoice  = cardValue; //Setting the value to compare for all tie rule
	
	currentRoundScore += cardValue;

	card_player[playerNumber].playerHand[cardChoice] = 0; //Sets value to 0 --> used instead of removing value from array

	return cardValue;
}

void dispenseCards() {
	int i, j;

	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 13; j++) {
			
			//Random cards between 2-14 --> Used for point value
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
	system("@cls||clear");
	printf("-------WAR-------\n");
	printf("   -----------\n\n\n");
}

char initialsInput(int playerNumber, int numberOfUsers) {
	char initials[2];
	
	printf("Player[%d] ", playerNumber); 
	printf("Enter initials\n--> ");
	scanf("%s", initials);
	printf("\n\n");

	return  initials;
}

