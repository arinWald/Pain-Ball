#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class Kicker : public Module
{
public:
	Kicker(Application* app, bool start_enabled = true);
	virtual ~Kicker();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	PhysBody* pivot;
	PhysBody* mobile;

	SDL_Rect kickerSect = { 302,706,22,96 };
	SDL_Rect kickerSectBonus = { 1002,706,22,96 };

	uint kickerFx;
};