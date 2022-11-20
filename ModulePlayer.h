#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "p2Point.h"
#include "Kicker.h"
#include "Animation.h"

#include "SDL\include\SDL.h"

struct Flipper
{
	PhysBody* Rect;
	PhysBody* Circle;
	bool rightSide;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	SDL_Texture* playerText;
	Animation* currentAnimation;
	Animation* rightflipperAnimation;
	Animation* leftflipperAnimation;

	PhysBody* ball;
	SDL_Rect ballSect;
	bool onceInit = true;
	bool isDead = false;

	


	p2List<Flipper*> flippers;
	SDL_Rect rectSect;

	//Kicker

	int ballPushForce;
	int cargablack;
	int flippersFxId;

	SDL_Texture* barraCarga;

	uint clickFx;
	uint kickerFx;

	bool onceBall = true;
	//int currentScore = 0;
	int previousScore;
	int highScore;

	int ballCounter;

	// puntuacion del player
	uint currentScore;
	uint previouScore;
	uint highestScore;

};