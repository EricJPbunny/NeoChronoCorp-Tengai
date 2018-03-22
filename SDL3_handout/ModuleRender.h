#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;
typedef struct _Mix_Music Mix_Music;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = nullptr);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* tex = nullptr;
	Mix_Music* mus = nullptr;
};

#endif //__ModuleRenderer_H__