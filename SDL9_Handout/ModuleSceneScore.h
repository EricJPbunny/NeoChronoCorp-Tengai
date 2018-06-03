#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
struct SDL_Texture;

class ModuleScore : public Module
{
public:
	ModuleScore();
	~ModuleScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	int font_score = 1;
	Mix_Music* mus = nullptr;
	SDL_Texture* graphics = nullptr;

	SDL_Rect score_sho, score_junis;
	
};

#endif // __MODULESCORE_H__