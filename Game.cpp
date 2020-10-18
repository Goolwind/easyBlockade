#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <string>
#include "Map.h"
using namespace std;
bool isAlive = true;


void paint(Map *map) {
	string str;
	for (int i = 0; i < Heighth; i++) {
		int m;
		for (int j = 0; j < Width; j++) {
			m = map->map[i][j];
			if (m == AIR)str += ' ';
			else if (m == WALL)str += '*';
			else if (m == HEAD)str += '@';
			else if (m == BODY)str += '#';
			else if (m == FOOD)str += '&';
			else if (m == MINE)str += '%'; 
			else if (m == POISON)str += '$';
			else if (m == POISON_2)str += ' ';
		}
		str += '\n';
	}
	cout << str;
}

int main()
{
	int sx, sy;
	char cmd = UP;
	int DyMsg;
	Level1 map;
	SnakeNode Snake(20, 10);
	Snake.make(3);
	food fd;
	fd.setPosition();
	poison psn;
	psn.setPosition();
	psn.createNext(1);
	mine mn;
	mn.setPosition();
	time_t start = clock();
	while (1) {
		map.setMap(&Snake, &fd, &mn, &psn);
		paint(&map);
		while (clock() - start < 300) {
			if (_kbhit()){
				cmd = _getch();
				if (cmd == -32)
					cmd = _getch();
				if (!(cmd == UP or cmd == DOWN or cmd == LEFT or cmd == RIGHT)) {
					cout << "Enter any direction key to continue..." << endl;
					cout << "If you still enter an un-directing key, the game will over." << endl;
					cmd = _getch();
					if (cmd == -32)cmd = _getch();
				}
			}
		}
		if (!(cmd == UP or cmd == DOWN 
			or cmd == LEFT or cmd == RIGHT)) {
			isAlive = false;
			DyMsg = 0;
		}
		Snake.move(cmd);
		sx = Snake.sx();
		sy = Snake.sy();
		SnakeNode *temp = Snake.showNext();
		while (temp != nullptr) {
			if (sx == temp->sx() and sy == temp->sy()) {
				isAlive = false;
				DyMsg = 0;
				break;
			}
			temp = temp->showNext();
		}
		if (map.map[sy][sx] == WALL) {
			isAlive = false;
			DyMsg = 1;
		}
		else if (map.map[sy][sx] == FOOD) {
			fd.beEatenBy(&Snake);
			fd.setPosition();
			cmd = cmd;
		}
		else if (map.map[sy][sx] == MINE) {
			if (!mn.beEatenBy(&Snake)) {
				isAlive = false;
				DyMsg = 2;
			}
			mn.setPosition();
		}
		else if (map.map[sy][sx] == POISON or 
			map.map[sy][sx] == POISON_2) {
			if (!psn.beEatenBy(&Snake)) {
				isAlive = false;
				DyMsg = 3;
			}
		}
		if (!isAlive)break;
		system("cls");
		start = clock();
	}
	cout << "Game Over." << endl;
	switch (DyMsg) {
	case 0:
		cout << "Self-killed";
		break;
	case 1:
		cout << "Hit Wall";
		break;
	case 2:
		cout << "Be Bombed";
		break;
	case 3:
		cout << "Eat Poinson";
		break;
	}
}