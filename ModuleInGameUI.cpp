#include "ModuleInGameUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"

#include <iostream>



ModuleInGameUI::ModuleInGameUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	

}

ModuleInGameUI::~ModuleInGameUI()
{

}

// Load assets
bool ModuleInGameUI::Start()
{
	scoreFont = App->textures->Load("Assets/ScoreFont.png");
	fontPositionX = 430;
	fontPositionY = 240;

	//inicializamos la posicion de cada rectangulo
	r0 = { 0,0,13,19 };
	r0 = { 0,0,5,5 };
	r0 = { 0,0,5,5 };
	r0 = { 0,0,5,5 };
	r0 = { 0,0,5,5 };


	return true;
}

update_status ModuleInGameUI::Update()
{
	

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInGameUI::PostUpdate()
{
	

	App->renderer->Blit(scoreFont, fontPositionX, fontPositionY, &r0);

	return UPDATE_CONTINUE;
}



bool ModuleInGameUI::CleanUp()
{


	return true;
}

