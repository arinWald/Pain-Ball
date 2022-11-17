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

	int ballPushForce = 0;

	uint kickerFx;
};