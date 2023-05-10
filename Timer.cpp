#include "Timer.h"

LTimer::LTimer() {
	start_ticks_ = 0; 
	pause_ticks_ = 0; 

	started_ = false;
	paused_ = false;
}
LTimer::~LTimer() {

}
 void LTimer::start() {
	 started_ = true; 
	 paused_ = false; 

	 start_ticks_ = SDL_GetTicks();
	 pause_ticks_ = 0;
}
 void LTimer::stop() {
	 started_ = false;
	 paused_ = false;
 }
 void LTimer::pause() {
	 if (started_ && !paused_) {
		 paused_ = true;
		 pause_ticks_ = SDL_GetTicks() - start_ticks_;
		 start_ticks_ = 0;
	 }
 }
 void LTimer::unpause() {
	 if (started_ && paused_) {
		 paused_ = false;
		 start_ticks_ = SDL_GetTicks() - pause_ticks_;
		 pause_ticks_ = 0;
	 }
 }
 int LTimer::get_ticks() {
	 if (started_ == true) {
		 if (paused_ == true) {
			 return pause_ticks_;
		 }
		 else return SDL_GetTicks() - start_ticks_;
	 }
	 else {
		 return 0;
	 }
}