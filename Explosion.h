#pragma once
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 4 

class ExplosionObject : public BaseObject {
public:
	ExplosionObject();
	~ExplosionObject();
public:
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	bool LoadIMG(std::string path, SDL_Renderer* des);
	void Show(SDL_Renderer* des);

	int get_width_frame() const { return frame_width_; }
	int get_height_frame() const { return frame_height_; }
private:
	int frame_width_; 
	int frame_height_;

	int frame_;

	SDL_Rect frame_clip_[NUM_FRAME_EXP];
};

#endif // !EXPLOSION_H_

