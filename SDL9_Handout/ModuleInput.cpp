#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	controller_A_button = KEY_IDLE;
	controller_X_button = KEY_IDLE;
	controller_START_button = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	SDL_Init(SDL_INIT_GAMECONTROLLER);


	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return update_status::UPDATE_STOP;
		else if (event.type == SDL_CONTROLLERDEVICEADDED) {
			if (!controller) {
				controller = SDL_GameControllerOpen(0);
				if (controller) {
					LOG("Controller loaded correctly");
				}
				else if (controller && !controller2) {
					controller2 = SDL_GameControllerOpen(1);
				}
				else LOG("Could not open gamecontroller: %s", SDL_GetError());
			}
		}
		else if (event.type == SDL_CONTROLLERDEVICEREMOVED) {
			if (event.cdevice.which == 0) {
				SDL_GameControllerClose(controller);
				controller = nullptr;
				LOG("Controller 1 removed!\n");
			}
			if (event.cdevice.which == 1) {
					SDL_GameControllerClose(controller2);
					controller2 = nullptr;
					LOG("Controller 2 removed!\n");
			}

			
		}
	}
	Uint8 button_state_A = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
	Uint8 button_state_X = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
	Uint8 button_state_B = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
	Uint8 button_state_START = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
	if (button_state_A) {
		if (controller_A_button == KEY_IDLE) controller_A_button = KEY_DOWN;
		else controller_A_button = KEY_REPEAT;
	}
	else {
		if (controller_A_button == KEY_REPEAT || controller_A_button == KEY_DOWN) controller_A_button = KEY_UP;
		else controller_A_button = KEY_IDLE;
	}

	if (button_state_X) {
		if (controller_X_button == KEY_IDLE) controller_X_button = KEY_DOWN;
		else controller_X_button = KEY_REPEAT;
	}
	else {
		if (controller_X_button == KEY_REPEAT || controller_X_button == KEY_DOWN) controller_X_button = KEY_UP;
		else controller_X_button = KEY_IDLE;
	}

	if (button_state_B) {
		if (controller_B_button == KEY_IDLE) controller_B_button = KEY_DOWN;
		else controller_B_button = KEY_REPEAT;
	}
	else {
		if (controller_B_button == KEY_REPEAT || controller_B_button == KEY_DOWN) controller_B_button = KEY_UP;
		else controller_B_button = KEY_IDLE;
	}



	if (button_state_START) {
		if (controller_START_button == KEY_IDLE) controller_START_button = KEY_DOWN;
		else controller_START_button = KEY_REPEAT;
	}
	else {
		if (controller_START_button == KEY_REPEAT || controller_START_button == KEY_DOWN) controller_START_button = KEY_UP;
		else controller_START_button = KEY_IDLE;
	}
	Uint8 button_state_A2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A);
	Uint8 button_state_X2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_X);
	Uint8 button_state_B2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B);
	Uint8 button_state_START2 = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START);
	if (button_state_A2) {
		if (controller_A_button2 == KEY_IDLE) controller_A_button2 = KEY_DOWN;
		else controller_A_button2 = KEY_REPEAT;
	}
	else {
		if (controller_A_button2 == KEY_REPEAT || controller_A_button2 == KEY_DOWN) controller_A_button2 = KEY_UP;
		else controller_A_button2 = KEY_IDLE;
	}
	if (button_state_X2) {
		if (controller_X_button2 == KEY_IDLE) controller_X_button2 = KEY_DOWN;
		else controller_X_button2 = KEY_REPEAT;
	}
	else {
		if (controller_X_button2 == KEY_REPEAT || controller_X_button2 == KEY_DOWN) controller_X_button2 = KEY_UP;
		else controller_X_button2 = KEY_IDLE;
	}

	if (button_state_B2) {
		if (controller_B_button2 == KEY_IDLE) controller_B_button2 = KEY_DOWN;
		else controller_B_button2 = KEY_REPEAT;
	}
	else {
		if (controller_B_button2 == KEY_REPEAT || controller_B_button2 == KEY_DOWN) controller_B_button2 = KEY_UP;
		else controller_B_button2 = KEY_IDLE;
	}

	if (button_state_START2) {
		if (controller_START_button2 == KEY_IDLE) controller_START_button2 = KEY_DOWN;
		else controller_START_button2 = KEY_REPEAT;
	}
	else {
		if (controller_START_button2 == KEY_REPEAT || controller_START_button2 == KEY_DOWN) controller_START_button2 = KEY_UP;
		else controller_START_button2 = KEY_IDLE;
	}

	

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_GameControllerClose(controller);
	controller = nullptr;

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}