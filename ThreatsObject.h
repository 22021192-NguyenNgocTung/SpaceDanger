#ifndef  THREATSOBJECT_H_
#define THREATSOBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"


#define WIDTH_THREAT 80
#define HEIGHT_THREAT 50
class ThreatsObject : public BaseObject {
public:
	ThreatsObject();
	~ThreatsObject();

	void HandelMove(int& num_ , int x_, Mix_Chunk* heart);
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_y_val() { return y_val_; }

	int get_y() { return rect_.y; }
	void Reset(const int &x_border);
private:
	int y_val_;
};
#endif // ! THREATOBJECT_H_
