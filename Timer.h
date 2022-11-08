#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class Timer : public Module
{
public:
	Timer(Application* app, bool start_enabled = true);
	virtual ~Timer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

};