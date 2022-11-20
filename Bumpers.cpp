#include "Globals.h"
#include "Application.h"
#include "Bumpers.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL\include\SDL.h"
#include "Ball.h"
#include <iostream>

Bumpers::Bumpers(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	idleBC1.PushBack({ 0,1,22,23 });
	idleBC4.PushBack({ 51,28,23,25 });
	idleBC2.PushBack({ 0,29,23,24 });
	idleBC3.PushBack({ 50,3,24,19 });

	idleSC1.PushBack({ 0,0,20,20 });
	idleSC3.PushBack({ 43,0,21,21 });
	idleSC2.PushBack({ 87,1,20,20 });


	OnBC1.PushBack({ 23,3,22,20 });
	OnBC4.PushBack({ 76,28,23,22 });
	OnBC2.PushBack({ 25,29,23,22 });
	OnBC3.PushBack({ 76,3,24,18 });

	OnSC1.PushBack({ 22,0,19,18 });
	OnSC3.PushBack({ 66,0,19,19 });
	OnSC2.PushBack({ 109,1,19,19 });
}

Bumpers::~Bumpers()
{}

// Load assets
bool Bumpers::Start()
{
	currentAnimationBC1 = &idleBC1;
	currentAnimationBC2 = &idleBC2;
	currentAnimationBC3 = &idleBC3;
	currentAnimationBC4 = &idleBC4;

	currentAnimationSC1 = &idleSC1;
	currentAnimationSC2 = &idleSC2;
	currentAnimationSC3 = &idleSC3;
	//Bumpers - Big Circles
	PhysBody* pbodyBC1 = new PhysBody();
	pbodyBC1 = App->physics->CreateCircleWithBounciness(112, 43, 10, 1.2f, b2_staticBody);
	pbodyBC1->ctype = ColliderType::BUMPBIGCIRCLE1; 

	PhysBody* pbodyBC2 = new PhysBody(); 
	pbodyBC2 = App->physics->CreateCircleWithBounciness(215, 90, 10, 1.2f, b2_staticBody);
	pbodyBC2->ctype = ColliderType::BUMPBIGCIRCLE2;

	PhysBody* pbodyBC3 = new PhysBody();
	pbodyBC3 = App->physics->CreateCircleWithBounciness(191, 123, 10, 1.2f, b2_staticBody);
	pbodyBC3->ctype = ColliderType::BUMPBIGCIRCLE3;

	PhysBody* pbodyBC4 = new PhysBody();
	pbodyBC4 = App->physics->CreateCircleWithBounciness(173, 96, 10, 1.2f, b2_staticBody);
	pbodyBC4->ctype = ColliderType::BUMPBIGCIRCLE4;


	BumperElement* bigCircle1 = new BumperElement{ "bigCircle1", pbodyBC1 };
	bumpersList.add(bigCircle1);
	BumperElement* bigCircle2 = new BumperElement{ "bigCircle2", pbodyBC2 };
	bumpersList.add(bigCircle2);
	BumperElement* bigCircle3 = new BumperElement{ "bigCircle3", pbodyBC3 };
	bumpersList.add(bigCircle3);
	BumperElement* bigCircle4 = new BumperElement{ "bigCircle4", pbodyBC4 };
	bumpersList.add(bigCircle4);



	//Bumpers - Small Circles
	PhysBody* pbodySC1 = new PhysBody();
	pbodySC1 = App->physics->CreateCircleWithBounciness(63, 217, 5, 1.2f, b2_staticBody);
	pbodySC1->ctype = ColliderType::BUMPSMALLCIRCLE1;

	PhysBody* pbodySC2 = new PhysBody();
	pbodySC2 = App->physics->CreateCircleWithBounciness(95, 227, 5, 1.2f, b2_staticBody);
	pbodySC2->ctype = ColliderType::BUMPSMALLCIRCLE2;

	PhysBody* pbodySC3 = new PhysBody();
	pbodySC3 = App->physics->CreateCircleWithBounciness(73, 241, 5, 1.2f, b2_staticBody);
	pbodySC3->ctype = ColliderType::BUMPSMALLCIRCLE3;


	BumperElement* smallCircle1 = new BumperElement{ "smallCircle1", pbodySC1 };
	bumpersList.add(smallCircle1);
	BumperElement* smallCircle2 = new BumperElement{ "smallCircle2", pbodySC2 };
	bumpersList.add(smallCircle2);
	BumperElement* smallCircle3 = new BumperElement{ "smallCircle3", pbodySC3 };
	bumpersList.add(smallCircle3);



	//Bumpers - Triangles
	PhysBody* pbodyT1 = new PhysBody();
	pbodyT1 = App->physics->CreateRectangleWithBounciness(260, 310, 3, 63, 1.4f, 9.75f, b2_staticBody);
	pbodyT1->ctype = ColliderType::TRIANGLE;

	PhysBody* pbodyT2 = new PhysBody();
	pbodyT2 = App->physics->CreateRectangleWithBounciness(126, 310, 3, 63, 1.4f, -9.75f, b2_staticBody);
	pbodyT2->ctype = ColliderType::TRIANGLE;

	BumperElement* triangleDret = new BumperElement{ "triangleDret", pbodyT1 };
	bumpersList.add(triangleDret);
	BumperElement* triangleEsquerre = new BumperElement{ "triangleEsquerre", pbodyT2 };
	bumpersList.add(triangleEsquerre);
	
	//bumpersList.findNode(&smallCircle1);

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
	if (App->ball->BC1Timer == 0) {
		currentAnimationBC1 = &idleBC1;
	}
	if (App->ball->BC2Timer == 0) {
		currentAnimationBC2 = &idleBC2;
	}
	if (App->ball->BC3Timer == 0) {
		currentAnimationBC3 = &idleBC3;
	}
	if (App->ball->BC4Timer == 0) {
		currentAnimationBC4 = &idleBC4;
	}
	if (App->ball->SC1Timer == 0) {
		currentAnimationSC1 = &idleSC1;
	}
	if (App->ball->SC2Timer == 0) {
		currentAnimationSC2 = &idleSC2;
	}
	if (App->ball->SC3Timer == 0) {
		currentAnimationSC3 = &idleSC3;
	}
	currentAnimationBC1->Update();
	currentAnimationBC2->Update();
	currentAnimationBC3->Update();
	currentAnimationBC4->Update();
	currentAnimationSC1->Update();
	currentAnimationSC2->Update();
	currentAnimationSC3->Update();


	//Aumentar el coeficiente de Restitución de los Bumpers
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		p2List_item<BumperElement*>* iterador; 
		iterador = bumpersList.start;

		while (iterador != NULL)
		{
			//std::cout << "actual " << iterador->data->bumper->body->GetFixtureList()->GetRestitution() << std::endl;
			float32 actualRestitution = iterador->data->bumper->body->GetFixtureList()->GetRestitution();
			iterador->data->bumper->body->GetFixtureList()->SetRestitution(actualRestitution + 0.1f);
			
			//std::cout << "cambiado " << iterador->data->bumper->body->GetFixtureList()->GetRestitution() << std::endl;
		
			iterador = iterador->next;
		}
	}

	//Disminuir el coeficiente de Restitución de los Bumpers
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		p2List_item<BumperElement*>* iterador;
		iterador = bumpersList.start;
		

		while (iterador != NULL)
		{
			//std::cout << "actual " << iterador->data->bumper->body->GetFixtureList()->GetRestitution() << std::endl;
			float32 actualRestitution = iterador->data->bumper->body->GetFixtureList()->GetRestitution();
			iterador->data->bumper->body->GetFixtureList()->SetRestitution(actualRestitution - 0.1f);

			//std::cout << "cambiado " << iterador->data->bumper->body->GetFixtureList()->GetRestitution() << std::endl;

			iterador = iterador->next;
		}
	}
	
	p2List_item<BumperElement*>* iterador;
	iterador = bumpersList.start;

	p2List_item<PhysBody*>* c;

	SDL_Rect rectBC1 = currentAnimationBC1->GetCurrentFrame();
	SDL_Rect rectBC2 = currentAnimationBC2->GetCurrentFrame();
	SDL_Rect rectBC3 = currentAnimationBC3->GetCurrentFrame();
	SDL_Rect rectBC4 = currentAnimationBC4->GetCurrentFrame();

	SDL_Rect rectSC1 = currentAnimationSC1->GetCurrentFrame();
	SDL_Rect rectSC2 = currentAnimationSC2->GetCurrentFrame();
	SDL_Rect rectSC3 = currentAnimationSC3->GetCurrentFrame();

	while (iterador != NULL)
	{
		int x, y;
		
		if (iterador->data->name == ("bigCircle1")) {

			App->renderer->Blit(App->player->BCtextures, 100, 32, &rectBC1);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("bigCircle2")) {

			App->renderer->Blit(App->player->BCtextures, 202, 77, &rectBC2);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("bigCircle3")) {

			App->renderer->Blit(App->player->BCtextures, 180, 113, &rectBC3);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("bigCircle4")) {

			App->renderer->Blit(App->player->BCtextures, 162, 85, &rectBC4);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("smallCircle1")) {

			App->renderer->Blit(App->player->SCtextures, 53, 205, &rectSC1);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("smallCircle2")) {

			App->renderer->Blit(App->player->SCtextures, 85, 217, &rectSC2);
			iterador = iterador->next;

		}
		if (iterador->data->name == ("smallCircle3")) {

			App->renderer->Blit(App->player->SCtextures, 60, 231, &rectSC3);
			iterador = iterador->next;

		}
		iterador = iterador->next;
	}


	return UPDATE_CONTINUE;
}