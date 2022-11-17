#include "GameManager.h"
#include "Application.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"

GameManager::GameManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

GameManager::~GameManager()
{}

bool GameManager::Start()
{

	gameState = START;
	return true;
}

update_status GameManager::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && (gameState == START || gameState == END))
	{
		gameState = PLAYING;
	}


	return UPDATE_CONTINUE;
}