#pragma once
#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class Background : public BaseObject {
public:
	Background();
	~Background();
	void set_step(const int& step) { step_ = step; }
	int get_step() { return step_; }
	void ScrollingBackground();
	void Render(SDL_Renderer* dex);
	void set_clip();
private:
	SDL_Rect clip_;
	int step_;
};
#endif // !BACKGROUND_H_

