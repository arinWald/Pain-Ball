#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class Score : public Module
{
public:
	Score(Application* app, bool start_enabled = true);
	virtual ~Score();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};