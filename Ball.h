#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Animation.h"
#include "SDL\include\SDL.h"



struct transformPosition {
	float posX;
	float posY;
	bool turn;

};

class Ball : public Module
{
public:
	Ball(Application* app, bool start_enabled = false);
	virtual ~Ball();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ChangePosition(int x, int y);

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	
	PhysBody* ball;
	
	bool ballReset;

	bool sensorU1;
	bool sensorU2;
	bool sensorU3;

	bool sensorD1;
	bool sensorD2;
	bool sensorD3;

	bool colliderInicial;
	b2Vec2 inicial;
	b2Vec2 final;


	//p2DynArray<PhysBody*> ballsContainer;
	SDL_Texture* ballText;
	SDL_Texture* LlumText;

	int bumpersFxId;
	int loseBallFxId;
	int ExtraballFxId;
	int SalvaVidasFxId;
	int kickerDisparaFxId;
	int kickerCarregaFxId;
	int BoletaEncesaId;

	transformPosition teleport;
	bool Tp;
	int stoppedTimer = 0;
	bool bolaATub = true;
	int BC1Timer = 0;
	int BC2Timer = 0;
	int BC3Timer = 0;
	int BC4Timer = 0;
	int SC1Timer = 0;
	int SC2Timer = 0;
	int SC3Timer = 0;
	bool salvaVidesOn;
	bool culdesac;
	bool cuadradito;
	bool alternPis;
	bool segonF;

	bool audioCarrega;


};