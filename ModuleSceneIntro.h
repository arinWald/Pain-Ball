#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include <string>

class PhysBody;



class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	

public:

	// Lists of physics objects
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> edges;

	PhysBody* colliderInicial;
	PhysBody* u1Sensor;
	PhysBody* u2Sensor;
	PhysBody* u3Sensor;
	PhysBody* d1Sensor;
	PhysBody* d2Sensor;
	PhysBody* d3Sensor;
	PhysBody* salvD1Sensor;
	PhysBody* salvD2Sensor;
	PhysBody* cuadraditoSensor;
	PhysBody* inicialSensor;
	PhysBody* segonSensor;
	PhysBody* segonFSensor;
	PhysBody* culdesacSensor;
	PhysBody* RSalvaVides;
	PhysBody* LSalvaVides;

	PhysBody* tubeSensor;
	PhysBody* tubeSensor2;
	PhysBody* Tpsensor;
	
	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	bool sensed;

	// Textures
	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* backgroundTexture = nullptr;
	SDL_Texture* backgroundTopPlantTexture = nullptr;

	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	//Bool per alternar pisos amb tecla 5 o 6
	bool primerPis;
	bool veureSensor;


};
