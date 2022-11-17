#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2DynArray.h"

struct transformPosition {
	float posX;
	float posY;
	bool turn;

};

class Ball : public Module
{
public:
	Ball(Application* app, bool start_enabled = true);
	virtual ~Ball();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ChangePosition(int x, int y);

public:

	PhysBody* ball;

	//p2DynArray<PhysBody*> ballsContainer;

	transformPosition teleport;

};