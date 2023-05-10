#pragma once
#ifndef TIMER_H_
#define TIMER_H_

#include "CommonFunc.h"
class LTimer {
public :
	LTimer();
	~LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	int get_ticks();

	bool is_paused() { return paused_; }
	bool is_started() { return started_; }
private:
	int start_ticks_;
	int pause_ticks_;

	bool paused_;
	bool started_;
};
#endif // !TIMER_H_

