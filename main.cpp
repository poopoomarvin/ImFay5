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
#include "play.h"
#include "ai.h"
using namespace std;

int main()
{
    Play play;
    AI ai;
    srand(time(NULL));
    bool flag = false;
    int mode;
    play.init();

    cout << "Game Start." << endl << endl;
    cout << "|--------------------------------- |" << endl;
    cout << "|   " << endl << "| Select Mode:" << "\n|\n";
    cout << "|\t1) Player\n|\t2) Auto\n|\t3) playerAI\n|\t4) See Priority Advantage\n|" << endl;
    cout << "|--------------------------------- \n";
    cout << "Blokus>>";

    cin >> mode;
    bool pause = false;
    if (mode == 1) {	// player
        play.twoPlayers();
        pause = true;
    }
    else if (mode == 2)
        ai.twoAIs();
    else if (mode == 3)
        play.playerAI();
    else
        play.priorityAdvantage();
    string s = "";

    while (s != "seeResult" && pause) {
        cout << endl;
        cout << "|--------------------------------- |" << endl;
        cout << "|   " << endl << "| Please input string : seeResult" << "\n";
        cout << "|" << endl;
        cout << "|--------------------------------- \nBlokus>>";
        cin >> s;
    }

    play.printBoard();
    cout << "|--------------------------------- |" << endl;
    cout << "|   " << endl << "| Player " << play.winner() << " wins." << "\n";
    cout << "|" << endl;
    cout << "|--------------------------------- \nBlokus>>";
    return 0;
}
