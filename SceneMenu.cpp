#include "Globals.h"
#include "Application.h"
#include "SceneMenu.h"

SceneMenu::SceneMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

SceneMenu::~SceneMenu()
{}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool SceneMenu::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status SceneMenu::Update()
{
	return UPDATE_CONTINUE;
}



