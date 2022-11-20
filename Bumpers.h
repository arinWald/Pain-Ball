#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"
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
	Animation* currentAnimationBC1;
	Animation idleBC1;
	Animation OnBC1;
	Animation* currentAnimationBC2;
	Animation idleBC2;
	Animation OnBC2;
	Animation* currentAnimationBC3;
	Animation idleBC3;
	Animation OnBC3;
	Animation* currentAnimationBC4;
	Animation idleBC4;
	Animation OnBC4;
	Animation* currentAnimationSC1;
	Animation idleSC1;
	Animation OnSC1;
	Animation* currentAnimationSC2;
	Animation idleSC2;
	Animation OnSC2;
	Animation* currentAnimationSC3;
	Animation idleSC3;
	Animation OnSC3;



	
};