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
	ball = App->physics->CreateCircle(334, 352, 7, b2_dynamicBody);
	ball->body->GetFixtureList()->SetDensity(10.0f);
	ball->body->GetFixtureList()->SetFriction(0.2f);
	ball->body->ResetMassData();

	//App->physics->CreateRectangle(300, 416, 600, 50, b2_staticBody);

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
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		ball = nullptr;
		ball = App->physics->CreateCircle(334, 352, 7, b2_dynamicBody);
		ball->body->GetFixtureList()->SetDensity(10.0f);
		ball->body->ResetMassData();
	}

	std::cout << "Mouse X - " << App->input->GetMouseX() << std::endl;
	std::cout << "Mouse Y - " << App->input->GetMouseY() << std::endl;
	cout << ball->body->GetMass() << endl;
	
	return UPDATE_CONTINUE;
}



