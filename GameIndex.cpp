#include "GameIndex.h"

GameIndex::GameIndex() {
	number_ = 0;
}
GameIndex::~GameIndex() {

}
void GameIndex::SetPos(const int& xPos) {
	for (int i = 0; i < NUM_HEART ; i++) {
		pos.push_back(xPos + i * 35 );
	}
}
void GameIndex::Show(SDL_Renderer* des) {
	
	for (int i = 0; i < NUM_HEART; i++) {
		rect_.x = pos[i];
		if (i < number_) {
			if (LoadImg("Image\\Heartfull.png", des)) {
				Render(des);
			}
		}
		else {
			if (LoadImg("Image\\Heart.png", des)) {
				Render(des);
			}
		}
	}
}
