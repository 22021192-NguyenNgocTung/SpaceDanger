#pragma once
#ifndef GAME_INDEX_H_
#define GAME_INDEX_H_

#define NUM_HEART 5

#include "CommonFunc.h"
#include "BaseObject.h"

class GameIndex : public BaseObject {
public:
	GameIndex(); 
	~GameIndex();

	void setNum(int number) {number_ = number; }
	int getNum() { return number_; }
	void SetPos(const int& xPos);
	void Show(SDL_Renderer* des);
private:
	int number_;
	std::vector<int> pos;

};


#endif // !PLAYRENDER_H_

