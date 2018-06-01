#ifndef __MODULESCENESELECT_H__
#define __MODULESCENESELECT_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleSceneSelect : public Module
{
public:
	ModuleSceneSelect();
	~ModuleSceneSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;

	SDL_Rect background, sho_face, sho_player, sho_name, junis_face, junis_player, junis_name, ui_1p, ui_2p, time;

};

#endif // __MODULESCENESELECT_H__