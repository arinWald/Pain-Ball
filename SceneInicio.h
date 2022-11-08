#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class SceneInicio : public Module
{
public:
	SceneInicio(Application* app, bool start_enabled = true);
	virtual ~SceneInicio();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};