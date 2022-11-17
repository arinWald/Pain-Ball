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
	SDL_Rect ballSect = { 127, 317, 19, 21 };
	bool onceInit = true;
	bool isDead = false;

	p2List<Flipper*> flippers;
	SDL_Rect rectSect = { 48, 250, 64, 20 };

	//Kicker
	//SDL_Rect kickerSect = { 302,706,22,96 };
	//SDL_Rect kickerSectBonus = { 1002,706,22,96 };

	uint clickFx;
	uint kickerFx;

	bool onceBall = true;
	int currentScore = 0;
	int previousScore;
	int highScore = 0;

	int ballCounter = 3;

	// puntuacion del player
	uint score = 000;

};