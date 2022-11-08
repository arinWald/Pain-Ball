#include "Globals.h"
#include "Application.h"
#include "SceneInicio.h"

SceneInicio::SceneInicio(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

SceneInicio::~SceneInicio()
{}

// Load assets
bool SceneInicio::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool SceneInicio::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status SceneInicio::Update()
{
	return UPDATE_CONTINUE;
}



