#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include <memory>
#include <string>

struct BumperElement
{
	std::string name;
	PhysBody* bumper;
};

class Bumpers : public Module
{
public:
	Bumpers(Application* app, bool start_enabled = true);
	virtual ~Bumpers();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	//std::unique_ptr<PhysBody*> ball;
	p2List<BumperElement*> bumpersList;

};