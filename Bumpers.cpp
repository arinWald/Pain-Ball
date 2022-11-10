#include "Globals.h"
#include "Application.h"
#include "Bumpers.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "SDL\include\SDL.h"
#include <iostream>

Bumpers::Bumpers(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Bumpers::~Bumpers()
{}

// Load assets
bool Bumpers::Start()
{
	//Bumpers - Big Circles
	PhysBody* pbodyBC1;
	pbodyBC1 = App->physics->CreateCircle(112, 43, 10, b2_staticBody);
	PhysBody* pbodyBC2;
	pbodyBC2 = App->physics->CreateCircle(215, 90, 10, b2_staticBody);
	PhysBody* pbodyBC3;
	pbodyBC3 = App->physics->CreateCircle(191, 123, 10, b2_staticBody);
	PhysBody* pbodyBC4;
	pbodyBC4 = App->physics->CreateCircle(173, 96, 10, b2_staticBody);

	//Bumpers - Small Circles
	PhysBody* pbodySC1;
	pbodySC1 = App->physics->CreateCircle(63, 217, 8, b2_staticBody);
	PhysBody* pbodySC2;
	pbodySC2 = App->physics->CreateCircle(95, 227, 8, b2_staticBody);
	PhysBody* pbodySC3;
	pbodySC3 = App->physics->CreateCircle(73, 241, 8, b2_staticBody);


	//Bumpers - Triangles
	PhysBody* pbodyT1;
	pbodyT1 = App->physics->CreateCircle(250, 150, 9, b2_staticBody);



	BumperElement bigCircle1{ "bigCircle1", pbodyBC1 };
	bumpersList.add(&bigCircle1);


	return true;
}

// Unload assets
bool Bumpers::CleanUp()
{
	LOG("Unloading Ball");
	bumpersList.clear();
	return true;
}

// Update: draw background
update_status Bumpers::Update()
{




	return UPDATE_CONTINUE;
}



