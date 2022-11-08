#include "Globals.h"
#include "Application.h"
#include "Timer.h"

Timer::Timer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Timer::~Timer()
{}

// Load assets
bool Timer::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool Timer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Timer::Update()
{
	return UPDATE_CONTINUE;
}



