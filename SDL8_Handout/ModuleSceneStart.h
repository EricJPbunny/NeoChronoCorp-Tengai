#ifndef __MODULESCENESTART_H__
#define __MODULESCENESTART_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleSceneStart : public Module
{
public:
	ModuleSceneStart();
	~ModuleSceneStart();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* start_screen = nullptr;
	SDL_Rect background, title, start;
	SDL_Rect cloud, cloud1, cloud2, cloud3, cloud4, cloud5, cloud6, cloud7;
	float posx = 0, posx1 = 0, posx2 = 0, posx3 = 0, posx4 = 0, posx5 = 0, posx6 = 0, posx7 = 0, posx8 = 0, posx9 = 0, posx10 = 0, posx11 = 0, posx12 = 0, posx13 = 0, posx14 = 0, posx15 = 0;
	int alpha_start = 255;
	int speed = 1;
	bool fade = true;

	Mix_Music* mus = nullptr;
};

#endif // __MODULESCENESTART_H__