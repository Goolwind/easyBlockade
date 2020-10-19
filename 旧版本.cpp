#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <conio.h>
#define AIR 0
#define WALL 1
#define HEAD 2
#define BODY 3
#define FOOD 4
#define MINE 5
#define POISON 6
#define Width  40
#define Heighth  20
using namespace std;
bool isAlive = true;
class SnakeNode
{
private:
	int x, nextX;
	int y, nextY;
	int No;
	int Length = 1;
	SnakeNode *nextNode = nullptr;
public:
	SnakeNode(int x, int y, int No);
	bool make(int len) {
		if (Length != 1)return false;
		int fy;
		fy = y;
		Length++;
		SnakeNode *temp = new SnakeNode(x, fy++ + 1, Length);
		this->nextNode = temp;
		for (; Length < len; Length++) {
			SnakeNode *temp2 = new SnakeNode(x, fy++ + 1, Length + 1);
			temp->nextNode = temp2;
			temp = temp2;
		}
		return true;
	}
	void move(char cmd) {
		if (nextNode != nullptr) {
			if (No == 1) {
				nextX = x;
				nextY = y;
				switch (cmd) {
				case 'w':
					x--;
					break;
				case 'a':
					y--;
					break;
				case 's':
					x++;
					break;
				case 'd':
					y++;
					break;
				}
			}
			nextNode->nextX = nextNode->x;
			nextNode->nextY = nextNode->y;
			nextNode->x = nextX;
			nextNode->y = nextY;
			nextNode->move(cmd);
		}
	};
	void Longer() {

		SnakeNode *node, *temp;
		node = new SnakeNode(0, 0, 0);
		temp = this;
		while (temp->nextNode != nullptr)temp = temp->nextNode;
		temp->nextNode = node;
		node->No = temp->No + 1;
		Length++;
	};
	bool beenBombed() {
		if (Length == 1)return false;
		int len = Length;
		SnakeNode *temp = this;
		SnakeNode *temp2, *temp3;
		while (temp->No < len / 2)temp = temp->nextNode;
		temp2 = temp->nextNode;
		while (temp2->nextNode != nullptr) {
			temp3 = temp2;
			temp2 = temp2->nextNode;
			delete temp3;
		}
		delete temp2;
		temp->nextNode = nullptr;
		Length = Length / 2;
		return true;
	};
	bool eatPoison() {
		if (Length == 1)return false;
		SnakeNode *temp = this;
		while (temp->nextNode != nullptr)temp = temp->nextNode;
		delete temp;
		Length--;
		return true;
	}
	SnakeNode *showNext() {
		return nextNode;
	}
	bool isHead() {
		if (No == 1)return true;
		else return false;
	}
	int sx() {
		return x;
	}
	int sy() {
		return y;
	}
	int slen() {
		return Length;
	}
	int sNo() {
		return No;
	}
};
SnakeNode::SnakeNode(int x, int y, int No) {
	this->x = x;
	this->y = y;
	this->No = No;
}
class item {
public:
	int x;
	int y;
	virtual bool beEatenBy(SnakeNode *Snake) {
		return true;
	}
	void setPosition() {
		x = rand() % (Heighth - 2) + 1;
		y = rand() % (Width - 2) + 1;
	}
	int sx() {
		return x;
	}
	int sy() {
		return y;
	}
};
class food :public item {
public:
	bool beEatenBy(SnakeNode *Snake) {
		Snake->Longer();
		return true;
	}
};
class poison :public item {
public:
	bool beEatenBy(SnakeNode *Snake) {
		return Snake->eatPoison();
	}
};
class mine :public item {
public:
	bool beEatenBy(SnakeNode *Snake) {
		return Snake->beenBombed();
	}
};
class Map {
public:
	int levle;
	int map[Heighth][Width];
	virtual void setLv(SnakeNode *Snake) {};
	void addThing(SnakeNode *Snake, food *fd, mine *mn, poison *psn) {
		while (Snake->showNext() != nullptr) {
			if (Snake->isHead()) {
				map[Snake->sx()][Snake->sy()] = HEAD;
			}
			Snake = Snake->showNext();
			map[Snake->sx()][Snake->sy()] = BODY;
		}

		map[fd->sx()][fd->sy()] = FOOD;
		map[mn->sx()][mn->sy()] = MINE;
		map[psn->sx()][psn->sy()] = POISON;
	}

};
class Level1 :public Map {
public:
	void setLv() {
		this->levle = 1;
	}
	void setMap(SnakeNode *Snake, food *fd, mine *mn, poison *psn) {
		for (int i = 0; i < Width; i++) {
			for (int j = 0; j < Heighth; j++)map[j][i] = 0;
		}
		for (int i = 0; i < Width; i++) {
			map[0][i] = WALL;
			map[Heighth - 1][i] = WALL;
		}
		for (int i = 1; i < Heighth; i++) {
			map[i][0] = WALL;
			map[i][Width - 1] = WALL;
		}
		addThing(Snake, fd, mn, psn);
	}
};
void paint(Map *map) {
	for (int i = 0; i < Heighth; i++) {
		int m;
		for (int j = 0; j < Width; j++) {
			m = map->map[i][j];
			if (m == AIR)cout << ' ';
			else if (m == WALL)cout << '*';
			else if (m == HEAD)cout << '@';
			else if (m == BODY)cout << '#';
			else if (m == FOOD)cout << '&';
			else if (m == MINE)cout << '%';
			else if (m == POISON)cout << '$';
		}
		cout << endl;
	}
}

int main()
{
	int sx, sy;
	char cmd = 'a';
	int DyMsg;
	Level1 map;
	SnakeNode Snake(10, 20, 1);
	Snake.make(10);
	food fd;
	fd.setPosition();
	poison psn;
	psn.setPosition();
	mine mn;
	mn.setPosition();
	time_t start = clock();
	while (clock() - start < 100000) {
		map.setMap(&Snake, &fd, &mn, &psn);
		paint(&map);
		while (clock() - start < 100) {
			if (_kbhit()){
				char tcmd = cmd;
				cmd = _getch();
				if ((cmd == 'w' and tcmd == 's') or (cmd == 's' and tcmd == 'w') or (cmd == 'a' and tcmd == 'd') or (cmd == 'd' and tcmd == 'a'))cmd = tcmd;
				if (cmd != 'w' and cmd != 's' and cmd != 'a' and cmd != 'd') {
					cout << "Enter any direction command to continue..." << endl;
					cout << "If you still enter an un-directing command, the game will over.";
					cmd = _getch();
				}
			}
		}
		Snake.move(cmd);
		sx = Snake.sx();
		sy = Snake.sy();
		SnakeNode *temp = &Snake;
		while (temp != nullptr) {
			if (sx == temp->sx() and sy == temp->sy() and temp->sNo() != 1) {
				isAlive = false;
				DyMsg = 0;
				break;
			}
			temp = temp->showNext();
		}
		if (map.map[sx][sy] == WALL) {
			DyMsg = 1;
			isAlive = false;
		}
		else if (map.map[sx][sy] == FOOD) {
			fd.beEatenBy(&Snake);
			fd.setPosition();
			cmd = cmd;
		}
		else if (map.map[sx][sy] == MINE) {
			if (!mn.beEatenBy(&Snake)) {
				DyMsg = 2;
				isAlive = false;
			}
			mn.setPosition();
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
	}
}
