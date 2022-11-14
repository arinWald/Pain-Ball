#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "Ball.h"
#include <iostream>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer
	circle = box = rick = NULL;
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
	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	backgroundTexture = App->textures->Load("Assets/pinball.png");

	// Create a big red sensor on the bottom of the screen.
	// This sensor will not make other objects collide with it, but it can tell if it is "colliding" with something else
	//lower_ground_sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	// In ModulePhysics::PreUpdate(), we iterate over all sensors and (if colliding) we call the function ModuleSceneIntro::OnCollision()
	//lower_ground_sensor->listener = this;


	//Colliders - Bumpers

	//Colliders Pista EDGES
	//
			// Pivot 0, 0
	{int pinball[96] = {
		374, 417,
		303, 0,
		81, 0,
		12, 416,
		118, 415,
		119, 395,
		61, 349,
		56, 382,
		33, 381,
		49, 277,
		67, 256,
		107, 252,
		109, 207,
		86, 156,
		75, 127,
		76, 96,
		91, 68,
		95, 64,
		99, 60,
		87, 52,
		85, 39,
		88, 29,
		98, 21,
		110, 18,
		131, 18,
		145, 26,
		159, 23,
		181, 20,
		207, 21,
		240, 26,
		262, 35,
		279, 48,
		299, 67,
		307, 95,
		321, 178,
		351, 358,
		358, 408,
		333, 408,
		326, 356,
		303, 170,
		298, 173,
		324, 384,
		307, 384,
		302, 375,
		302, 369,
		267, 395,
		269, 425,
		373, 419
	};

	// Pivot 0, 0
	int pinball2[62] = {
		285, 225,
		284, 214,
		268, 211,
		266, 173,
		284, 130,
		287, 108,
		282, 88,
		268, 67,
		241, 47,
		227, 52,
		235, 62,
		251, 75,
		259, 84,
		262, 99,
		262, 122,
		248, 136,
		241, 133,
		253, 106,
		253, 89,
		236, 66,
		222, 58,
		220, 47,
		231, 41,
		251, 48,
		266, 58,
		279, 73,
		292, 99,
		297, 153,
		281, 164,
		289, 227,
		286, 228
	};

	// Pivot 0, 0
	int pinball3[10] = {
		248, 373,
		299, 334,
		296, 283,
		292, 283,
		296, 333
	};

	// Pivot 0, 0
	int pinball4[10] = {
		134, 369,
		67, 318,
		70, 280,
		76, 280,
		73, 320
	};

	//Pivot 0, 0
	int upLeftPiece[10] = {
		157, 42,
		137, 55,
		140, 70,
		167, 56,
		166, 46
	};

	// Pivot 0, 0
	int leftBounceTriangle[6] = {
		113, 280,
		136, 346,
		108, 327
	};

	// Pivot 0, 0
	int rightBounceTriangle[6] = {
		250, 345,
		272, 281,
		277, 326
	};

	// Pivot 0, 0
	int upLeftLeftPiece[18] = {
		95, 93,
		92, 115,
		97, 135,
		113, 159,
		142, 145,
		139, 139,
		104, 122,
		97, 112,
		98, 93
	};


	ricks.add(App->physics->CreateChain(0, 0, pinball, 92));
	ricks.add(App->physics->CreateChain(0, 0, pinball2, 62));
	ricks.add(App->physics->CreateChain(0, 0, pinball3, 10));
	ricks.add(App->physics->CreateChain(0, 0, pinball4, 10));
	ricks.add(App->physics->CreateChain(0, 0, upLeftPiece, 10));
	ricks.add(App->physics->CreateChain(0, 0, leftBounceTriangle, 6));
	ricks.add(App->physics->CreateChain(0, 0, rightBounceTriangle, 6));
	ricks.add(App->physics->CreateChain(0, 0, upLeftLeftPiece, 18));
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
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());

		c = c->next;
	}

	// Boxes
	c = boxes.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);

		// Always paint boxes texture
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());

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

	// Rick Heads
	c = ricks.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
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
