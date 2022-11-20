#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "Ball.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load textures
	circle = App->textures->Load("Assets/wheel.png");
	box = App->textures->Load("Assets/crate.png");
	bonus_fx = App->audio->LoadFx("Assets/bonus.wav");
	backgroundTexture = App->textures->Load("Assets/pinball.png");
	backgroundTopPlantTexture = App->textures->Load("Assets/BackGroundTopPlant.png");
	

	PhysBody* pbodySC3 = new PhysBody();
	pbodySC3 = App->physics->CreateCircleWithBounciness(73, 241, 5, 1.2f, b2_staticBody);
	pbodySC3->ctype = ColliderType::BUMPSMALLCIRCLE1;


	colliderInicial = App->physics->CreateRectangle(700, 34, 3, 10, b2_staticBody);
	

	u1Sensor = App->physics->CreateRectangleSensor(177, 55, 5, 5);
	u1Sensor->ctype = ColliderType::SENSORU1;
	u2Sensor = App->physics->CreateRectangleSensor(193, 55, 5, 5);
	u2Sensor->ctype = ColliderType::SENSORU2;
	u3Sensor = App->physics->CreateRectangleSensor(210, 55, 5, 5);
	u3Sensor->ctype = ColliderType::SENSORU3;

	d1Sensor = App->physics->CreateRectangleSensor(63, 184, 5, 5);
	d1Sensor->ctype = ColliderType::SENSORD1;
	d2Sensor = App->physics->CreateRectangleSensor(79, 187, 5, 5);
	d2Sensor->ctype = ColliderType::SENSORD2;
	d3Sensor = App->physics->CreateRectangleSensor(98, 196, 5, 5);
	d3Sensor->ctype = ColliderType::SENSORD3;


	salvD1Sensor = App->physics->CreateRectangleSensor(290, 171, 10, 10);
	salvD1Sensor->ctype = ColliderType::SEGON;
	salvD2Sensor = App->physics->CreateRectangleSensor(282, 126, 10, 10);
	salvD2Sensor->ctype = ColliderType::SALVAVIDESCANVI;

	salvD2Sensor = App->physics->CreateRectangleSensor(189, 220, 110, 10);
	salvD2Sensor->ctype = ColliderType::SALVAVIDESCANVI;

	cuadraditoSensor = App->physics->CreateRectangleSensor(262, 145, 10, 10);
	cuadraditoSensor->ctype = ColliderType::CUADRADITO;
	inicialSensor = App->physics->CreateRectangleSensor(215, 35, 10, 10);
	inicialSensor->ctype = ColliderType::INICIAL;
	segonSensor = App->physics->CreateRectangleSensor(152, 187, 15, 15);
	segonSensor->ctype = ColliderType::SEGON;
	segonFSensor = App->physics->CreateRectangleSensor(80, 300, 10, 10);
	segonFSensor->ctype = ColliderType::SEGONF;
	culdesacSensor = App->physics->CreateRectangleSensor(245, 55, 10, 10);
	culdesacSensor->ctype = ColliderType::CULDESAC;

	RSalvaVides = App->physics->CreateRectangleSensor(310, 380, 10, 10);
	RSalvaVides->ctype = ColliderType::SALVAVIDES;

	LSalvaVides = App->physics->CreateRectangleSensor(40, 380, 10, 10);
	LSalvaVides->ctype = ColliderType::SALVAVIDES;

	//tubeSensor = App->physics->CreateRectangleSensor(335, 370, 10, 10);
	//tubeSensor->ctype = ColliderType::TUB;
	tubeSensor2 = App->physics->CreateRectangleSensor(335, 386, 20, 10);
	tubeSensor2->ctype = ColliderType::TUB;

	/*Tpsensor = App->physics->CreateRectangleSensor(270,230, 10, 10);
	Tpsensor->ctype = ColliderType::TP;*/

	App->ball->sensorU1 = false;
	App->ball->sensorU2 = false;
	App->ball->sensorU3 = false;

	App->ball->sensorD1 = false;
	App->ball->sensorD2 = false;
	App->ball->sensorD3 = false;

	primerPis = true;
	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleSceneIntro::OnCollision()
	//lower_ground_sensor->listener = this;

	//Colliders - Bumpers

	//EDGES
	{	
	//Colliders Pista EDGES 1r PIS
	// Pivot 0, 0
	int base[12] = {
		105, 406,
		104, 467,
		287, 470,
		285, 412,
		283, 453,
		109, 453
	};

	// Pivot 0, 0
	int exterior[64] = {
		117, 420,
		119, 394,
		61, 350,
		58, 384,
		32, 381,
		69, 177,
		76, 120,
		78, 100,
		83, 80,
		96, 65,
		85, 50,
		84, 35,
		89, 27,
		101, 20,
		116, 17,
		129, 18,
		139, 25,
		143, 29,
		158, 25,
		179, 22,
		210, 21,
		241, 25,
		271, 39,
		296, 63,
		308, 97,
		314, 143,
		357, 382,
		328, 383,
		304, 383,
		301, 370,
		266, 395,
		267, 418
	};


	// Pivot 0, 0
	int obstacleMig[8] = {
		171, 133,
		174, 122,
		205, 131,
		203, 141
	};

	// Pivot 0, 0
	int obstacleMigDreta[12] = {
		289, 121,
		266, 175,
		270, 211,
		288, 225,
		282, 164,
		298, 148
	};

	// Pivot 0, 0
	int obstacleMigEsquerra[12] = {
		78, 130,
		112, 207,
		106, 251,
		76, 254,
		52, 273,
		70, 130
	};



	// Pivot 0, 0
	int obstacleSuperiorDreta[32] = {
		242, 133,
		250, 118,
		255, 100,
		252, 86,
		240, 69,
		225, 58,
		220, 60,
		218, 47,
		230, 44,
		235, 45,
		228, 56,
		243, 66,
		254, 77,
		264, 92,
		267, 114,
		249, 135
	};

	// Pivot 0, 0
	int obstacleSuperiorEsquerra[26] = {
		96, 92,
		94, 112,
		98, 132,
		114, 160,
		124, 158,
		138, 201,
		123, 152,
		143, 143,
		174, 188,
		143, 141,
		107, 125,
		98, 109,
		101, 92
	};


	// Pivot 0, 0
	int obstacleSuperiorMig[10] = {
		138, 55,
		158, 42,
		166, 47,
		166, 60,
		138, 68
	};


	// Pivot 0, 0
	int rallaFlipperLeft[10] = {
		135, 371,
		65, 317,
		67, 288,
		73, 288,
		70, 318
	};

	// Pivot 0, 0
	int rallaFlipperRight[10] = {
		250, 372,
		301, 335,
		297, 279,
		290, 286,
		296, 335
	};

	// Pivot 0, 0
	int rallesLeft1[6] = {
		70, 186,
		70, 195,
		71, 186
	};

	// Pivot 0, 0
	int rallesLeft2[6] = {
		87, 190,
		87, 198,
		88, 190
	};

	// Pivot 0, 0
	int rallesUp1[6] = {
		183, 48,
		183, 57,
		185, 48
	};

	// Pivot 0, 0
	int rallesUp2[6] = {
		200, 47,
		202, 58,
		202, 47
	};


	// Pivot 0, 0
	int triangleLeft[6] = {
		138, 345,
		112, 281,
		107, 326
	};

	// Pivot 0, 0
	int triangleRight[6] = {
		273, 284,
		277, 327,
		251, 344
	};

	// Pivot 0, 0
	int tubSortida[24] = {
		328, 378,
		292, 102,
		278, 75,
		260, 59,
		250, 49,
		235, 41,
		229, 40,
		249, 50,
		265, 63,
		277, 79,
		287, 107,
		294, 126
	};

	// Pivot 0, 0
	int colliderEspecialLeft[8] = {
		296, 371,
		301, 372,
		276, 139,
		272, 147
	};

	// Pivot 0, 0
	int colliderEspecialRight[8] = {
		326, 378,
		329, 378,
		293, 116,
		290, 117
	};

	// Pivot 0, 0
	int segonPis[74] = {
		131, 191,
		130, 167,
		119, 154,
		111, 150,
		100, 149,
		92, 150,
		86, 154,
		84, 160,
		86, 165,
		103, 177,
		108, 186,
		109, 195,
		100, 220,
		103, 247,
		91, 261,
		87, 291,
		80, 300,
		68, 295,
		68, 266,
		60, 260,
		50, 242,
		58, 210,
		52, 203,
		58, 155,
		80, 134,
		92, 131,
		110, 130,
		123, 133,
		134, 140,
		145, 150,
		154, 160,
		164, 176,
		173, 180,
		180, 171,
		172, 234,
		122, 203,
		132, 195
	};


	// Pivot 0, 0
	int puntetDreta[8] = {
		286, 261,
		285, 250,
		293, 248,
		294, 260
	};


	edges.add(App->physics->CreateChain(0, 0, base, 12));
	edges.add(App->physics->CreateChain(0, 0, exterior, 64));
	edges.add(App->physics->CreateChain(0, 0, obstacleMig, 8));
	edges.add(App->physics->CreateChain(0, 0, obstacleMigEsquerra, 12));
	edges.add(App->physics->CreateChain(0, 0, obstacleMigDreta, 12));
	edges.add(App->physics->CreateChain(0, 0, obstacleSuperiorDreta, 32));
	edges.add(App->physics->CreateChain(0, 0, obstacleSuperiorEsquerra, 26));
	edges.add(App->physics->CreateChain(0, 0, obstacleSuperiorMig, 10));
	edges.add(App->physics->CreateChain(0, 0, rallaFlipperLeft, 10));
	edges.add(App->physics->CreateChain(0, 0, rallaFlipperRight, 10));
	edges.add(App->physics->CreateChain(0, 0, rallesUp1, 6));
	edges.add(App->physics->CreateChain(0, 0, rallesUp2, 6));
	edges.add(App->physics->CreateChain(0, 0, triangleLeft, 6));
	edges.add(App->physics->CreateChain(0, 0, triangleRight, 6));
	edges.add(App->physics->CreateChain(0, 0, tubSortida, 24));
	edges.add(App->physics->CreateChain(0, 0, puntetDreta, 8));

	edges.add(App->physics->CreateChain(0 - 600, 0, colliderEspecialLeft, 8));
	edges.add(App->physics->CreateChain(0 - 600, 0, colliderEspecialRight, 8));
	edges.add(App->physics->CreateChain(0 - 600, 0, segonPis, 72));
	edges.add(App->physics->CreateChain(0 - 600, 0, rallesLeft1, 6));
	edges.add(App->physics->CreateChain(0 - 600, 0, rallesLeft2, 6));
	}
	
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

update_status ModuleSceneIntro::Update()
{
	// If user presses SPACE, enable RayCast
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// Enable raycast mode
		ray_on = !ray_on;

		// Origin point of the raycast is be the mouse current position now (will not change)
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	// If user presses 1, create a new circle object
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7));

		// Add this module (ModuleSceneIntro) as a "listener" interested in collisions with circles.
		// If Box2D detects a collision with this last generated circle, it will automatically callback the function ModulePhysics::BeginContact()
		circles.getLast()->data->listener = this;
	}

	// If user presses 2, create a new box object
	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}


	//Alternar pisos edges
	if ((App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN || App->ball->alternPis==true) && primerPis)
	{
		p2List_item<PhysBody*>* item;
		item = edges.getFirst();

		while (item != nullptr)
		{
			item->data->body->SetTransform({ item->data->body->GetTransform().p.x + PIXEL_TO_METERS(600), 0 }, 0);
			item = item->next;
		}
		primerPis = false;
		App->ball->alternPis = false;
	}
	//Posar primer pis
	if ((App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN || App->ball->alternPis == true) && !primerPis)
	{
		p2List_item<PhysBody*>* item;
		item = edges.getFirst();

		while (item != nullptr)
		{
			item->data->body->SetTransform({ item->data->body->GetTransform().p.x - PIXEL_TO_METERS(600), 0 }, 0);
			item = item->next;
		}
		primerPis = true;
		App->ball->alternPis = false;
	}

	

	// Prepare for raycast ------------------------------------------------------
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	// Circles
	p2List_item<PhysBody*>* c = circles.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// If mouse is over this circle, paint the circle's texture
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
		

		c = c->next;
	}

	// Boxes
	c = boxes.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// Always paint boxes texture
		

		// Are we hitting this box with the raycast?
		if(ray_on)
		{
			// Test raycast over the box, return fraction and normal vector
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}



	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	App->renderer->Blit(backgroundTexture, 0, 0, NULL);

	// Keep playing
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding
	App->audio->PlayFx(bonus_fx);

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}

