#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include "Text.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static SDL_Event g_event; 
static std::string WindowTitle = "GAME";
static Mix_Music* g_music = NULL;
static Mix_Chunk* g_amo = NULL; 
static Mix_Chunk* g_exp = NULL; 
static Mix_Chunk* g_endgame = NULL;
static Mix_Chunk* g_heart = NULL;
static Mix_Chunk* g_click = NULL;

const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 560; 
const int SCREEN_HEIGHT = 800 ;
const int SCREEN_BPP = 32; 
const int NUM_THREATS = 5; 

const int COLOR_KEY_R = 102; 
const int COLOR_KEY_G = 38; 
const int COLOR_KEY_B = 255;
const int RENDER_DRAW_COLOR = 0xFF;

static int num = 5;
namespace SDL_CommonFunc {
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	int Show_Menu(SDL_Renderer* des, TTF_Font* font , Mix_Chunk* click);
	int Show_TryAgain(SDL_Renderer* des, TTF_Font* font ,TTF_Font* font_ ,  int score_ , Mix_Chunk* click);
	int Show_Rank(SDL_Renderer* des, TTF_Font* font, Mix_Chunk* click);
	int Show_Instruction(SDL_Renderer* des, TTF_Font* font,Mix_Chunk* click);
}
#endif // !COMMONFUNC_HH
