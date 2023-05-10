#include "CommonFunc.h"

bool SDL_CommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) {
	int left_a = object1.x; 
	int right_a = object1.x + object1.w; 
	int top_a = object1.y; 
	int bot_a = object1.y + object1.h; 

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bot_b = object2.y + object2.h;

	//case1 : size of object1 < object2 
	if (left_b < right_a && right_a < right_b) {
		if (top_b < bot_a && bot_a < bot_b) {
			return true;
		}
		if (top_b < top_a && top_a< bot_b) {
			return true;
		}
	}
	if (left_b < left_a && left_a < right_b) {
		if (top_b < bot_a && bot_a < bot_b) {
			return true;
		}
		if (top_b < top_a && top_a < bot_b) {
			return true;
		}
	}

	//case2 : size of object1 > object2 
	if (left_a < left_b && left_b < right_a) {
		if (top_a < bot_b && bot_b < bot_a) {
			return true; 
		}
		if (top_a < top_b && top_b < bot_a) {
			return true;
		}
	}
	if (left_a < right_b && right_b < right_a) {
		if (top_a < bot_b && bot_b < bot_a) {
			return true;
		}
		if (top_a < top_b && top_b < bot_a) {
			return true; 
		}
	}
	//case3 : size of object1 = object2 
	if (left_a == left_b && top_a == top_b && bot_a == bot_b) {
		return true;
	}
	return false;
}

int SDL_CommonFunc::Show_Menu(SDL_Renderer* des, TTF_Font* font , Mix_Chunk* click) {
	SDL_Surface* menu_surface = IMG_Load("Image\\Menu1.png"); 
	SDL_Texture* menu_texture = NULL;
	if (menu_surface != NULL) {
		SDL_SetColorKey(menu_surface, SDL_TRUE, SDL_MapRGB(menu_surface->format, 0, 0, 255));
		menu_texture = SDL_CreateTextureFromSurface(des, menu_surface);
	}
	const int kItem = 4; 
	LText ItemMenu[kItem]; 
	SDL_Rect pos_arr[kItem];
	ItemMenu[0].set_Text("PLAY GAME");
	ItemMenu[0].setColor(LText::WHITE_TEXT);
	ItemMenu[0].LoadFromRenderedText(font, des);
	ItemMenu[0].set_pos(SCREEN_WIDTH/2 - ItemMenu[0].getWidth() / 2, 377);
	pos_arr[0] = ItemMenu[0].get_rect();

	ItemMenu[1].set_Text("RANK");
	ItemMenu[1].setColor(LText::WHITE_TEXT);
	ItemMenu[1].LoadFromRenderedText(font, des);
	ItemMenu[1].set_pos(SCREEN_WIDTH / 2 - ItemMenu[1].getWidth() / 2, 442);
	pos_arr[1] = ItemMenu[1].get_rect();

	ItemMenu[2].set_Text("INTRUCTION");
	ItemMenu[2].setColor(LText::WHITE_TEXT);
	ItemMenu[2].LoadFromRenderedText(font, des);
	ItemMenu[2].set_pos(SCREEN_WIDTH / 2 - ItemMenu[2].getWidth() / 2, 507);
	pos_arr[2] = ItemMenu[2].get_rect();

	ItemMenu[3].set_Text("QUIT");
	ItemMenu[3].setColor(LText::WHITE_TEXT);
	ItemMenu[3].LoadFromRenderedText(font, des);
	ItemMenu[3].set_pos(SCREEN_WIDTH / 2 - ItemMenu[3].getWidth() / 2, 572);
	pos_arr[3] = ItemMenu[3].get_rect();
	
	int x, y;

	bool selected[4] = {0 ,0 , 0 , 0};
	SDL_Event events; 
	while (true) {
		SDL_RenderCopy(des, menu_texture, NULL, NULL);
		while (SDL_PollEvent(&events) != 0) {
			if (events.type == SDL_QUIT) {
				return 3;
			}
			SDL_GetMouseState(&x, &y);
			for (int i = 0; i < kItem; i++) {
				if (x >= pos_arr[i].x && x <= (pos_arr[i].x + pos_arr[i].w) &&
					y >= pos_arr[i].y && y <= (pos_arr[i].y + pos_arr[i].h)) {
					selected[i] = 1;
					ItemMenu[i].setColor(LText::RED_TEXT);
				}
				else {
					selected[i] = 0;
					ItemMenu[i].setColor(LText::WHITE_TEXT);
				}
			}
			 if (events.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < kItem; i++) {
					if (x >= pos_arr[i].x && x <= (pos_arr[i].x + pos_arr[i].w) &&
						y >= pos_arr[i].y && y <= (pos_arr[i].y + pos_arr[i].h)) {
						Mix_PlayChannel(-1, click, 0);
						return i;
					}
				}
			}
			else if (events.key.keysym.sym == SDLK_ESCAPE) {
				return 3;
			}
		}
		for (int i = 0; i < kItem; i++) {
			ItemMenu[i].LoadFromRenderedText(font, des);
			ItemMenu[i].render(des, NULL);
		}
		SDL_RenderPresent(des);
	}
}
int SDL_CommonFunc::Show_Instruction(SDL_Renderer* des, TTF_Font* font , Mix_Chunk* click) {
	SDL_Surface* intr_surface = IMG_Load("Image\\Instruction.png");
	SDL_Texture* intr_texture = NULL; 
	if (intr_surface != NULL) {
		SDL_SetColorKey(intr_surface, SDL_TRUE, SDL_MapRGB(intr_surface->format, 0, 0, 255)); 
		intr_texture = SDL_CreateTextureFromSurface(des, intr_surface);
	}
	LText back; 
	SDL_Rect pos_back; 
	back.set_Text("Back to Menu");
	back.setColor(LText::WHITE_TEXT); 
	back.LoadFromRenderedText(font, des); 
	back.set_pos(SCREEN_WIDTH - back.getWidth() - 33, 30);
	pos_back = back.get_rect();
	bool selected = false;

	int x, y; 
	SDL_Event events;
	while (true) {
		SDL_RenderCopy(des, intr_texture, NULL, NULL);
		while (SDL_PollEvent(&events) != 0) {
			if (events.type == SDL_QUIT) {
				return 0;
			}
			else if (events.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&x, &y);
				if (x >= pos_back.x && x <= (pos_back.x + pos_back.w)
						&& y >= pos_back.y && y <= (pos_back.y + pos_back.h)) {
						selected = 1;
						back.setColor(LText::RED_TEXT);
					}
					else {
						selected = 0;
						back.setColor(LText::WHITE_TEXT);
					}
				}
			else if (events.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
					if (x >= pos_back.x && x <= (pos_back.x + pos_back.w) &&
						y >= pos_back.y && y <= (pos_back.y + pos_back.h)) {
						Mix_PlayChannel(-1, click, 0);
						return 1;
				}
			}
			else if (events.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}
		}
		back.LoadFromRenderedText(font, des);
		back.render(des, NULL);
		
		SDL_RenderPresent(des);
	}
}
int SDL_CommonFunc::Show_Rank(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* click) {
	SDL_Surface* rank_surface = IMG_Load("Image\\Rank.png");
	SDL_Texture* rank_texture = NULL;
	if (rank_surface != NULL) {
		SDL_SetColorKey(rank_surface, SDL_TRUE, SDL_MapRGB(rank_surface->format, 0, 0, 255));
		rank_texture = SDL_CreateTextureFromSurface(des, rank_surface);
	}
	LText back;
	SDL_Rect pos_back;
	back.set_Text("Back to Menu");
	back.setColor(LText::WHITE_TEXT);
	back.LoadFromRenderedText(font, des);
	back.set_pos(SCREEN_WIDTH - back.getWidth() - 33, 30);
	pos_back = back.get_rect();
	bool selected = false;

	LText top[3];
	std::string Top[3]; 
	std::ifstream fin("Score.txt");
	if (fin.is_open()) {
		for (int i = 0; i < 3; i++) {
			fin >> Top[i];
		}
	}
	else return 0;

	top[0].set_Text(Top[0]); 
	top[0].setColor(222 , 187 , 38 );
	top[0].LoadFromRenderedText(font, des);
	top[0].set_pos(190, 270);

	top[1].set_Text(Top[1]);
	top[1].setColor(228 , 223 , 213);
	top[1].LoadFromRenderedText(font, des);
	top[1].set_pos(400, 340);

	top[2].set_Text(Top[2]);
	top[2].setColor(238 , 138 , 0);
	top[2].LoadFromRenderedText(font, des);
	top[2].set_pos(30, 440);

	int x, y;
	SDL_Event events;
	while (true) {
		SDL_RenderCopy(des, rank_texture, NULL, NULL);
		while (SDL_PollEvent(&events) != 0) {
			if (events.type == SDL_QUIT) {
				return 0;
			}
			else if (events.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&x, &y);
				if (x >= pos_back.x && x <= (pos_back.x + pos_back.w)
					&& y >= pos_back.y && y <= (pos_back.y + pos_back.h)) {
					selected = 1;
					back.setColor(LText::RED_TEXT);
				}
				else {
					selected = 0;
					back.setColor(LText::WHITE_TEXT);
				}
			}
			else if (events.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x >= pos_back.x && x <= (pos_back.x + pos_back.w) &&
					y >= pos_back.y && y <= (pos_back.y + pos_back.h)) {
					Mix_PlayChannel(-1, click, 0);
					return 1;
				}
			}
			else if (events.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}
		}
		back.LoadFromRenderedText(font, des);
		back.render(des, NULL);
		for (int i = 0; i < 3; i++) {
			top[i].render(des ,NULL);
		}
		SDL_RenderPresent(des);
	}
}
int SDL_CommonFunc::Show_TryAgain(SDL_Renderer* des, TTF_Font* font , TTF_Font* font_ , int score_ ,Mix_Chunk* click) {
	SDL_Surface* menu_surface = IMG_Load("Image\\Play_Again.png");
	SDL_Texture* menu_texture = NULL;
	if (menu_surface != NULL) {
		SDL_SetColorKey(menu_surface, SDL_TRUE, SDL_MapRGB(menu_surface->format, 0, 0, 255));
		menu_texture = SDL_CreateTextureFromSurface(des, menu_surface);
	}
	const int kItem = 4;
	LText ItemMenu[kItem];
	SDL_Rect pos_arr[kItem];
	std::string str = "x"; 
	str += std::to_string(score_);
	ItemMenu[0].set_Text(str);
	ItemMenu[0].setColor(LText::WHITE_TEXT);
	ItemMenu[0].LoadFromRenderedText(font_, des);
	ItemMenu[0].set_pos(SCREEN_WIDTH / 2 , 345);
	pos_arr[0] = ItemMenu[0].get_rect();

	ItemMenu[1].set_Text("HOME");
	ItemMenu[1].setColor(LText::WHITE_TEXT);
	ItemMenu[1].LoadFromRenderedText(font, des);
	ItemMenu[1].set_pos(SCREEN_WIDTH / 2 - ItemMenu[1].getWidth() / 2, 433);
	pos_arr[1] = ItemMenu[1].get_rect();
	
	ItemMenu[2].set_Text("TRY AGAIN");
	ItemMenu[2].setColor(LText::WHITE_TEXT);
	ItemMenu[2].LoadFromRenderedText(font, des);
	ItemMenu[2].set_pos(SCREEN_WIDTH / 2 - ItemMenu[2].getWidth() / 2, 510);
	pos_arr[2] = ItemMenu[2].get_rect();

	ItemMenu[3].set_Text("QUIT");
	ItemMenu[3].setColor(LText::WHITE_TEXT);
	ItemMenu[3].LoadFromRenderedText(font, des);
	ItemMenu[3].set_pos(SCREEN_WIDTH / 2 - ItemMenu[3].getWidth() / 2, 587);
	pos_arr[3] = ItemMenu[3].get_rect();

	
	int x, y;

	bool selected[4] = { 0 , 0 , 0 , 0};
	SDL_Event events;
	while (true) {
		SDL_RenderCopy(des, menu_texture, NULL, NULL);
		while (SDL_PollEvent(&events) != 0) {
			if (events.type == SDL_QUIT) {
				return 3;
			}
			else if (events.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&x, &y);
				for (int i = 1; i < kItem; i++) {
					if (x >= pos_arr[i].x && x <= (pos_arr[i].x + pos_arr[i].w) 
						&& y >= pos_arr[i].y && y <= (pos_arr[i].y + pos_arr[i].h)) {
							selected[i] = 1;
							ItemMenu[i].setColor(LText::RED_TEXT);
					}
					else {
						if (selected[i] == 1) {
							selected[i] = 0;
							ItemMenu[i].setColor(LText::WHITE_TEXT);
						}
					}
				}
			}
			else if (events.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (int i = 1; i < kItem; i++) {
					if (x >= pos_arr[i].x && x <= (pos_arr[i].x + pos_arr[i].w) &&
						y >= pos_arr[i].y && y <= (pos_arr[i].y + pos_arr[i].h)) {
						Mix_PlayChannel(-1, click, 0);
						return i;
					}
				}
			}
			else if (events.key.keysym.sym == SDLK_ESCAPE) {
				return 3;
			}
		}
		ItemMenu[0].LoadFromRenderedText(font_, des);
		ItemMenu->render(des, NULL);
		for (int i = 1; i < kItem; i++) {
			ItemMenu[i].LoadFromRenderedText(font, des);
			ItemMenu[i].render(des, NULL);
		}
		
		SDL_RenderPresent(des);
	}
}