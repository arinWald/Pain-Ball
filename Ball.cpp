#include "Globals.h"
#include "Application.h"
#include "Ball.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "GameManager.h"
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

	inicial = b2Vec2(PIXEL_TO_METERS(224), PIXEL_TO_METERS(34));
	final = b2Vec2(PIXEL_TO_METERS(700), PIXEL_TO_METERS(34));
	teleport.turn = false;
	ballReset = false;
	colliderInicial = false;
	audioCarrega = true;

	
	ball->listener = this;
	ball->ctype = ColliderType::BALL;
	bumpersFxId = App->audio->LoadFx("Assets/SFX/bumper.wav");
	loseBallFxId = App->audio->LoadFx("Assets/SFX/BolaEsPerd.wav");
	ExtraballFxId = App->audio->LoadFx("Assets/SFX/ExtraBall.wav");
	SalvaVidasFxId = App->audio->LoadFx("Assets/SFX/SalvaVida.wav");
	BoletaEncesaId = App->audio->LoadFx("Assets/SFX/BoletaEncesa.wav");
	kickerDisparaFxId = App->audio->LoadFx("Assets/SFX/kickerDispara.wav");
	kickerCarregaFxId = App->audio->LoadFx("Assets/SFX/SalvaVida.wav");

	ballText = App->textures->Load("Assets/Ball.png");
	LlumText = App->textures->Load("Assets/LlumBonus.png");

	stoppedTimer = 0;
	salvaVidesOn = false;
	culdesac = false;
	cuadradito = false;
	alternPis = false;
	segonF = false;

	bolaATub = true;
	BC1Timer = 0;
	BC2Timer = 0;
	BC3Timer = 0;
	BC4Timer = 0;
	SC1Timer = 0;
	SC2Timer = 0;
	SC3Timer = 0;



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

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		ball->body->SetGravityScale(0.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		float gravetat = ball->body->GetGravityScale();
		gravetat += 0.2f;
		ball->body->SetGravityScale(gravetat);
	}
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		float gravetat = ball->body->GetGravityScale();
		gravetat -= 0.2f;
		ball->body->SetGravityScale(gravetat);
	}
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		ball->body->SetGravityScale(0.5f);
	}


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
	
	//Resetear la ball y disminuir una ball (de las 3 posibles que puede jugar el player en una partida) si la pelota cae al vacio
	if (ballPositionYInPixels > 410/*415*/ && !ballReset) 
	{
		App->scene_intro->colliderInicial->body->SetTransform(final, 0);
		
		if (App->player->ballCounter ==1) {
			App->audio->PlayFx(App->gameManager->loseFxId);
		}
		else {
			App->audio->PlayFx(loseBallFxId);
		}
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

	//CUL DE SAC
	if (culdesac)
	{
		if (stoppedTimer < 100)
		{
			++stoppedTimer;
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetGravityScale(0.0f);
			if (audioCarrega)
			{
				App->audio->PlayFx(kickerCarregaFxId);
				audioCarrega = false;
			}
		}
		else if (stoppedTimer == 100)
		{
			ball->body->SetGravityScale(0.5f);
			App->audio->PlayFx(kickerDisparaFxId);
			ball->body->ApplyForceToCenter(b2Vec2(0, 300), true);
			stoppedTimer = 0;
			culdesac = false;
			audioCarrega = true;
		}
	}

	//CUADRADITO GIRATORIO
	if (cuadradito)
	{
		if (stoppedTimer < 50)
		{
			++stoppedTimer;
			//animacio cuadradito girando
		}
		else if (stoppedTimer == 50)
		{
			//animacio cuadradito quieto
			stoppedTimer = 0;
			cuadradito = false;
		}
	}

	//SORTDIDA 2N PIS
	if (segonF)
	{
		if (stoppedTimer < 50)
		{
			++stoppedTimer;
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetGravityScale(0.0f);
			
		}
		else if (stoppedTimer == 50)
		{
			
			ball->body->SetGravityScale(0.5f);
			ball->body->ApplyForceToCenter(b2Vec2(0, 5), true);
			stoppedTimer = 0;
			segonF = false;
		}
	}


	//SALVA VIDES LEFT I RIGHT
	if (salvaVidesOn)
	{
		if (stoppedTimer < 100)
		{
			++stoppedTimer;
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetGravityScale(0.0f);
			if (audioCarrega)
			{
				App->audio->PlayFx(kickerCarregaFxId);
				audioCarrega = false;
			}
		}
		else if (stoppedTimer == 100)
		{
			ball->body->SetGravityScale(0.5f);
			ball->body->ApplyForceToCenter(b2Vec2(0, -30), true);
			App->audio->PlayFx(kickerDisparaFxId);
			stoppedTimer = 0;
			salvaVidesOn = false;
			audioCarrega = true;
		}
	}
	
	//Tp ball
	if (Tp) {


		if (stoppedTimer < 100) {

			++stoppedTimer;
			ball->body->SetLinearVelocity({ 0,0 });
			ball->body->SetGravityScale(0.0f);
			b2Vec2 resetPos = b2Vec2(PIXEL_TO_METERS(teleport.posX), PIXEL_TO_METERS(teleport.posY));
			ball->body->SetTransform(resetPos, 0);
		}
		else if (stoppedTimer == 100)
		{
			ball->body->SetGravityScale(0.5f);
			ball->body->ApplyForceToCenter(b2Vec2(5, 5), true);
			stoppedTimer = 0;
			Tp = false;
				b2Vec2 resetPos = b2Vec2(PIXEL_TO_METERS(teleport.posX), PIXEL_TO_METERS(teleport.posY));
			ball->body->SetTransform(resetPos, 0);
		}


	}
	
		int x, y;
		ball->GetPosition(x, y);
		App->renderer->Blit(ballText, x, y, NULL);

		if (alternPis == false) {
			App->renderer->Blit(App->scene_intro->backgroundTopPlantTexture, 30, 5, NULL);
		}
	


	//Combo 3 adalt sumar una bola
	if (sensorU1 && sensorU2 && sensorU3) {
		if (App->player->ballCounter < 9) {
			App->player->ballCounter++;
		}
		sensorU1 = false;
		sensorU2 = false;
		sensorU3 = false;
		App->audio->PlayFx(ExtraballFxId);
		//desactivar animacio puntito amarillo
	}

	//Combo 3 2n pis sumar una bola
	if (sensorD1 && sensorD2 && sensorD3) {
		if (App->player->ballCounter < 9) {
			App->player->ballCounter++;
		}
		sensorD1 = false;
		sensorD2 = false;
		sensorD3 = false;
		App->audio->PlayFx(ExtraballFxId);
		//desactivar animacio puntito amarillo
	}
	
	if (colliderInicial) {
		App->scene_intro->colliderInicial->body->SetTransform(inicial, 0);
		colliderInicial = false;
	}
	
	if (sensorU1 == true) {
		App->renderer->Blit(LlumText, 172, 50, NULL);
	}
	if (sensorU2 == true) {
		App->renderer->Blit(LlumText, 189, 48, NULL);
	}
	if (sensorU3 == true) {
		App->renderer->Blit(LlumText, 205, 50, NULL);
	}
	if (sensorD1 == true) {
		App->renderer->Blit(LlumText, 65, 182, NULL);
	}
	if (sensorD2 == true) {
		App->renderer->Blit(LlumText, 79, 185, NULL);
	}
	if (sensorD3 == true) {
		App->renderer->Blit(LlumText, 94, 189, NULL);
	}


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
		App->audio->PlayFx(SalvaVidasFxId);
		break;

	case(ColliderType::TUB):
		bolaATub = true;
		break;

	case(ColliderType::INICIAL):
		colliderInicial = true;
		break;

	case(ColliderType::SEGON):
		App->scene_intro->veureSensor = true;
		alternPis = true;
		break;

	case(ColliderType::SEGONF):
		if (App->scene_intro->primerPis == false) {
			alternPis = true;
			segonF = true;
		}
		break;

	case(ColliderType::SALVAVIDESCANVI):
		if (App->scene_intro->primerPis == false) {
			alternPis = true;
		}
		break;

	case(ColliderType::CULDESAC):
		culdesac = true;
		break;

	case(ColliderType::CUADRADITO):
		cuadradito = true;
		break;

	//Sensor combo de 3 de adalt
	case(ColliderType::SENSORU1):
		if (sensorU1 != true) {
			sensorU1 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;

	case(ColliderType::SENSORU2):
		if (sensorU2 != true) {
			sensorU2 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;

	case(ColliderType::SENSORU3):
		if (sensorU3 != true) {
			sensorU3 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;

	//Sensors combo de 3 2n pis
	case(ColliderType::SENSORD1):
		if (sensorD1 != true) {
			sensorD1 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;

	case(ColliderType::SENSORD2):
		if (sensorD2 != true) {
			sensorD2 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;

	case(ColliderType::SENSORD3):
		if (sensorD3 != true) {
			sensorD3 = true;
			App->audio->PlayFx(BoletaEncesaId);
			//falta animacio puntito amarillo
		}
		break;
	case(ColliderType::TP):

			Tp = true;
			break;

	default:
		break;
	}
}


