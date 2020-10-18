#pragma once
#ifndef MAP
#define MAP
#include "Snake.h"
#include "item.h"
#define AIR 0
#define WALL 1
#define HEAD 2
#define BODY 3
#define FOOD 4
#define MINE 5
#define POISON 6
#define POISON_2 7

class Map {
public:
	int levle;
	int map[Heighth][Width];
	virtual void setLv(SnakeNode *Snake) {};
	void addThing(SnakeNode *Snake, food *fd, mine *mn, poison *psn) {
		if (Snake->isHead()) {
			map[Snake->sy()][Snake->sx()] = HEAD;
		}
		while (Snake->showNext() != nullptr) {
			Snake = Snake->showNext();
			map[Snake->sy()][Snake->sx()] = BODY;
		}

		map[fd->sy()][fd->sx()] = FOOD;
		map[mn->sx()][mn->sy()] = MINE;
		if (psn->isShown) {
			map[psn->sy()][psn->sx()] = POISON;
			psn->isShown = false;
		}
		else {
			map[psn->sy()][psn->sx()] = POISON_2;
			psn->isShown = true;
		}
		while (psn->next() != nullptr) {
			if (psn->next()->isShown) {
				map[psn->next()->sy()][psn->next()->sx()] = POISON;
				psn->next()->isShown = false;
			}
			else {
				map[psn->next()->sy()][psn->next()->sx()] = POISON_2;
				psn->next()->isShown = true;
			}
			psn = psn->next();
		}
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

#endif // !MAP.H
