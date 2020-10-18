#pragma once
#ifndef ITEM
#define ITEM
#include "Snake.h"
#include <cstdlib>

class item {
public:
	int x;
	int y;
	virtual bool beEatenBy(SnakeNode *Snake) {
		return true;
	}
	void setPosition() {
		x = rand() % (Width - 2) + 1;
		y = rand() % (Heighth - 2) + 1;
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
private:
	poison *nextPsn = nullptr;
public:
	bool isShown = true;
	bool beEatenBy(SnakeNode *Snake) {
		poison *temp = this;
		if (temp->x == Snake->sx() and temp->y == Snake->sy())temp->setPosition();
		do {
			temp = temp->nextPsn;
			if (temp->x == Snake->sx() and temp->y == Snake->sy()) {
				temp->setPosition();
				break;
			}
		} while (temp->nextPsn != nullptr);
		return Snake->eatPoison();
	}
	void createNext(int nums) {
		nextPsn = new poison;
		nextPsn->setPosition();
		nums--;
		if (nums != 0)nextPsn->createNext(nums);
	}
	poison *next() {
		return nextPsn;
	}
};
class mine :public item {
public:
	bool beEatenBy(SnakeNode *Snake) {
		return Snake->beenBombed();
	}
};
#endif // !ITEM.H
