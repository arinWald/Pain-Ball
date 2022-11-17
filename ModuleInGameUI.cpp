#include "ModuleInGameUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"

#include <iostream>
#include "ModuleFonts.h"
#include "ModulePlayer.h"



ModuleInGameUI::ModuleInGameUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	

}

ModuleInGameUI::~ModuleInGameUI()
{

}

// Load assets
bool ModuleInGameUI::Start()
{
	
	char lookupTable[] = { "0123456789" };
	numFont = App->fonts->Load("Assets/ScoreFont.png", "0123456789",1);

	char lookupTable2[] = { "ABCDEFGHIJLMOPRSTUVWabcdeghijklmnoprstuvwyz " };
	alphabetFont = App->fonts->Load("Assets/TextFont.png", lookupTable2, 1);

	return true;
}

update_status ModuleInGameUI::Update()
{
	

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInGameUI::PostUpdate()
{
	

	sprintf_s(scoreText, 10, "%7d", App->player->score);
	App->fonts->BlitText(58, 248, numFont, scoreText);

	//App->fonts->BlitText(440, 208, scoreFont, "0");
	//App->fonts->BlitText(440, 228, scoreFont, "1");
	//App->fonts->BlitText(440, 248, scoreFont, "2");
	//App->fonts->BlitText(440, 268, scoreFont, "3");
	//App->fonts->BlitText(440, 288, scoreFont, "4");
	//App->fonts->BlitText(440, 308, scoreFont, "5");
	//App->fonts->BlitText(440, 328, scoreFont, "6");
	//App->fonts->BlitText(440, 348, scoreFont, "7");
	//App->fonts->BlitText(440, 368, scoreFont, "8");
	//App->fonts->BlitText(440, 388, scoreFont, "9");

	App->fonts->BlitText(10, 300, alphabetFont, "Matricitas jeje");


	return UPDATE_CONTINUE;
}



bool ModuleInGameUI::CleanUp()
{


	return true;
}

