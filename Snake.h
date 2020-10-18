#pragma once
#ifndef SNAKE
#define SNAKE
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define Width  40
#define Heighth  20
class SnakeNode
{
private:
	int x, nextX;
	int y, nextY;
	int No;
	int Length = 1;
	SnakeNode *nextNode = nullptr;
	char tcmd;
	SnakeNode(int x, int y, int No);
public:
	SnakeNode(int x, int y);
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
		if (Length != 1 and ((cmd == UP and tcmd == DOWN) 
			or (cmd == DOWN and tcmd == UP) 
			or (cmd == LEFT and tcmd == RIGHT) 
			or (cmd == RIGHT and tcmd == LEFT)))
			cmd = tcmd;
		if (No == 1) {
			nextX = x;
			nextY = y;
			switch (cmd) {
			case UP:
				y--;
				break;
			case LEFT:
				x--;
				break;
			case DOWN:
				y++;
				break;
			case RIGHT:
				x++;
				break;
			}
		}
		if (nextNode != nullptr) {
			nextNode->nextX = nextNode->x;
			nextNode->nextY = nextNode->y;
			nextNode->x = nextX;
			nextNode->y = nextY;
			nextNode->move(cmd);
			tcmd = cmd;
		}
	};
	void Longer() {
		Length++;
		SnakeNode *node, *temp;
		temp = this;
		while (temp->nextNode != nullptr)temp = temp->nextNode;
		node = new SnakeNode(nextX, nextY, Length);
		temp->nextNode = node;
	};
	bool beenBombed() {
		if (Length == 1)return false;
		SnakeNode *temp = this;
		SnakeNode *temp2, *temp3;
		while (temp->No < Length / 2)temp = temp->nextNode;
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
		while (temp->nextNode->nextNode != nullptr)temp = temp->nextNode;
		temp->nextNode = nullptr;
		delete temp->nextNode;
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
SnakeNode::SnakeNode(int x, int y) {
	this->x = x;
	this->y = y;
	this->No = 1;
}
SnakeNode::SnakeNode(int x, int y, int No) {
	this->x = x;
	this->y = y;
	this->No = No;
}
#endif