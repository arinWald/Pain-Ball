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
#include "Ball.h"

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

	ballPushForce = 0;

	////Kicker -----------------------------------------------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (ballPushForce < 100) { //max 100 de potència
			ballPushForce += 1;
			//App->audio->PlayFx(carga_fx);
		}
		else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			App->ball->ball->body->ApplyForceToCenter(b2Vec2(0, -ballPushForce), true);
			ballPushForce = 30; //min 30 de potència
		}
	}
		

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



