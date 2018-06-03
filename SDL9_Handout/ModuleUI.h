#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
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

	int pos_score = 0;

	bool update_score = false;
	
	int time_on_entry = 0;
	int current_time = 0;

	int num_life_koyori, num_life_sho, num_life_junis, num_ulti_sho = 2, num_ulti_junis;
	bool aux = true, enemies_movement = true, game_over_koyori = false, game_over_sho = false, game_over_junis= false;
	uint score_koyori = 0, score_sho = 0, score_junis = 0, time = 9;
	char player1_score[10], player2_score[10], player3_score[10], time_text[2], credit_text[2];

	SDL_Texture* graphics = nullptr;
	SDL_Texture* black = nullptr;
	Animation* current_animation;
	Animation* ulti_ui;
	Animation ulti_parchment, start;
	SDL_Rect player1, player2, player3, game_over, screen, credit;
	SDL_Rect life_koyori, life_sho, life_junis;
};

#endif // __MODULESCENESTART_H__