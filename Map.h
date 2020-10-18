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
#define PORTAL 8

class Map {
public:
	int level = 1;
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
		
		while (map[fd->sy()][fd->sx()] != AIR
			and map[fd->sy()][fd->sx()] != FOOD) {
			fd->setPosition();
		}
		map[fd->sy()][fd->sx()] = FOOD;
		while (map[mn->sy()][mn->sx()] != AIR
			and map[mn->sy()][mn->sx()] != MINE)
			mn->setPosition();
		map[mn->sy()][mn->sx()] = MINE;
		if (psn->isShown) {
			while (map[psn->sy()][psn->sx()] != AIR 
				and map[psn->sy()][psn->sx()] != POISON
				and map[psn->sy()][psn->sx()] != POISON_2)
				psn->setPosition();
			map[psn->sy()][psn->sx()] = POISON;
			psn->isShown = false;
		}
		else {
			while (map[psn->sy()][psn->sx()] != AIR
				and map[psn->sy()][psn->sx()] != POISON
				and map[psn->sy()][psn->sx()] != POISON_2)
				psn->setPosition();
			map[psn->sy()][psn->sx()] = POISON_2;
			psn->isShown = true;
		}
		while (psn->next() != nullptr) {
			if (psn->next()->isShown) {
				while (map[psn->next()->sy()][psn->next()->sx()] != AIR
					and map[psn->next()->sy()][psn->next()->sx()] != POISON
					and map[psn->next()->sy()][psn->next()->sx()] != POISON_2)
					psn->next()->setPosition();
				map[psn->next()->sy()][psn->next()->sx()] = POISON;
				psn->next()->isShown = false;
			}
			else {
				while (map[psn->next()->sy()][psn->next()->sx()] != AIR
					and map[psn->next()->sy()][psn->next()->sx()] != POISON
					and map[psn->next()->sy()][psn->next()->sx()] != POISON_2)
					psn->next()->setPosition();
				map[psn->next()->sy()][psn->next()->sx()] = POISON_2;
				psn->next()->isShown = true;
			}
			psn = psn->next();
		}
	}
	void setMap(SnakeNode *Snake, food *fd, mine *mn, poison *psn) {
		if (level == 1) {
			for (int i = 0; i < Heighth; i++) {
				for (int j = 0; j < Width; j++) {
					if (i == 0 or i == Heighth - 1)map[i][j] = WALL;
					else if (j == 0 or j == Width - 1)map[i][j] = WALL;
					else if (map[i][j] == PORTAL);
					else map[i][j] = AIR;
				}
			}
			addThing(Snake, fd, mn, psn);
		}
		else if (level == 2){
			for (int i = 0; i < Heighth; i++) {
				for (int j = 0; j < Width; j++) {
					if (i == 0 or i == Heighth - 1)map[i][j] = WALL;
					else if (j == 0 or j == Width - 1 )map[i][j] = WALL;
					else if ((i < 5 or i > 13) and (j == 19 or j == 20))map[i][j] = WALL;
					else if (map[i][j] == PORTAL);
					else map[i][j] = AIR;
				}
			}
			addThing(Snake, fd, mn, psn);
		}
	}
};


#endif // !MAP
