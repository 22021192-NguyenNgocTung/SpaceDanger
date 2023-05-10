#include "BaseObject.h"
BaseObject::BaseObject() {
	p_object_ = NULL;
	rect_.x = 0; 
	rect_.y = 0; 
	rect_.w = 0; 
	rect_.h = 0;
}
BaseObject::~BaseObject() {
	Free();
}
bool BaseObject::LoadImg(std::string path, SDL_Renderer* renderer) {
	SDL_Texture* texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL) {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0 , 0, 255));
		texture = SDL_CreateTextureFromSurface(renderer, load_surface);
		if (texture != NULL) {
			rect_.w = load_surface->w; 
			rect_.h = load_surface->h;
			SDL_FreeSurface(load_surface);
		}
		
	}
	p_object_ = texture;
	return p_object_ != NULL;
 }
void BaseObject::Render(SDL_Renderer* des ) {
	SDL_Rect renderquad = { rect_.x , rect_.y , rect_.w , rect_.h };
	SDL_RenderCopy(des, p_object_, NULL , &renderquad);
}
void BaseObject::Free() {
	if (p_object_ != NULL) {
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}