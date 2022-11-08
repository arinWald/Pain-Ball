#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "Kicker.h"

Kicker::Kicker(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Kicker::~Kicker()
{}

// Load assets
bool Kicker::Start()
{
	LOG("Loading Kicker");

	//kickerFx = App->audio->LoadFx("Game/pinball/audio/fx/Spring.wav");

	//Kicker -----------------------------------------------------------------------------------------
	pivot = App->physics->CreateRectangle(313, 894, 20, 8, b2_staticBody);
	mobile = App->physics->CreateRectangle(304, 794, 22, 8, b2_dynamicBody);
	App->physics->CreatePrismaticJoint(mobile, { 0,0 }, pivot, { 0,0 }, { 0,1 }, 1.9f);

	return true;
}

// Unload assets
bool Kicker::CleanUp()
{
	LOG("Unloading Kicker");

	return true;
}

// Update: draw background
update_status Kicker::Update()
{
	return UPDATE_CONTINUE;
}



