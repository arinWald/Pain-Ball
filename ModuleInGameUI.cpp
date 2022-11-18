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
	
	//App->fonts->BlitText(440, 208, scoreFont, "0");

	switch (App->gameManager->gameState)
	{
	case(NONE):
		break;

	case(START):
		App->fonts->BlitText(400, 217, alphabetFont, "Press P to");
		App->fonts->BlitText(400, 247, alphabetFont, "play");
		break;

	case(PLAYING)://mostrando la currentpuntuación en real-time
		sprintf_s(scoreText, 10, "%7d", App->player->currentScore);
		App->fonts->BlitText(432, 356, numFont, scoreText);
		break;

	case(END): //Mostrando current, previous y highest score al acabar una partida
		App->fonts->BlitText(400, 217, alphabetFont, "C ");
		sprintf_s(scoreText, 10, "%7d", App->player->currentScore);
		App->fonts->BlitText(432, 217, numFont, scoreText);

		App->fonts->BlitText(400, 247, alphabetFont, "P ");
		sprintf_s(scoreText, 10, "%7d", App->player->previouScore);
		App->fonts->BlitText(432, 247, numFont, scoreText);

		App->fonts->BlitText(400, 277, alphabetFont, "H ");
		sprintf_s(scoreText, 10, "%7d", App->player->highestScore);
		App->fonts->BlitText(432, 277, numFont, scoreText);

		App->fonts->BlitText(400, 356, alphabetFont, "P to play");
		break;

	default:
		break;
	}



	return UPDATE_CONTINUE;
}



bool ModuleInGameUI::CleanUp()
{


	return true;
}

