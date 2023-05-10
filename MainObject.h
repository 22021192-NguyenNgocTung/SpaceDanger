#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "AmoObject.h"
#define MAINOBJECT_WIDTH  66
#define MAINOBJECT_HEIGHT 102
class MainObject : public BaseObject {
public:
	MainObject();
	~MainObject();
	void HandelInputAction(SDL_Event events, SDL_Renderer* des ,Mix_Chunk* amo);
	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list_ = amo_list; }
	std::vector <AmoObject*> GetAmoList() const { return p_amo_list_; }
	void HandelAmo(SDL_Renderer* des);
	void RemoveAmo(const int& idx);
private:
	int x_val_;
	int y_val_;
	std::vector<AmoObject*> p_amo_list_;
};

#endif // !
