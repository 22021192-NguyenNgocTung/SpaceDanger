#pragma once
#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"

class LText {
public:
	LText();
	~LText();
	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,

	};
	bool LoadFromRenderedText(TTF_Font* font, SDL_Renderer* des);
	void setColor(Uint8 red, Uint8 blue, Uint8 green);
	void setColor(int type);
	void render(SDL_Renderer* des, SDL_Rect* clip );
	int getWidth() { return rect_text_.w; }
	int getHeight() { return rect_text_.h; }

	void set_pos(const int& x, const int& y) { rect_text_.x = x; rect_text_.y = y; }
	void set_Text(const std::string& text) { text_ = text; }
	std::string get_Text() { return text_; }
	SDL_Rect get_rect() { return rect_text_; }
private:
	std::string text_;
	SDL_Texture* texture_;
	SDL_Color text_Color_;
	SDL_Rect rect_text_;
};

#endif

