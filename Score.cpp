#include "Globals.h"
#include "Application.h"
#include "Score.h"

Score::Score(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Score::~Score()
{}

// Load assets
bool Score::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool Score::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Score::Update()
{
	return UPDATE_CONTINUE;
}



