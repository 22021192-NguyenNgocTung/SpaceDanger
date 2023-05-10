#include "MainObject.h"

MainObject::MainObject() {
	rect_.x = 0; 
	rect_.y = 0; 
	rect_.w = MAINOBJECT_WIDTH; 
	rect_.h = MAINOBJECT_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject() {

}
void MainObject::HandelInputAction(SDL_Event events , SDL_Renderer* des ,Mix_Chunk* amo) {
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		AmoObject* p_amo = new AmoObject();
		p_amo->LoadImg("Image\\AmoObject.png", des);
		p_amo->SetRect(this->rect_.x + MAINOBJECT_WIDTH/2 - WIDTH_AMO/2 , this->rect_.y + HEIGHT_AMO);
		p_amo->set_y_val(-19);
		p_amo->set_is_move(true);
		p_amo_list_.push_back(p_amo);
		Mix_PlayChannel(-1, amo, 0);
	}
	else if (events.type = SDL_MOUSEMOTION) {
		int x, y; 
		SDL_GetMouseState(&x, &y);
		SetRect(x - MAINOBJECT_WIDTH/2, y - MAINOBJECT_HEIGHT/2);
	}
}
void MainObject::HandelAmo(SDL_Renderer* des) {
	for (int i = 0; i < p_amo_list_.size(); i++) {
		AmoObject* p_amo = p_amo_list_[i];
		if (p_amo != NULL) {
			if (p_amo->get_is_move() == true) {
				p_amo->HandelMove();
				p_amo->Render(des);
			}
			else {
				p_amo_list_.erase(p_amo_list_.begin() + i);
				if (p_amo != NULL) {
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}
void MainObject::RemoveAmo(const int& idx) {
	int size_amo = p_amo_list_.size();
	if (size_amo > 0 && idx < size_amo) {
		AmoObject* p_amo = p_amo_list_[idx];
		p_amo_list_.erase(p_amo_list_.begin() + idx);
		if (p_amo != NULL) {
			delete p_amo;
			p_amo = NULL;
		}
	}
}