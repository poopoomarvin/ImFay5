#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"
#include "game.h"
#include "ai.h"
using namespace std;

//Some nouns definition :
//  board : The game board. The playground.
//  shape : The stuff looks like LEGO. The thing you place it on the board.
//  piece : Same as shape. Different coder.
//  shp   : Abbr for shape.
//  block : smallest unit on the board. 1x1 square.

class Play
{
	private:
		Game game;

		int instrCounter;
		bool selectShape;
		int shapeID;
		Shape selected;

	public:
		Play();
		//The assigned player plays the game. True when the game is quitted.
		bool playerPlay(const char& player);
		//If autoPlay fails to place THE shape by random, place it by brutal force.
		void autoPlace(const int& id, const char& player);
		//Play a round for Artificial Idiot. Random everything.
		void autoPlay(const char& player);
		//Playing mode of 2 human players.

		void twoPlayers();
		//mode of two Artificial Idiots battle.
		void twoAIs();
		//Playing mode of human v.s. Artificial Idiot
		void playerAI();
		//
		void priorityAdvantage();

		void printBoard();
		string winner();
};


#endif
