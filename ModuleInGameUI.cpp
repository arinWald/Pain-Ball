#include "ModuleInGameUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"

#include <stdio.h>



ModuleInGameUI::ModuleInGameUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	

}

ModuleInGameUI::~ModuleInGameUI()
{

}

// Load assets
bool ModuleInGameUI::Start()
{


	return true;
}

update_status ModuleInGameUI::Update()
{
	

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInGameUI::PostUpdate()
{


	return UPDATE_CONTINUE;
}



bool ModuleInGameUI::CleanUp()
{


	return true;
}

