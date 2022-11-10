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
	pbodyBC1 = App->physics->CreateCircleWithBounciness(112, 43, 10, 0.9f, b2_staticBody);
	PhysBody* pbodyBC2;
	pbodyBC2 = App->physics->CreateCircleWithBounciness(215, 90, 10, 0.9f, b2_staticBody);
	PhysBody* pbodyBC3;
	pbodyBC3 = App->physics->CreateCircleWithBounciness(191, 123, 10, 0.9f, b2_staticBody);
	PhysBody* pbodyBC4;
	pbodyBC4 = App->physics->CreateCircleWithBounciness(173, 96, 10, 0.9f, b2_staticBody);

	BumperElement bigCircle1{ "bigCircle1", pbodyBC1 };
	bumpersList.add(&bigCircle1);
	BumperElement bigCircle2{ "bigCircle2", pbodyBC2 };
	bumpersList.add(&bigCircle2);
	BumperElement bigCircle3{ "bigCircle3", pbodyBC3 };
	bumpersList.add(&bigCircle3);
	BumperElement bigCircle4{ "bigCircle4", pbodyBC4 };
	bumpersList.add(&bigCircle4);

	//Bumpers - Small Circles
	PhysBody* pbodySC1;
	pbodySC1 = App->physics->CreateCircleWithBounciness(63, 217, 8, 0.9f, b2_staticBody);
	PhysBody* pbodySC2;
	pbodySC2 = App->physics->CreateCircleWithBounciness(95, 227, 8, 0.9f, b2_staticBody);
	PhysBody* pbodySC3;
	pbodySC3 = App->physics->CreateCircleWithBounciness(73, 241, 8, 0.9f, b2_staticBody);

	BumperElement smallCircle1{ "smallCircle1", pbodySC1 };
	bumpersList.add(&smallCircle1);
	BumperElement smallCircle2{ "smallCircle2", pbodySC2 };
	bumpersList.add(&smallCircle2);
	BumperElement smallCircle3{ "smallCircle3", pbodySC3 };
	bumpersList.add(&smallCircle3);

	//Bumpers - Triangles
	PhysBody* pbodyT1;
	pbodyT1 = App->physics->CreateRectangleWithBounciness(260, 310, 3, 63, 0.9F, 9.75f, b2_staticBody);
	PhysBody* pbodyT2;
	pbodyT2 = App->physics->CreateRectangleWithBounciness(126, 310, 3, 63, 0.9F, -9.75f, b2_staticBody);

	BumperElement triangleDret{ "triangleDret", pbodyT1 };
	bumpersList.add(&triangleDret);
	BumperElement triangleEsquerre{ "triangleEsquerre", pbodyT2 };
	bumpersList.add(&triangleEsquerre);
	
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



