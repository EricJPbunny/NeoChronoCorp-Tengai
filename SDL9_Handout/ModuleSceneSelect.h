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

	SDL_Rect background_1p, background_2p, sho_face, sho_player, sho_name, junis_face, junis_player, junis_name, ui_1p, ui_2p, time, credit;
	Animation sho_sprite, junis_sprite;
	SDL_Rect junis_anim;
	SDL_Rect sho_anim;

	Mix_Chunk* change_player = nullptr;
	Mix_Chunk* select_sho = nullptr;
	Mix_Chunk* select_junis = nullptr;

	bool one_player = true;
	bool sho_p1 = true;

	bool timer = true;
	int current_time, time_on_entry;

	char time_text[2], credit_text[2];

	int time_num = 9;

	int font_time = 0, font_score = 1;



};

#endif // __MODULESCENESELECT_H__