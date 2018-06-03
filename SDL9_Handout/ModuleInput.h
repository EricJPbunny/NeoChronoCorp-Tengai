#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 100

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum BUTTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_DOWN,
	BUTTON_REPEAT,
	BUTTON_UP,
};

class ModuleInput : public Module
{
public:
	
	SDL_GameController* controller;
	SDL_GameController* controller2;
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	BUTTON_STATE button[MAX_BUTTONS];
	KEY_STATE controller_A_button;
	KEY_STATE controller_X_button;
	KEY_STATE controller_B_button;
	KEY_STATE controller_START_button;
	KEY_STATE controller_A_button2;
	KEY_STATE controller_X_button2;
	KEY_STATE controller_B_button2;
	KEY_STATE controller_START_button2;
};

#endif // __ModuleInput_H__