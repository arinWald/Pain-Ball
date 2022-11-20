#include "Globals.h"
#include "Application.h"
#include "Ball.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "Bumpers.h"
#include "SDL\include\SDL.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include <iostream>
using namespace std;

Ball::Ball(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Ball::~Ball()
{}

// Load assets
bool Ball::Start()
{

	ball = App->physics->CreateCircle(334, 352, 7, b2_dynamicBody);
	ball->body->GetFixtureList()->SetDensity(1.0f);
	ball->body->GetFixtureList()->SetFriction(0.2f);
	ball->body->SetGravityScale(0.5f);
	ball->body->ResetMassData();

	//App->physics->CreateRectangle(300, 416, 600, 50, b2_staticBody);

	/*ball->body->SetGravityScale(2.0f);*/

	teleport.turn = false;
	ballReset = false;
	
	ball->listener = this;
	ball->ctype = ColliderType::BALL;
	bumpersFxId = App->audio->LoadFx("Assets/SFX/bumper.wav");
	

	LOG("Loading Ball");
	return true;
}

// Unload assets
bool Ball::CleanUp()
{
	LOG("Unloading Ball");

	return true;
}

void Ball::ChangePosition(int x, int y)
{

	teleport.posX = x;
	teleport.posY = y;
	teleport.turn = true;

}

// Update: draw background
update_status Ball::Update()
{

	if (App->ball->BC1Timer > 0) {
		BC1Timer--;
	}
	if (App->ball->BC2Timer > 0) {
		BC2Timer--;
	}
	if (App->ball->BC3Timer > 0) {
		BC3Timer--;
	}
	if (App->ball->BC4Timer > 0) {
		BC4Timer--;
	}
	if (App->ball->SC1Timer > 0) {
		SC1Timer--;
	}
	if (App->ball->SC2Timer > 0) {
		SC2Timer--;
	}
	if (App->ball->SC3Timer > 0) {
		SC3Timer--;
	}
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		ball = nullptr;
		ball = App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 7, b2_dynamicBody);
		ball->body->GetFixtureList()->SetDensity(10.0f);
		ball->body->ResetMassData();
	}

	std::cout << "Mouse X - " << App->input->GetMouseX() << std::endl;
	std::cout << "Mouse Y - " << App->input->GetMouseY() << std::endl;
	//cout << ball->body->GetMass() << endl;  

	//Aumentar la friccion de la ball
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		//std::cout <<"actual " << ball->body->GetFixtureList()->GetFriction() << std::endl;
		float32 actualFriction = ball->body->GetFixtureList()->GetFriction();
		ball->body->GetFixtureList()->SetFriction(actualFriction + 1.0f);
		//std::cout << "cambiada " << ball->body->GetFixtureList()->GetFriction() << std::endl;
	}
	
	//Disminuir la friccion de la ball
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		float32 actualFriction = ball->body->GetFixtureList()->GetFriction();
		ball->body->GetFixtureList()->SetFriction(actualFriction - 1.0f);
	}


	b2Vec2 ballPosition = ball->body->GetPosition();
	int ballPositionYInPixels = METERS_TO_PIXELS(ballPosition.y);
	
	//Resetear la ball y disminuir una ball (de las 3 posibles que puede jugar el player en una partida) si la pelota cae al vac�o
	if (ballPositionYInPixels > 410 && !ballReset) 
	{
		App->player->ballCounter--;
		ballReset = true;
	}

	
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN || ballReset)
	{
		ChangePosition(334, 352);
	}
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		ChangePosition(App->input->GetMouseX(), App->input->GetMouseY());
	}

	if (teleport.turn == true)
	{
		b2Vec2 resetPos = b2Vec2(PIXEL_TO_METERS(teleport.posX), PIXEL_TO_METERS(teleport.posY));
		ball->body->SetTransform(resetPos, 0);
		teleport.turn = false;
		ballReset = false;
	}


	//SALVA VIDES LEFT I RIGHT
	if (salvaVidesOn)
	{
		if (stoppedTimer < 100)
		{
			++stoppedTimer;
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetGravityScale(0.0f);
		}
		else if (stoppedTimer == 100)
		{
			ball->body->SetGravityScale(1.0f);
			ball->body->ApplyForceToCenter(b2Vec2(0, -50), true);
			stoppedTimer = 0;
			salvaVidesOn = false;
		}
	}

	

	

	
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(App->player->ballText, x, y, NULL);

		App->renderer->Blit(App->scene_intro->backgroundTopPlantTexture, 30, 5, NULL);
		
	

	//cout << stoppedTimer << endl;
	

	return UPDATE_CONTINUE;
}

void Ball::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->ctype)
	{
	case(ColliderType::BUMPSMALLCIRCLE1):

		App->player->currentScore += 150;
		App->bumpers->currentAnimationSC1 = &App->bumpers->OnSC1;
		SC1Timer = 10;
		App->audio->PlayFx(bumpersFxId);

		break;
	case(ColliderType::BUMPSMALLCIRCLE2):

		App->player->currentScore += 150;
		App->bumpers->currentAnimationSC2 = &App->bumpers->OnSC2;
		SC2Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;
	case(ColliderType::BUMPSMALLCIRCLE3):

		App->player->currentScore += 150;
		App->bumpers->currentAnimationSC3 = &App->bumpers->OnSC3;
		SC3Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;

	case(ColliderType::BUMPBIGCIRCLE1):
		App->player->currentScore += 100;
		App->bumpers->currentAnimationBC1 = &App->bumpers->OnBC1;
		BC1Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;
	case(ColliderType::BUMPBIGCIRCLE2):
		App->player->currentScore += 100;
		App->bumpers->currentAnimationBC2 = &App->bumpers->OnBC2;
		BC2Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;
	case(ColliderType::BUMPBIGCIRCLE3):
		App->player->currentScore += 100;
		App->bumpers->currentAnimationBC3 = &App->bumpers->OnBC3;
		BC3Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;
	case(ColliderType::BUMPBIGCIRCLE4):
		App->player->currentScore += 100;
		App->bumpers->currentAnimationBC4 = &App->bumpers->OnBC4;
		BC4Timer = 10;
		App->audio->PlayFx(bumpersFxId);
		break;

	case(ColliderType::TRIANGLE):
		App->player->currentScore += 50;
		App->audio->PlayFx(bumpersFxId);
		break;
	case(ColliderType::SALVAVIDES):
		salvaVidesOn = true;
		break;

	case(ColliderType::TUB):
		bolaATub = true;
		break;

	default:
		break;
	}
}


