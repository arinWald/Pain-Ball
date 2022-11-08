#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class SceneGame : public Module
{
public:
	SceneGame(Application* app, bool start_enabled = true);
	virtual ~SceneGame();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};