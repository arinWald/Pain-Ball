#include "Globals.h"
#include "Application.h"
#include "SceneGame.h"

SceneGame::SceneGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

SceneGame::~SceneGame()
{}

// Load assets
bool SceneGame::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool SceneGame::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status SceneGame::Update()
{
	return UPDATE_CONTINUE;
}



