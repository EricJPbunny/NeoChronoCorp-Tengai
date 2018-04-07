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
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* laterals = nullptr;
	SDL_Texture* mid = nullptr;
	SDL_Texture* mid1 = nullptr;
	SDL_Rect groundandtrees, Templesgate, fisrttrees, backtrees, rockground, trees, ground, groundgrass, grasstrees2, grasstrees4, grasstree, onlygrass, Temple, Temple2, lonelytree,toptree, toptrees, backfinal, sky, mountain, bambu, bambuback, lateral;
	SDL_Rect fader, fademid;
	float posx = 7000, posy = -480, grassy = 185;
	bool fade = true;
	float alpha_mid = 0, alpha_mid1 = 255, alpha_graph2 = 255, alpha_graph1 = 0;

};

#endif