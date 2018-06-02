#include "ModuleBosses.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"


ModuleBosses::ModuleBosses()
{
	for (uint i = 0; i <MAX_BOSSES; ++i)
		bosses[i] = nullptr;
}

// Destructor
ModuleBosses::~ModuleBosses()
{
}


bool ModuleBosses::Start()
{
	

	return true;
}

update_status ModuleBosses::PreUpdate()
{
	
	

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleBosses::Update()
{
	

	return UPDATE_CONTINUE;
}

update_status ModuleBosses::PostUpdate()
{
	

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBosses::CleanUp()
{
	LOG("Freeing all bosses");

	for (uint i = 0; i < MAX_BOSSES; ++i)
	{
		if (bosses[i] != nullptr)
		{
			delete bosses[i];
			bosses[i] = nullptr;
		}
	}

	return true;
}

