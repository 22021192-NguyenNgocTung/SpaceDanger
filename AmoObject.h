#pragma once
#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_

#define WIDTH_AMO 16
#define HEIGHT_AMO 45

#include "BaseObject.h"
class AmoObject : public BaseObject {
public:
	AmoObject();
	~AmoObject();
	void set_x_val(const int& xVal) { x_val_ = xVal; }
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_x_val() { return x_val_; }
	int get_y_val() { return y_val_; }

	void set_is_move(const bool& is_move) { is_move_ = is_move; }
	bool get_is_move() { return is_move_;}

	void HandelMove();
private:
	int x_val_;
	int y_val_;
	bool is_move_;
};
#endif // !AMO_OBJECT_H_

