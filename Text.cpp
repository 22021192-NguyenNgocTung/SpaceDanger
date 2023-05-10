#include "Text.h"

LText :: LText() {
	texture_ = NULL;
	rect_text_.x = 0;
	rect_text_.y = 0;
	text_Color_.g = 0;
	text_Color_.r = 0;
	text_Color_.b = 0;
}
LText :: ~LText() {
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		rect_text_.w = 0; 
		rect_text_.h = 0;
	}
}
void LText::setColor( Uint8 red, Uint8 green, Uint8 blue) {
	text_Color_.r = red; 
	text_Color_.g = green; 
	text_Color_.b = blue;
}
void LText::setColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0 ,0 };
		text_Color_ = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = {255, 255, 255};
		text_Color_ = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = { 0 ,0 ,0 };
		text_Color_ = color;
	}
}
bool LText::LoadFromRenderedText(TTF_Font* font , SDL_Renderer* des) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text_.c_str(), text_Color_);
	if (textSurface != NULL) {
		SDL_Texture* new_texture = SDL_CreateTextureFromSurface(des, textSurface);
		if (new_texture == NULL) {
			return false;
		}
		else {
			rect_text_.w = textSurface->w;
			rect_text_.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
		texture_ = new_texture;
	}
	return texture_ != NULL;
}
void LText::render(SDL_Renderer* des, SDL_Rect* clip  ) {
	SDL_Rect renderQuad = { rect_text_.x , rect_text_.y , rect_text_.w , rect_text_.h };
	if (clip != NULL) {
		renderQuad.w = clip->w; 
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(des, texture_, clip, &renderQuad, 0, NULL , SDL_FLIP_NONE);
}