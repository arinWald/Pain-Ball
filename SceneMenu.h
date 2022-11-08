#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class SceneMenu : public Module
{
public:
	SceneMenu(Application* app, bool start_enabled = true);
	virtual ~SceneMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};