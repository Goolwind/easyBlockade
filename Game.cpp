#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include "Map.h"
using namespace std;

int score = 0;
int scores[10] = { 0,0,0,0,0,0,0,0,0,0 };
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
			else if (m == PORTAL)str += '=';
		}
		if (i == 0) {
			stringstream scoress;
			scoress << score;
			string scorestr = scoress.str();
			str = str + "      Score:" + scorestr;
		}
		for (int k = 1; k <= 10; k++) {
			int s;
			stringstream scoress;
			s = scores[10 - k];
			scoress << s;
			string scorestr = scoress.str();
			if (i == k)str = str + "      No." + scorestr;
		}
		str += '\n';
	}
	cout << str;
}

int main()
{
	char ctl = ' ';
	while (ctl != 'e') {
		cout << "\n\n            Enter 's' to start game...\n            Enter 'e' to end game.";
		ctl = _getch();
		sort(scores, scores + 10);
		system("cls");
		if (ctl == 's') {
			bool isAlive = true;
			int sx, sy;
			int len = 5;
			char cmd = UP;
			int DyMsg;
			Map *map = new Map;
			food *fd;
			mine *mn;
			poison *psn;
			fd = new food;
			mn = new mine;
			psn = new poison;
			fd->setPosition();
			mn->setPosition();
			psn->setPosition();
			psn->createNext(1);
			SnakeNode Snake(20, 10);
			time_t start = clock();
			while (1) {
				map->setMap(&Snake, fd, mn, psn);
				paint(map);
				while (clock() - start < 300 - Snake.slen() * 10) {
					if (_kbhit()) {
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
				if (map->map[sy][sx] == WALL) {
					isAlive = false;
					DyMsg = 1;
				}
				else if (map->map[sy][sx] == FOOD) {
					fd->beEatenBy(&Snake);
					fd->setPosition();
					score++;
				}
				else if (map->map[sy][sx] == MINE) {
					if (!mn->beEatenBy(&Snake)) {
						isAlive = false;
						DyMsg = 2;
					}
					mn->setPosition();
					score = score - 2;
				}
				else if (map->map[sy][sx] == POISON or
					map->map[sy][sx] == POISON_2) {
					if (!psn->beEatenBy(&Snake)) {
						isAlive = false;
						DyMsg = 3;
					}
					score = score - 1;
				}
				else if (map->map[sy][sx] == PORTAL) {
					map->level = 2;
					fd->setPosition();
					mn->setPosition();
					psn->setPosition();
					psn->createNext(1);
					map->map[Heighth / 2][Width / 2] = AIR;
				}
				if (Snake.slen() < len)Snake.Longer();
				if (Snake.slen() == len)len = 0;
				if (score % 20 == 0 and score / 20 == map->level) {
					map->map[Heighth / 2][Width / 2] = PORTAL;
				}
				system("cls");
				start = clock();
				if (!isAlive)break;
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

			while (clock() - start < 2000);
			system("cls");
			scores[0] = score;
			score = 0;
		}
	}
}