#include "BackGround.h"

Background::Background() {
	step_ = 0; 
	clip_.x = 0; 
	clip_.y = 800;
	clip_.w = SCREEN_WIDTH;
	clip_.h = SCREEN_HEIGHT;
}
Background::~Background() {

}
void Background::set_clip() {
	clip_.y = 800;
}
void Background:: ScrollingBackground() {
	clip_.y -= step_;
	if (clip_.y <= 0) {
		set_clip();
	}
}
void Background::Render(SDL_Renderer* des) {
	SDL_Rect rect = { rect_.x , rect_.y , SCREEN_WIDTH , SCREEN_HEIGHT }; 
	SDL_Rect clip = { clip_.x , clip_.y , clip_.w , clip_.h };
	SDL_RenderCopy(des, p_object_, &clip, &rect);
}