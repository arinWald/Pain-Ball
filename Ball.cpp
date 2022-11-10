#include "Globals.h"
#include "Application.h"
#include "Ball.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include <iostream>

Ball::Ball(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{
	//*ball.get() = App->physics->CreateCircle(303, 767, 10, b2_dynamicBody);
	ball= App->physics->CreateCircle(194, 263, 7, b2_dynamicBody);
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
	std::cout << "Mouse X - " << App->input->GetMouseX() << std::endl;
	std::cout << "Mouse Y - " << App->input->GetMouseY() << std::endl;
	
	return UPDATE_CONTINUE;
}



