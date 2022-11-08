#include "Globals.h"
#include "Application.h"
#include "Ball.h"

Ball::Ball(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{
	LOG("Loading Ball");
	return true;
}

// Unload assets
bool Ball::CleanUp()
{
	LOG("Unloading Ball");

	return true;
}

// Update: draw background
update_status Ball::Update()
{
	return UPDATE_CONTINUE;
}



