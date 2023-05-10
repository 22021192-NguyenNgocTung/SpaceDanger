#include "AmoObject.h"

AmoObject::AmoObject() {
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}
AmoObject::~AmoObject() {
	;
}
void AmoObject::HandelMove() {
	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y > SCREEN_HEIGHT) {
		is_move_ = false;
	}
}