#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class SceneFinal : public Module
{
public:
	SceneFinal(Application* app, bool start_enabled = true);
	virtual ~SceneFinal();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};