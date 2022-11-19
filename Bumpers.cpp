#include "Globals.h"
#include "Application.h"
#include "Bumpers.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
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
	PhysBody* pbodyBC1 = new PhysBody();
	pbodyBC1 = App->physics->CreateCircleWithBounciness(112, 43, 10, 1.2f, b2_staticBody);
	pbodyBC1->ctype = ColliderType::BUMPBIGCIRCLE; 

	PhysBody* pbodyBC2 = new PhysBody(); 
	pbodyBC2 = App->physics->CreateCircleWithBounciness(215, 90, 10, 1.2f, b2_staticBody);
	pbodyBC2->ctype = ColliderType::BUMPBIGCIRCLE;

	PhysBody* pbodyBC3 = new PhysBody();
	pbodyBC3 = App->physics->CreateCircleWithBounciness(191, 123, 10, 1.2f, b2_staticBody);
	pbodyBC3->ctype = ColliderType::BUMPBIGCIRCLE;

	PhysBody* pbodyBC4 = new PhysBody();
	pbodyBC4 = App->physics->CreateCircleWithBounciness(173, 96, 10, 1.2f, b2_staticBody);
	pbodyBC4->ctype = ColliderType::BUMPBIGCIRCLE;


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
	pbodySC1->ctype = ColliderType::BUMPSMALLCIRCLE;

	PhysBody* pbodySC2 = new PhysBody();
	pbodySC2 = App->physics->CreateCircleWithBounciness(95, 227, 5, 1.2f, b2_staticBody);
	pbodySC2->ctype = ColliderType::BUMPSMALLCIRCLE;

	PhysBody* pbodySC3 = new PhysBody();
	pbodySC3 = App->physics->CreateCircleWithBounciness(73, 241, 5, 1.2f, b2_staticBody);
	pbodySC3->ctype = ColliderType::BUMPSMALLCIRCLE;


	BumperElement* smallCircle1 = new BumperElement{ "smallCircle1", pbodySC1 };
	bumpersList.add(smallCircle1);
	BumperElement* smallCircle2 = new BumperElement{ "smallCircle2", pbodySC2 };
	bumpersList.add(smallCircle2);
	BumperElement* smallCircle3 = new BumperElement{ "smallCircle3", pbodySC3 };
	bumpersList.add(smallCircle3);



	//Bumpers - Triangles
	PhysBody* pbodyT1 = new PhysBody();
	pbodyT1 = App->physics->CreateRectangleWithBounciness(260, 310, 3, 63, 2.0f, 9.75f, b2_staticBody);
	pbodyT1->ctype = ColliderType::TRIANGLE;

	PhysBody* pbodyT2 = new PhysBody();
	pbodyT2 = App->physics->CreateRectangleWithBounciness(126, 310, 3, 63, 2.0f, -9.75f, b2_staticBody);
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



	while (iterador != NULL)
	{
		int x, y;
		
		if (iterador->data->name == ("bigCircle1")) {

			App->renderer->Blit(App->player->BCtextures, 112, 43, NULL);


		}
		iterador = iterador->next;
	}


	return UPDATE_CONTINUE;
}


