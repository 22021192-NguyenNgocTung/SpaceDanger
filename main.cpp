#include "CommonFunc.h"
#include "BaseObject.h"
#include "BaseObject.h"
#include "BackGround.h"
#include "ThreatsObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "Text.h"
#include "GameIndex.h"
#include "Explosion.h"

Background g_background;
MainObject human_object;
ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];
ExplosionObject explosion;

LText time_game;
LText scores;

GameIndex health;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_back = NULL;


int score = 0; 
int speed_game = 0;
bool is_running = true;
bool is_showmenu = true; 
bool is_rank = true ;
bool is_instruction = true;
bool is_play = true; 
bool is_playagain = true;
bool Init_SDL() {
	bool success = true; 
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	
	g_window = SDL_CreateWindow(WindowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		success = false; 
	}
	else {
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer == NULL) {
			success = false;
		}
		else {
			SDL_RenderSetLogicalSize(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, 
				RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				success = false;
			}
			if (TTF_Init() == -1 ) {
				success = false;
			}
			font_time = TTF_OpenFont("font\\SVN-Caprica Script.ttf", 30);
			font_menu = TTF_OpenFont("font\\SVN-Cookies.ttf", 30);
			font_back = TTF_OpenFont("font\\SVN-Cookies.ttf", 60);
			if (font_time == NULL) {
				success = false;
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				success = false;
			}
		}
	}
	return success;
}
bool Load_game() {
	if (g_background.LoadImg("Image\\BackGround.png", g_renderer) == false) {
		return false;
	}
	if (human_object.LoadImg("Image\\MainObject.png", g_renderer) == false) {
		return false;
	}
	for (int i = 0; i < NUM_THREATS; i++) {
		ThreatsObject* p_threat = (p_threats + i);
		if (p_threat->LoadImg("Image\\ThreatObject.png", g_renderer) == false) {
			return false;
		}
	}
	time_game.setColor(LText::WHITE_TEXT);
	scores.setColor(LText::WHITE_TEXT);
	if (!explosion.LoadIMG("Image\\ExplosionObject.png", g_renderer)) {
		return false;
	}
	explosion.set_clip();
	g_music = Mix_LoadMUS("Sound\\backgound_sound.wav"); 
	if (g_music == NULL) {
		return false;
	}
	g_amo = Mix_LoadWAV("Sound\\amo.wav");
	if (g_amo == NULL) {
		return false;
	}
	g_exp = Mix_LoadWAV("Sound\\explosion.wav" );
	if (g_exp == NULL) {
		return false;
	}
	g_heart = Mix_LoadWAV("Sound\\heart.wav");
	if (g_heart == NULL) {
		return false; 
	}
	g_click = Mix_LoadWAV("Sound\\Click_Mouse.wav");
	if (g_click == NULL) {
		return false;
	}
	g_endgame = Mix_LoadWAV("Sound\\endgame.wav");
	if (g_endgame == NULL) {
		return false;
	}
	return true;
}
void reset_game() {
	g_background.set_step(2);
	human_object.SetRect(SCREEN_WIDTH / 2 - MAINOBJECT_WIDTH / 2, 400);
	for (int i = 0; i < NUM_THREATS; i++) {
		ThreatsObject* p_threat = p_threats + i;
		p_threat->SetRect( i * 110 + rand() % 30, -rand() % (SCREEN_WIDTH - 60));
		p_threat->set_y_val(5);
	}
	score = 0;
	speed_game = 0;
	num = 5;
}
void show_menu() {
	int chouse = SDL_CommonFunc::Show_Menu(g_renderer, font_menu,g_click);
	if (chouse == 0) {
		is_play = true;
		is_rank = false;
		is_instruction = false;
		is_playagain = true;
	}
	else if (chouse == 1) {
		is_rank = true;
	}
	else if( chouse == 2){
		is_instruction = true;
	}
	else {
		is_running = false; 
		is_rank = false;
		is_rank = false;
		is_instruction = false; 
		is_play = false; 
		is_playagain = false; 
	}
}
void rank() {
	int chouse = SDL_CommonFunc::Show_Rank(g_renderer, font_back,g_click);
	if (chouse == 1) {
		is_showmenu = true;
		is_rank = false;
		is_instruction = false;
		is_play = false;
		is_playagain = false;
	}
	else {
		is_running = false;
		is_rank = false;
		is_instruction = false;
		is_play = false;
		is_playagain = false;
	}
}
void instruction() {
	int chouse = SDL_CommonFunc::Show_Instruction(g_renderer, font_back , g_click);
	if (chouse == 1) {
		is_showmenu = true;
		is_instruction = false;
		is_rank = false;
		is_play = false; 
		is_playagain = false; 
	}
	else {
		is_running = false; 
		is_instruction = false; 
		is_rank = false;
		is_play = false; 
		is_playagain = false; 
	}
}
void play_game() {
	LTimer fps_timer;
	reset_game();
	Uint32 time_begin = SDL_GetTicks();

	int frame_width = explosion.get_width_frame();
	int frame_height = explosion.get_height_frame();
	while (is_play) {
		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT || g_event.key.keysym.sym == SDLK_ESCAPE) {
				is_play = false;
				is_running = false;
				is_playagain = false;
			}
			human_object.HandelInputAction(g_event, g_renderer , g_amo);
		}
		if (is_running == true) {
			SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			SDL_RenderClear(g_renderer);

			g_background.Render(g_renderer);
			g_background.ScrollingBackground();


			human_object.HandelAmo(g_renderer);
			human_object.Render(g_renderer);

			for (int i = 0; i < NUM_THREATS; i++) {
				ThreatsObject* p_threat = p_threats + i;
				p_threat->HandelMove(num, i * 110  + rand() % 30 , g_heart);
				if (num >= 1) {
					p_threat->Render(g_renderer);
					bool is_ColwithThreat = SDL_CommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect());
					if (is_ColwithThreat) {
						is_play = false;
						Mix_PlayChannel(-1, g_endgame, 0);
						break;
					}
					std::vector <AmoObject*> human_amo_list = human_object.GetAmoList();
					for (int am = 0; am < human_amo_list.size(); am++) {
						AmoObject* p_amo = human_amo_list[am];
						if (p_amo != NULL) {
							bool is_ColwithAmo = SDL_CommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
							if (is_ColwithAmo) {
								Mix_PlayChannel(-1, g_exp, 0);
								score++;
								for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
									explosion.set_frame(ex);
									explosion.SetRect(p_threat->GetRect().x + WIDTH_THREAT/2 - frame_width/2 ,
										p_threat->GetRect().y + HEIGHT_THREAT/2 - frame_height/2);
									explosion.Show(g_renderer);
								}
								p_threat->Reset( i * 110 + rand() % 30);
								human_object.RemoveAmo(am);  
							}
						}
					}

				}
				else {
					is_play = false;
					Mix_PlayChannel(-1, g_endgame, 0);
				}

			}
				SDL_Rect rect;
				rect.x = 0;
				rect.y = 0;
				rect.w = SCREEN_WIDTH;
				rect.h = 50;

				SDL_SetRenderDrawColor(g_renderer, 31, 196, 115, 255);
				SDL_RenderFillRect(g_renderer, &rect);

				health.setNum(num);
				health.SetPos(5);
				health.Show(g_renderer);

				std::string str_score = "Score: " + std::to_string(score);
				scores.set_Text(str_score);
				scores.LoadFromRenderedText(font_time, g_renderer);
				scores.set_pos(SCREEN_WIDTH - scores.getWidth() - 20, 50 /2  - scores.getHeight() / 2);
				scores.render(g_renderer, NULL);
				std::string str_time = "Time: ";

				Uint32 time_val = (SDL_GetTicks() - time_begin) / 1000;
				std::string str_val = std::to_string(time_val);
				str_time += str_val;
				time_game.set_Text(str_time);
				time_game.LoadFromRenderedText(font_time, g_renderer);
				time_game.set_pos(SCREEN_WIDTH / 2 - time_game.getWidth()/2, 50 / 2 - time_game.getHeight() / 2);
				time_game.render(g_renderer, NULL);

				SDL_RenderPresent(g_renderer);
				int real_imp_time = fps_timer.get_ticks();
				int time_one_frame = 1000 / (FRAME_PER_SECOND + score / 10);
				if (real_imp_time < time_one_frame) {
					int delay_time = time_one_frame - real_imp_time;
					SDL_Delay(delay_time);
				}
		}
	}
}
void play_again() {
	int chouse = SDL_CommonFunc::Show_TryAgain(g_renderer, font_menu, font_back, score, g_click);
	if (chouse == 1) {
		is_showmenu = true;
		is_instruction = false;
		is_rank = false;
		is_play = false;
		is_playagain = false;
	}
	else if (chouse == 2) {
		is_play = true;
		is_showmenu = false;
		is_instruction = false; 
		is_rank = false; 
	}
	else if (chouse == 3 ){
		is_running = false;
	}
}
void update_rank(std::string path) {
	int arr[4];
	std::ifstream fin(path);
	if (fin.is_open()) {
		for (int i = 0; i < 3; i++) {
			fin >> arr[i];
		}
		arr[3] = score;
		std::sort(arr, arr + 4, std::greater<int>());
		fin.close();
	}
	else {
		std::cerr << "Can't open file "<< path << std::endl;
		is_playagain = false;
		is_running = false;
	}
	std::ofstream fout(path);
	if (fout.is_open()) {
		for (int i = 0; i < 3; i++) {
			fout << arr[i] << std::endl;
		}
		fout.close();
	}
}
void close() {
	Mix_FreeChunk(g_amo);
	Mix_FreeChunk(g_exp);
	Mix_FreeChunk(g_heart);
	Mix_FreeChunk(g_click);
	Mix_FreeChunk(g_endgame);
	g_amo = NULL; 
	g_exp = NULL; 
	g_heart = NULL;
	g_click = NULL;
	g_endgame = NULL;
	Mix_FreeMusic(g_music);
	g_music = NULL; 

	TTF_CloseFont(font_back); 
	font_back = NULL; 
	TTF_CloseFont(font_time); 
	font_time = NULL;
	TTF_CloseFont(font_menu);
	font_menu = NULL;

	g_background.Free();
	human_object.Free();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}
int main(int argc, char* argv[]) {
	if (Init_SDL() == false) {
		return -1;
	}
	if (Load_game() == false) {
		return -1;
	}
	Mix_PlayMusic(g_music, -1);
	while(is_running) {
		
		if (is_showmenu == true) {
			show_menu();
		}
		if (is_rank == true) {
			rank();
		}
		if (is_instruction == true) {
			instruction();
		}
		play_game();
		update_rank("Score.txt");
		if (is_playagain == true) {
			play_again();
		}
	}
	delete[]p_threats;
	close();
	return 0;
}