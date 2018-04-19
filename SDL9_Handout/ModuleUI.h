#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	int font_score = -1, font_time = 0;
	int alpha = 0;
	
	int time_on_entry = 0;
	int current_time = 0;
	bool aux = true;
	uint score = 0, time = 9;
	char score_text[10], time_text[2];
	SDL_Texture* graphics = nullptr;
	SDL_Texture* black = nullptr;
	Animation* current_animation;
	Animation start;
	SDL_Rect player1, player2, game_over, screen;
};

#endif // __MODULESCENESTART_H__