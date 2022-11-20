#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "Ball.h"
#include "GameManager.h"

#include "ModuleFonts.h"

#include <iostream>
using namespace std;

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//rightflipperAnimation->PushBack({ 0,0,43,35 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//playerText = App->textures->Load("Game/Assets/SpriteSheet-Flippers.png");

	b2Vec2 a = { -0.44, 0 };
	b2Vec2 b = { 0, 0 };

	ballSect = { 127, 317, 19, 21 };
	rectSect = { 48, 250, 64, 20 };

	ballPushForce = 0;
	cargablack = 50;
	highScore = 0;
	ballCounter = 3;

	currentScore = 000;
	previouScore = 000;
	highestScore = 000;

	// Flippers --------------------------------------------------------------
	Flipper* f = new Flipper;
	f->Circle = App->physics->CreateCircle(140, 377, 4, b2_staticBody);
	f->Rect = App->physics->CreateRectangle(140 + rectSect.w / 2, 374 + rectSect.h / 2, rectSect.w - 20, rectSect.h - 10, b2_dynamicBody);
	f->rightSide = false;
	App->physics->CreateRevoluteJoint(f->Rect, a, f->Circle, b, 35.0f);
	flippers.add(f);

	a = { 0.44,0 };

	Flipper* f2 = new Flipper;
	f2->Circle = App->physics->CreateCircle(245, 377, 4, b2_staticBody);
	f2->Rect = App->physics->CreateRectangle(245 - rectSect.w / 2, 374 + rectSect.h / 2, rectSect.w - 20, rectSect.h - 10, b2_dynamicBody);
	f2->rightSide = true;
	App->physics->CreateRevoluteJoint(f2->Rect, a, f2->Circle, b, 35.0f);
	flippers.add(f2);

	barraCarga = App->textures->Load("Assets/carga.png");
	playerText = App->textures->Load("Assets/Flipper.png");

	kickerChargeFxId = App->audio->LoadFx("Assets/SFX/kickerCarrega.wav");
	kickerThrowFxId = App->audio->LoadFx("Assets/SFX/kickerDispara.wav");

	flippersFxId = App->audio->LoadFx("Assets/SFX/flipperUp.wav");
	pinballMusicPath = ("Assets/Music/music.ogg");

	App->audio->PlayMusic(pinballMusicPath, 0);
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
				f->data->Rect->body->ApplyForce({ -5,0 }, { 0,0 }, true);
				
			}
			f = f->next;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		App->audio->PlayFx(flippersFxId);
		
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		p2List_item<Flipper*>* f = flippers.getFirst();
		while (f != NULL)
		{
			if (f->data->rightSide == true)
			{
				f->data->Rect->body->ApplyForce({ 5,0 }, { 0,0 }, true);
				
			}
			f = f->next;
		}
	}

	
	
	p2List_item<Flipper*>* f = flippers.getFirst();
	while (f != NULL)
	{
		int x, y;
		f->data->Rect->GetPosition(x, y);

		App->renderer->BlitFliper(playerText, x, y - 5, false, NULL, f->data->rightSide, 1.0f, f->data->Rect->GetRotation());

		f = f->next;
	}
	int x, y;

	////Kicker inicial
	if (App->gameManager->gameState == GameState::PLAYING && App->ball->bolaATub)
	{
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			if (ballPushForce < 50) { //max 50 de potència
				ballPushForce += 1;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			App->ball->ball->body->ApplyForceToCenter(b2Vec2(0, -ballPushForce), true);
			ballPushForce = 3; //min 30 de potència
			App->ball->bolaATub = false;
			App->audio->PlayFx(kickerThrowFxId);
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			App->renderer->Blit(barraCarga, 385, 335, NULL);
			App->renderer->DrawQuad({ 385,335,21,cargablack }, 0, 0, 0);
			if (cargablack > 0)
				cargablack -= 1;
		}
		else
		{
			if (cargablack < 50)
				cargablack += 10;
		}
		cout << "BallPushForce " << ballPushForce << endl;
	}
	
		
	

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(clickFx);
}
