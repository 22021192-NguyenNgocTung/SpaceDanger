#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"

class BaseObject {
public :
	BaseObject();
	~BaseObject();
	void SetRect (int x, int y) {
		rect_.x = x, rect_.y = y;
	}
	SDL_Rect GetRect()const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }
	void SetTexture(SDL_Texture* texture) { p_object_ = texture; }
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des );
	void Free();
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};
#endif // !BASE_OBJECT_H_
