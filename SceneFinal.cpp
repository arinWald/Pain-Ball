#include "Globals.h"
#include "Application.h"
#include "SceneFinal.h"

SceneFinal::SceneFinal(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

SceneFinal::~SceneFinal()
{}

// Load assets
bool SceneFinal::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool SceneFinal::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status SceneFinal::Update()
{
	return UPDATE_CONTINUE;
}



