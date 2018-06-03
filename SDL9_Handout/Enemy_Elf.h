#ifndef __ENEMY_ELF_H__
#define __ENEMY_ELF_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Elf :
	public Enemy
{
public:
	Enemy_Elf(int x, int y, int type);
	~Enemy_Elf();

private:
	bool spawning;
	void Move();
	void Draw(SDL_Texture* sprites);
	SDL_Texture* boss_sprite;
	int fire_rate, shot_cd;

	SDL_Rect bosscollider_1;
	SDL_Rect bosscollider_2;

	iPoint originalposition;
	Animation previous;
	Animation spawn;
	Animation stay;
	Animation stay2;
	Animation idle;
	Animation back, back2, back3,back4;
	Animation hand,hand2,hand3;
	Animation shoot;
	Path movement;


	int current_time, time_on_entry;
	bool timer = true;
	bool shooting = true;
	bool shooting2 = true;
	bool shooting3 = true;
	bool shurikens = true;
	bool shurikens2 = true;
	bool shurikens3 = true;
	bool shurikens4 = true;
	bool shurikens5 = true;
	bool shurikens6 = true;
	bool shurikens7 = true;
	int type;
};

#endif

