#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <cstring>
#include "shapes.h"
#include "game.h"
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.

Game::Game()
{
	this->biggestRange = 0;
	memset(this->shapes, 0, sizeof(this->shapes));
	memset(this->board, 0, sizeof(this->board));
	this->firstStepFlagA = true;
	this->firstStepFlagB = true;
	this->errorMessage = "";
	memset(this->piecesUseA, 0, sizeof(this->piecesUseA));
	memset(this->piecesUseB, 0, sizeof(this->piecesUseB));
}

//Initial the game.
//Create shapes and initial board and identifiers for placed shapes.
void Game::init()
{
	for (int i=0; i<14; i++)
		for (int j=0; j<14; j++)
			this->board[i][j] = '.';

	this->board[4][4] = 'A';
	this->board[9][9] = 'B';
	for (int i=0; i<21; i++) {
		this->piecesUseA[i] = false;
		this->piecesUseB[i] = false;
	}
	shapes[0] = assignshape_00();	shapes[1] = assignshape_01();	shapes[2] = assignshape_02();	shapes[3] = assignshape_03();	shapes[4] = assignshape_04();
	shapes[5] = assignshape_05();	shapes[6] = assignshape_06();	shapes[7] = assignshape_07();	shapes[8] = assignshape_08();	shapes[9] = assignshape_09();
	shapes[10] = assignshape_10();	shapes[11] = assignshape_11();	shapes[12] = assignshape_12();	shapes[13] = assignshape_13();	shapes[14] = assignshape_14();
	shapes[15] = assignshape_15();	shapes[16] = assignshape_16();	shapes[17] = assignshape_17();	shapes[18] = assignshape_18();	shapes[19] = assignshape_19();
	shapes[20] = assignshape_20();
}

//Set all the pointers to the assigned player's
void Game::setPlayer(const char& player)
{
	this->piecesUsePointer = (player == 'A')? this->piecesUseA: this->piecesUseB;
}

//Get the shape of the assigned ID
Shape Game::getShape(const int& shapeID)
{
	if (shapeID<21 && shapeID>=0)
		return this->shapes[shapeID];

	Shape nullShape;
	cout << "Game::getShape: Can not get the assigned shape in shapes" << endl;
	return nullShape;
}

//Check if the selected piece used(true) or not(false)
bool Game::isPieceUse(const int& k)
{
	if (k>=0 && k<21)
		return this->piecesUsePointer[k];
	cout << "Game::isPieceUse: The argument is not between 0 and 21." << endl;
	return false;
}

//Set the selected piece used
void Game::setPieceUse(const int& k)
{
	if (k>=0 && k<21)
		this->piecesUsePointer[k] = true;
	else
		cout << "Game::setPieceUse: The argument is not between 0 and 21." << endl;
}

//Get biggestRangeA
int Game::getBstRngA()
{
	return this->biggestRangeA;
}

//Get biggestRangeB
int Game::getBstRngB()
{
	return this->biggestRangeB;
}

//Get errorMessage
string Game::getErrMsg()
{
	return this->errorMessage;
}

//List the shapes of the player that have not been placed yet.
void Game::listShapes(const char& player){
	//this->piecesUsePointer = (player == 'A'? this->piecesUseA : this->piecesUseB);
	if (player == 'A') {
		for (int i=0; i<21; i++) {
			if (!this->piecesUseA[i]) {
				cout << i << ":" << endl;
				this->shapes[i].printShape();
			}
		}
	}
	else {
		for (int i=0; i<21; i++) {
			if (!this->piecesUseB[i]) {
				cout << i << ":" << endl;
				this->shapes[i].printShape();
			}
		}
	}
}

//Print out the current board status.
void Game::printBoard()
{
	cout << "|---------------------------------\n| [Map]" << endl;
	cout << "|\t            1111" << endl;
	cout << "|\t  ";
	for (int i=0; i<14; i++) {
		if (i == 4 || i == 9)
			cout << MAGENTA << i%10 << RESET;
		else
			cout << i%10;
	}

	cout << endl;

	for (int i=0; i<14; i++) {
		if (i>=10)
			cout << "|\t" << 1;
		else
			cout << "|\t ";

		if (i == 4 || i == 9)
			cout << MAGENTA << i%10 << RESET;
		else
			cout << i%10;

		for (int j=0; j<14; j++) {
			if (this->board[i][j] == 'A')
				cout << YELLOW << 'A' << RESET;
			else if (this->board[i][j] == 'B')
				cout << RED << 'B' << RESET;
			else
				cout << this->board[i][j];
		}
		printf("\n");
	}
	cout << "|\n|---------------------------------\n" << endl;
}

//Check if the selected shape index is between 0 and 20.
bool Game::checkShapeID(const int& i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

//Check if it's first step and if it's a legal first step.
bool Game::isLegalFirst(Shape& shp, const int& x, const int& y, const char& player)
{
	if (player == 'A') {
		if (this->firstStepFlagA) {	// is first
			for (int i=0; i<shp.getSize(); i++) {
				if (x + shp.getPosX(i) == 4 && y + shp.getPosY(i) == 4)
					return true;
			}
		}
	}
	else {
		if (this->firstStepFlagB) {	// is first
			for (int i=0;i<shp.getSize();i++) {
				if (x + shp.getPosX(i) == 9 && y + shp.getPosY(i) == 9)
					return true;
			}
		}
	}
	this->errorMessage = "The first shape doesn't cover the initial position!";
	return false;
}

//connected to a shoulder
//To check if the block is connected so it's LEGAL.
bool Game::isConnectedToShoulder(Shape& shp, const int& x, const int& y, const char& player)
{
	for (int i=0; i<shp.getCornerSize(); i++) {
		int xtmp = shp.getCornerX(i)+x, ytmp = shp.getCornerY(i)+y;
		if (xtmp>=0 && xtmp<14 && ytmp>=0 && ytmp<14 && this->board[xtmp][ytmp] == player)
			return true;
	}
	this->errorMessage = "The shape is not connected to any shoulder!";
	return false;
}

//touched by itself
//To check if the block is touched so it's ILLEGAL.
bool Game::isTouchedBySelf(Shape& shp, const int& x, const int& y, const char& player)
{
	for (int i=0; i<shp.getEdgeSize(); i++) {
		int xtmp = shp.getEdgeX(i)+x, ytmp = shp.getEdgeY(i)+y;
		if (xtmp>=0 && xtmp<14 && ytmp>=0 && ytmp<14 && this->board[xtmp][ytmp] == player)
			return true;
	}
	this->errorMessage = "The shape is touched by some sides!";
	return false;
}

//To check if the board is spare to place the block so it's LEGAL.
bool Game::isSpare(Shape& shp, const int& x, const int& y)
{
	for (int i=0; i<5; i++) {
		// The block is in board range and unoccupied.
		int xtmp = shp.getPosX(i)+x, ytmp = shp.getPosY(i)+y;
		if ( !(xtmp<14 && xtmp>=0 && ytmp<14 && ytmp>=0 && this->board[xtmp][ytmp] == '.') ) {
			this->errorMessage = "The position is illegal or used!";
			return false;
		}
	}
	return true;
}

//To check the move is legal or not, that is, Connected, not Touched and Spare to place.
bool Game::isLegalMove(Shape& shp, const int& x, const int& y, const char& player)
{
	bool firstStep = (player == 'A') ? this->firstStepFlagA : this->firstStepFlagB;
	if (firstStep) {	//is first step
		if (isLegalFirst(shp, x, y, player))	// is first step
			return true;
		else
			return false;
	}

	if(!isConnectedToShoulder(shp, x, y, player) || isTouchedBySelf(shp, x, y, player) || !isSpare(shp, x, y))
		return false;
	else
		return true;
}

//Make a single move. Return true if the move is success.
bool Game::playerMove(Shape& shp, const int& shapeID, const char& player, const int& x, const int& y)
{
	char junk, cX, cY;
	//this->piecesUsePointer = (player == 'A')? this->piecesUseA : this->piecesUseB;

	// shapeID is not between 0 and 21.
	if (shapeID>=21 || shapeID<0) {
		this->errorMessage = "Game::playerMove: The argument is not between 0 and 21.";
		return false;
	}

	// check if piece alredy been used.
	if (this->piecesUsePointer[shapeID])
		return false;

	// check if legal.
	if(isLegalMove(shp, x, y, player)) {
		// The uniX and uniY of "shp" is always (0,0)
		for (int i=0; i<5; i++)
			this->board[shp.getPosX(i)+x][shp.getPosY(i)+y] = player;

		if (player == 'A')
			this->firstStepFlagA = false;
		else
			this->firstStepFlagB = false;

		printBoard();
		return true;
	}
	else
		return false;
}

//To check if the shape can be place anywhere or not.
bool Game::hasPlaceToPut(const int& id, const char& player)
{
	// loop though all board.
	Shape selected;
	int counter  = 0;
	if (id>=21 || id<0) {
		cout << "Game::hasPlaceToPut: The argument is not between 0 and 21." << endl;
		return false;
	}
	selected = this->shapes[id];

	for (int i=0; i<14; i++) {
		for (int j=0; j<14; j++) {
			// two flip.
			for (int f=0; f<2; f++) {
				if (f > 0) selected.flip();

				// and four direction.
				for (int clockwise = 0; clockwise < 4; clockwise++) {
					if (clockwise > 0) selected.turnClockwise();

					// if this piece can put => return true.
					if(isLegalMove(selected, i, j, player)){
						// cout << "selected id:" << id << ", and x,y" << i << ", " << j << endl;
						//this->shapes[id].printShape();
						return true;
					}
				}
			}
		}
	}
	return false; // if this piece can't   => return false.
}

//To check if the player have no shape to put and his turn is ended.
bool Game::isGameAlive(const char& player)
{
	cout << "\n\nstart check...\n" << endl;
	int counter = 0;
	bool cannotPutPieces = true;
	this->piecesUsePointer = (player == 'A') ? this->piecesUseA : this->piecesUseB;
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i])
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i]) {
			if (hasPlaceToPut(i, player)) {	// can place
				cannotPutPieces = false;
				break;
			}
		}
	}
	if (cannotPutPieces) { // can't place, end.
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": You have no more pieces or you can't place any more.\n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left." << endl;
		return false;	//end
	}
	else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;	//still
	}
}

//Same as isGameAlive, but without print anything. ( for AI )
bool Game::isGameAliveAI(const char& player)
{
	int counter = 0;
	bool cannotPutPieces = true;
	this->piecesUsePointer = (player == 'A') ? this->piecesUseA : this->piecesUseB;
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i])
			counter++;
	}
	for (int i=0; i<21; i++) {
		if (!this->piecesUsePointer[i]) {
			if (hasPlaceToPut(i, player) == true) {
				cannotPutPieces = false;
				break;
			}
		}
	}

	if (cannotPutPieces){
		cout << "press!!!" << player << endl;
		return false;
	}
	else{
		cout << "dont press!!!" << player << endl;
		return true;
	}
}

//To return the winner of the game.
string Game::winner()
{
	int ALeft = 0, BLeft = 0;
	for (int i=0; i<21; i++) {
		if (!this->piecesUseA[i])
			ALeft += this->shapes[i].getSize();
		if (!this->piecesUseB[i])
			BLeft += this->shapes[i].getSize();
	}

	cout << ALeft << " : " << BLeft << endl;
	if (ALeft < BLeft) return "Player A wins.";
	else if (ALeft > BLeft) return "Player B wins.";
	else return "The game ends in a tie.";
}

//To return the winner of the game and calculate the biggest range.
char Game::priorityWinner()
{
	int ALeft = 0, BLeft = 0;
	for (int i=0; i<21; i++) {
		if (!this->piecesUseA[i])
			ALeft += this->shapes[i].getSize();
		if (!this->piecesUseB[i])
			BLeft += this->shapes[i].getSize();
	}

	//Update the information of the biggest difference between A and B
	if (ALeft - BLeft > this->biggestRange || BLeft - ALeft > this->biggestRange) {
		this->biggestRange = ALeft - BLeft;
		this->biggestRangeA = ALeft;
		this->biggestRangeB = BLeft;
	}

	cout << ALeft << " : " << BLeft << endl;
	return (ALeft < BLeft) ? 'A' : 'B';
}
