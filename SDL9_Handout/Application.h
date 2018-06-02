#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 25

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleAudio;
class ModuleScore;
class ModuleSceneAir;
class ModuleSceneStart;
class ModuleSceneSelect;
class ModuleSceneIntro;
class ModuleUI;
class ModulePlayer;
class ModulePlayerTwo;
class ModulePlayer3;
class ModulePartner;
class ModulePartner2;
class ModulePartner3;
class ModuleUlti2;
class ModuleUlti3;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleEnemies;
class ModuleFonts;
class ModulePowerup;
class ModuleBosses;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleScore* scene_score;
	ModuleSceneAir* scene_air;
	ModuleSceneStart* scene_start;
	ModuleSceneSelect* scene_select;
	ModuleSceneIntro* scene_intro;
	ModuleCollision* collision;
	ModuleUI* ui;
	ModulePlayer* player;
	ModulePlayerTwo* player2;
	ModulePlayer3* player3;
	ModulePartner* partner;
	ModulePartner2* partner2;
	ModulePartner3* partner3;
	ModuleUlti2* ulti2;
	ModuleUlti3* ulti3;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	ModulePowerup* pu;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__