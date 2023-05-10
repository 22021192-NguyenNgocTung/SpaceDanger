#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() {
	rect_.x = 0; 
	rect_.y = 0;
	rect_.w = WIDTH_THREAT; 
	rect_.h = HEIGHT_THREAT;
	y_val_ = 0;
}
ThreatsObject::~ThreatsObject() {
}
void ThreatsObject::HandelMove(int& num_ , int x_ , Mix_Chunk* heart) {
	rect_.y += y_val_;
	if (rect_.y > SCREEN_HEIGHT) {
		rect_.y = -80;
		rect_.x = x_;
		num_--;
		if (num_ >= 1) {
			Mix_PlayChannel(-1, heart, 0);
		}
	}
}

void ThreatsObject::Reset(const int &x_border) {
	rect_.y = -80;
	rect_.x = x_border;
}
