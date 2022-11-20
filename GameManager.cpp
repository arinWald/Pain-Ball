#include "GameManager.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "ModulePlayer.h"
#include "Ball.h"

GameManager::GameManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

GameManager::~GameManager()
{}

bool GameManager::Start()
{

	gameState = START;
	loseFxId = App->audio->LoadFx("Assets/SFX/youLose.wav");
	return true;
}

update_status GameManager::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (gameState == START)
		{
			gameState = PLAYING;
			App->ball->enabled = true;
			App->ball->Start();
			App->player->ballCounter = 3;
			App->player->currentScore = 0;
		}
		else if (gameState == END)
		{
			if (firstGame)
			{
				
				App->player->previouScore = 0;
			}
			else
			{
				App->player->previouScore = App->player->currentScore;
			}
			
			gameState = PLAYING;
			App->player->ballCounter = 3;
			App->player->currentScore = 0;
			
		}
	}

	if(App->player->ballCounter == 0)
	{
		
		gameState = END;

	}

	switch (gameState)
	{
	case(NONE):
		break;

	case(START):
		firstGame = true;
		break;

	case(PLAYING):
	

		break;

	case(END): 
	

		if (App->player->currentScore > App->player->highestScore)
		{
			App->player->highestScore = App->player->currentScore;
		}

		if (firstGame == true)
			firstGame = false;
	
		

		break;

	default:
		break;
	}


	return UPDATE_CONTINUE;
}