#include "Globals.h"
#include "Application.h"
#include "Ball.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include <iostream>
using namespace std;

Ball::Ball(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{
	ball = App->physics->CreateCircle(194, 263, 7, b2_dynamicBody);
	ball->body->GetFixtureList()->SetDensity(10.0f);

	//App->physics->CreateRectangle(300, 416, 600, 50, b2_staticBody);

	ball->body->ResetMassData();
	/*ball->body->SetGravityScale(2.0f);*/

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
	//std::cout << "Mouse X - " << App->input->GetMouseX() << std::endl;
	//std::cout << "Mouse Y - " << App->input->GetMouseY() << std::endl;
	cout << ball->body->GetMass() << endl;
	
	return UPDATE_CONTINUE;
}



