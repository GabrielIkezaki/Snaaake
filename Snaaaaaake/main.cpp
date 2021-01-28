#include <iostream>
#include <conio.h>

using namespace std; 

bool print = false;
bool gameOver;

const int mapWidth = 20;
const int mapHeight = 20;

int headPosX, headPosy, fruitPosX, fruitPosY, score;

//This will be the x and y position of each individual tail unit
int tailX[400], tailY[400];
int tailLength;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void SetFruitPosition() {
	//rand() will generate a random number from 0 to the mapWidth - 1
	fruitPosX = rand() % mapWidth;

	//Same for the y position of the fruit, but now from 0 to the height - 1
	fruitPosY = rand() % mapHeight;
}

void Setup() {
	gameOver = false;
	dir = STOP; 
	headPosX = mapWidth / 2; 
	headPosy = mapHeight / 2;

	SetFruitPosition();

	score = 0;
}

void Draw() {
	//this will clear the screen
	system("cls");

	//This will drawn the first row, drawn only by #
	for (int i = 0; i < mapWidth + 2; i++) {
		cout << "#";	
	}
	cout << endl;

	//Once the upper wall is drawn, the application will draw the rest of the rows (which will be equivalent to the number of heigh units)
	for (int i = 0; i < mapHeight; i++) {
		
		//Every first unit of every row will be a wall, thus the first thing that will be drawn (when j = 0) is a wall
		for (int j = 0; j < mapWidth; j++) {
			if (j == 0) {
				cout << "#";
			}
			
			//The application will check if the unit being drawn has the same coordinates as the snake head. If so, the head will be drawn
			if (i == headPosy && j == headPosX) {
				cout << "O";
			}
			else if (i == fruitPosY && j == fruitPosX) {
				//If a fruit is locafted at the same unit being drawn, the fruit will be drawn instead
				cout << "+";
			}		
			else {

				//The application will check the position of each tail unit. If there's a tail unit where the current unit is being drawn, a "o" will be printed
				for (int k = 0; k < tailLength; k++) {

					//the print variable will signalize wether a tail unit has been drawn in the current map coordinate or not
					print = false;

					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}

					
				}
				
				//if no tail units were drawn, an empty map coordinate will be drawn instead
				if (!print) {
					cout << " ";
				}
				//cout << " ";
			
			}

			if (j == mapWidth - 1) {
				//Uppon reaching the right wall, a # will be drawn, marking the dead end of the map
				cout << "#";
			}
		}

		cout << endl;
	}

	//Finally, the last row wil be the bottom wall, and much like the upper wall, will be drawn only by #
	for (int i = 0; i < mapWidth + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << endl; 

	//The Score will always be displayed at the bottom of the screen;
	cout << "Score: " << score;
	
}

void Input() {
	
	//Will return "true" if any key is being pressed
	if (_kbhit()) {
		
		//getch is a conio function which returns the character that is being pressed. We will switch this variable to change directions accordingly
		switch (_getch()) {
		case 'a':
			if(dir != RIGHT)
				dir = LEFT;
			break;
		case 's':
			if(dir != UP)
				dir = DOWN;
			break;
		case 'd':
			if(dir != LEFT)
				dir = RIGHT;
			break; 
		case 'w':

			if(dir != DOWN)
				dir = UP; 
			break;
		case 'p':
			gameOver = true;
			break;
		}
	}
}

void ManageTailUnits() {

	//Every time the map is drawn, the "prev" variables will take the value of the last tail unit before the head
	int prevTailXPos = tailX[0];
	int prevTailYPos = tailY[0];

	int prev2X, prev2Y;

	//The first tail unit will be the head
	tailX[0] = headPosX;
	tailY[0] = headPosy;


	//For every unit after the head, prev2 variables will temporarily register current position of the tail unit
	for (int i = 1; i < tailLength; i++) {

		
		prev2X = tailX[i];
		prev2Y = tailY[i];

		//Then, the tail unit will move to where the head or the neighbour unit closest to the head was
		tailX[i] = prevTailXPos;
		tailY[i] = prevTailYPos;

		//The prev variables will finally take the values of what the current unit's position was, so that the neighbour unit may take its place
		prevTailXPos = prev2X;
		prevTailYPos = prev2Y;
	}
}

void Logic() {

	ManageTailUnits();



	//The dir variable will determine wether the x and y pos of the head will decrease or not
	switch (dir) {
	case LEFT:
		headPosX--;
		break;

	case RIGHT:
		headPosX++;
		break;

	case UP:
		headPosy--;
		break;

	case DOWN:
		headPosy++;
		break;
	}

	//If the head collides with any wall, the game will end
	if (headPosX > mapWidth || headPosX < 0 || headPosy > mapHeight || headPosy < 0) {
		gameOver = true;
	}

	for (int i = 0; i < tailLength; i++) {
		if (tailX[i] == headPosX && tailY[i] == headPosy) {
			gameOver = true;
		}
	}

	//Everytime the head is drawn at the same position as the fruit, the score will increase and the fruit will be drawn elsewhere
	if (headPosX == fruitPosX && headPosy == fruitPosY) {
		score++;
		SetFruitPosition();
		tailLength++;
	}
}

int main() {

	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();

		//Sleep(10) - This will slow down the game when applied
	}

	return 0;
}