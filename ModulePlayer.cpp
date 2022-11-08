#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	b2Vec2 a = { -0.44, 0 };
	b2Vec2 b = { 0, 0 };

	// Flippers --------------------------------------------------------------
	Flipper* f = new Flipper;
	f->Circle = App->physics->CreateCircle(140, 374, 4, b2_staticBody);
	f->Rect = App->physics->CreateRectangle(140 + rectSect.w / 2, 374 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f->rightSide = false;
	App->physics->CreateRevoluteJoint(f->Rect, a, f->Circle, b, 35.0f);
	flippers.add(f);

	a = { 0.44,0 };

	Flipper* f2 = new Flipper;
	f2->Circle = App->physics->CreateCircle(245, 374, 4, b2_staticBody);
	f2->Rect = App->physics->CreateRectangle(245 - rectSect.w / 2, 374 + rectSect.h / 2, rectSect.w, rectSect.h - 10, b2_dynamicBody);
	f2->rightSide = true;
	App->physics->CreateRevoluteJoint(f2->Rect, a, f2->Circle, b, 35.0f);
	flippers.add(f2);



	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	// Flippers --------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		p2List_item<Flipper*>* f = flippers.getFirst();
		while (f != NULL)
		{
			if (f->data->rightSide == false)
			{
				f->data->Rect->body->ApplyForce({ -50,0 }, { 0,0 }, true);
			}
			f = f->next;
		}
	}
	//else
	//{
	//	p2List_item<Flipper*>* f = flippers.getFirst();
	//	while (f != NULL)
	//	{
	//		if (f->data->rightSide == false)
	//		{
	//			f->data->Rect->body->ApplyForce({ 5,0 }, { 0,0 }, true);
	//		}
	//		f = f->next;
	//	}
	//}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		p2List_item<Flipper*>* f = flippers.getFirst();
		while (f != NULL)
		{
			if (f->data->rightSide == true)
			{
				f->data->Rect->body->ApplyForce({ 50,0 }, { 0,0 }, true);
			}
			f = f->next;
		}
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(clickFx);
}
