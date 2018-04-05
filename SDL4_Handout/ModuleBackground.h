#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* laterals = nullptr;
	SDL_Rect groundandtrees, Templesgate, fisrttrees, backtrees, rockground, trees, ground, groundgrass, grasstrees2, grasstrees4, grasstree, onlygrass, Temple, Temple2, lonelytree,toptree, toptrees, backfinal, sky, mountain, bambu, bambuback, lateral;
	float posx = 7000, posy = -480, grassy = 185;
	
	int alpha = 255;

};

#endif