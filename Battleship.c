/*==============================================================================
| Programmers: Marios Bikos, Panagiotis Chronopoulos, Nikolas Zaglis
| Class: Introductions to Computers II, Spring 2010 ; Battle Ship Competition
| Final Programming Assignment: Basic Game of Battleship
| Date: May 2010
+------------------------------------------------------------------------------
| Description: This programme is a BattleShip game for 2 players. Each player
|              tries to hit enemy ships until victory!
==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_ROWS 10
#define MAX_COLS 10

//Functions
void printMap(char map[][MAX_COLS]);
int executeShot(int g,int A[][10]);
int incomingShot(char map[][MAX_COLS]);
void welcomeScreen (void);

int main()
{
	welcomeScreen();
	system("chcp 1253 >nul ");	//Enable Greek Characters Command
	FILE *fileptr=NULL;

	char myColchar,apantisi,map[MAX_ROWS][MAX_COLS];

	int winCounter=0,loseCounter=0,shotResult=0,myColnum=1,myrow=1,formation,row, col,A[10][10],i,j;
	int g=0;
	char fileRow[MAX_COLS + 2];	// Consider newline and NULL

	printf("Choose the initial formation of your ships from .txt files(1/2/3/4/5/6): \n");
	scanf("%d",&formation);
	while (formation!=1 && formation!=2 && formation!=3 && formation!=4 && formation!=5 && formation!=6)
	{
		printf("Wrong formation number. Please choose the initial formation of your ships again(1/2/3/4/5/6): \n");
		scanf("%d",&formation);
	}
	if (formation==1){
		fileptr = fopen("1.txt", "r");
	}
	else if (formation==2){
		fileptr=fopen("2.txt","r");
	}
	else if (formation==3){
		fileptr=fopen("3.txt","r");
	}
	else if (formation==4){
		fileptr=fopen("4.txt","r");
	}
	else if (formation==5){
		fileptr=fopen("5.txt","r");
	}
	else if (formation==6){
		fileptr=fopen("6.txt","r");
	}

	if (fileptr == NULL)
	{
		perror("File Open Error");
		system("pause");
		return -1;
	}
	else if (fileptr!=NULL)
	{
		//Print Grid Map with ship formation
		printf(" A B Γ Δ Ε Ζ Η Θ Ι Κ\n");
		printf("--------------------- \n");
		for (row = 0; row < MAX_ROWS; row++)
		{
			//fgets reads characters from input and stores them into a string.
			//A newline character stops input reading, but it is considered as a valid character
			// Therefore, It is included in the string and copied in str.
			fgets(fileRow, sizeof(fileRow), fileptr);
			printf("|");
			for (col = 0; col < MAX_COLS; col++)
			{
				//Put each ship symbol from txt file into the 2D Grid Map
				map[row][col] = fileRow[col];
				if (map[row][col]=='.')
				{
					map[row][col]=' ';
				}
				printf("%c",map[row][col]);
				printf("|");
			}
			printf("%d",row+1);

			printf("\n");
			printf("--------------------- \n");
		}
	}
	//Initialize 2D Grid A[10][10] which shows us if a ship has been hit or not using 0 for missed shot and 1 for a successful shot
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
		{
			A[i][j]=0;
		}
	}
	//Ask user who plays first: Him or the opponent
	printf("\nEnter <<N>> in case it is your turn to shoot or <<O>> if it is your opponent's turn: \n");
	printf("Is it your turn? (N/O): \n");
	getchar();
	scanf("%c", &apantisi);
	while (apantisi!='N' && apantisi!='Ν' && apantisi!='O' && apantisi!='ν' && apantisi!='o' && apantisi!='n' && apantisi!='Ο' && apantisi!='ο')
	{
		printf("\nIncorrect Order!Enter <<N>> in case it is your turn to shoot or <<O>> if it is your opponent's turn: \n");
		printf("Is it your turn? (N/O): \n");
		getchar();
		scanf("%c", &apantisi);
	}

	//In case it is user's turn
	if (apantisi=='Ν' || apantisi=='n' || apantisi=='N' || apantisi=='ν')
	{
		shotResult=executeShot(g,A);
		if (shotResult==1)
		{
			winCounter++;			//Increase winning counter if fired shot was successful
		}
		printMap(map);
		g++;

		while (1)
		{
			loseCounter=incomingShot(map);
			printMap(map);
			//When losecounter reaches 17 user loses
			if (loseCounter==17)
			{
				printf("You Lose\n");
				break;
			}
			shotResult=executeShot(g,A);
			if (shotResult==1)
			{
				winCounter++;
			}
			printMap(map);
			g++;

			if (winCounter==17)
			{
				printf("VICTORY IS OURS\n");
				break;
			}
		}

	}
	//In case user is taking fire
	else if (apantisi=='O' || apantisi=='o' || apantisi=='ο' || apantisi=='Ο' )
	{
		loseCounter=incomingShot(map);
		printMap(map);
		while (1)
		{
			shotResult=executeShot(g,A);
			if (shotResult==1)
			{
				winCounter++;
			}
			printMap(map);
			g++;
			if (winCounter==17)
			{
				printf("VICTORY IS OURS\n");
				break;
			}
			loseCounter=incomingShot(map);
			printMap(map);
			if (loseCounter==17)
			{
				printf("You Lose\n");
				break;
			}
		}
	}
	fclose(fileptr);

	system("pause");

	return 0;
}

//****************************************************************************************************************************************************************************************
/*
* Summary:      Prints a Welcome Message
*               when the game starts
* Parameters:   void
* Return:       void
*/
void welcomeScreen (void) {
	printf ("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
	printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
	printf ("\n\n");
	printf ("RULES OF THE GAME:\n");
	printf ("1. This is a two player game.However each players uses his own computer and his own instance of this programme\n");
	printf ("2. Player will be prompted to select the initial formation of his ships\n");
	printf ("    for the game board \n");
	printf ("3. There are 6 types of formations to be placed \n");
	printf ("4. The ship grid is printed and user should select which goes first: himself or the opponent \n");
	printf ("5. The computer randomly selects where the next player's shot will hit(coordinates in GREEK)\n");
	printf ("6. When the enemy hits the player, user has to enter incoming shot coordinates(using GREEK letters)\n");
	printf ("7. The game begins as each player tries to guess the location of the ships\n");
	printf ("   of the opposing player's game board; [*] hit and [X] miss\n");
	printf ("8. First player to guess the location of all ships wins\n\n");
}
//****************************************************************************************************************************************************************************************

/*
* Summary:      Prints the grid(map) with the ships
*               refreshed after every shot
* Parameters:   map[][MAX_COLS]
* Return:       void
*/
void printMap(char map[][MAX_COLS])
{
	int row,col;
	printf(" A B Γ Δ Ε Ζ Η Θ Ι Κ\n");
	printf("--------------------- \n");
	for (row = 0; row < MAX_ROWS; row++)
	{
		printf("|");
		for (col = 0; col < MAX_COLS; col++){
			printf("%c",map[row][col]);
			printf("|");}
		printf("%d",row+1);
		printf("\n");
		printf("--------------------- \n");
	}
}

// ***************************************************************************************************************************************************************************************
/*
* Summary:      Calculates where your next shot will be.
*               Can be improved for better results.
* Parameters:   map[][] 2D array containing a ships' grid for memorizing where shot were hit
* Return:       Integer indicating if shot was successful(1) or unsuccessful(2)
*/
int executeShot(int g,int A[][10])
{
	static int shotResult=0,i,pin[100],pin2[100];
	int l,c;
	static char apotelesma='Α';

	srand ( time(NULL) );
	l = rand() % 10;
	c = rand() % 10;
	// Loop so that it we don't have firing at the same spot
	while (1)
	{
		if (A[l][c]==1)
		{
			//If a spot in Array A has already been hit,then a new coordinate position is calculated
			l = rand() % 10;
			c = rand() % 10;

		}
		if ( A[l][c]==0)
		{					//If this position hasn't been hit, show that pair
			A[l][c]=1;
			break ;
		}
	}

	c=c-63;					//Subtract 63 from the number in order to correspond to the greek alphabet letter
	l=l+1;					//Increase by 1(offset) to get from 0-9 to 1-10
	pin[g]=c;                     //Place in the grid
	pin2[g]=l;

	if (apotelesma=='ε' || apotelesma=='Ε' || apotelesma=='e' || apotelesma=='E')
	{
		//If shot fired is successful, then our program chooses to shot next fire right
		if (  pin[g-1]+1!=-53)
		{
			pin[g]=pin[g-1]+1;		//increase column number(go right)
			pin2[g]=pin2[g-1];
		}
	}

	printf("State: Shot fire\n");
	printf("Coordinates to shoot: %c%d\n",pin[g],pin2[g]);
	printf("Result of the shot you fired:(Enter <<E>> for success or <<A>> for missed shot)\n");
	printf("Shot %c %d: \n",pin[g],pin2[g]);

	//User enters result of whether shot was successful or not
	scanf("%s",&apotelesma);

	while (apotelesma!='A' && apotelesma!='E' && apotelesma!='ε' && apotelesma!='α' && apotelesma!='Ε' && apotelesma!='Α' && apotelesma!='e' && apotelesma!='a' )
	{
		printf("Wrong Input!\nResult of the shot you fired:(Enter <<E>> for success or <<A>> for missed shot)\n");
		printf("Shot %c %d: \n",c,l);
		scanf("%s",&apotelesma);

	}
	if (apotelesma=='E' || apotelesma=='e' || apotelesma=='ε' || apotelesma=='Ε' )
	{
		//If shot was successful, function returns 1 and counter is increased
		return 1;
	}
	else
	{
		//If shot was unsuccessful, function returns 2 and counter in NOT increased
		return 2;
	}
}

//********************************************************************************************************************************************************************************************

//sinartisi gia tin katastasi lipsis volis pou kanei tis katalliles voles sta ploia sou
/*
* Summary:      Prints the grid(map) with the ships
*               refreshed after every shot
* Parameters:   map[][MAX_COLS]
* Return:       Integer
*/
int incomingShot(char map[][MAX_COLS])
{
	char myColchar,myColchar2;
	int myColnum,myrow,myrow2,col,row;
	static int loseCounter=1;
	printf("State: Taking fire from opponent\n");
	printf("Coordinates of incoming fire: \n");

	fflush(stdin);
	scanf("%c",&myColchar);
	getchar();
	scanf("%d",&myrow);

	printf("Confirm incoming shot: \n");
	fflush(stdin);
	scanf("%c",&myColchar2);//exoume edo diaforetikes metavlites mycolchar2,myrow2
	getchar();
	scanf("%d",&myrow2);

	while (myrow!=myrow2 || myColchar!=myColchar2)
	{   //If coordinates given are wrong, user has to reenter coordinates
		printf("Wrong confirmation of coordinates, please enter incoming shot coordinates again: \n");
		fflush(stdin);
		scanf("%c",&myColchar);
		getchar();
		scanf("%d",&myrow);

		printf("Confirm Incoming shot: \n");
		fflush(stdin);
		scanf("%c",&myColchar2);
		getchar();
		scanf("%d",&myrow2);
	}
	myColnum = (int)myColchar;

	while ( (myColnum<-63) || (myColnum >-54 && myColnum <-31) || (myColnum>-22) || (myrow>MAX_ROWS || myrow<1) )
	{
		printf("You entered wrong coordinates(out of bounds)\n");
		printf("State: Taking fire from opponent\n");
		printf("Coordinates of incoming fire: \n");
		fflush(stdin);
		scanf("%c",&myColchar);
		getchar();
		scanf("%d",&myrow);
		printf("Confirm Incoming shot: \n");
		fflush(stdin);
		scanf("%c",&myColchar2);
		getchar();
		scanf("%d",&myrow2);
		while (myrow!=myrow2 || myColchar!=myColchar2)
		{
			printf("Wrong confirmation of coordinates, please enter incoming shot coordinates again: \n");
			fflush(stdin);
			scanf("%c",&myColchar);
			getchar();
			scanf("%d",&myrow);

			printf("Confirm incoming Shot: \n");
			fflush(stdin);
			scanf("%c",&myColchar2);
			getchar();
			scanf("%d",&myrow2);
		}
		myColnum = (int)myColchar;
	}
	//Transform incoming coordinates to specific array cells of map array
	if(myColnum >= -63 && myColnum <=-54)
	{
		myColnum = myColnum + 63;
	}
	else if((myColnum >=-31) && (myColnum <=-22))
	{
		myColnum = myColnum + 31;
	}
	col = myColnum;
	row = myrow - 1;

	//If there isn't any ship to hit then replace the cell with an 'X'
	if (map[row][col]==' ')
	{
		map[row][col]='X';
		printf("Result of incoming shot: Missed!\n");
	}
	//If ship has been hit replace ship symbol with a '*' in array
	else if (map[row][col]=='Π' || map[row][col]=='Ν' || map[row][col]=='Κ' || map[row][col]=='Φ' || map[row][col]=='Υ'){
		map[row][col]='*';
	}

	if (map[row][col]!='X')
	{
		printf("Result of incoming shot: Success!!!\n");
		return loseCounter++;
	}

}
