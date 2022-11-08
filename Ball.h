#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class Ball : public Module
{
public:
	Ball(Application* app, bool start_enabled = true);
	virtual ~Ball();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};