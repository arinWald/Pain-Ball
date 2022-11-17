#pragma once
#include "Module.h"


enum GameState {
	NONE,
	START,
	PLAYING,
	END,
};

class GameManager:public Module {

public:
	GameManager(Application* app, bool start_enabled = true);
	virtual ~GameManager();

	bool Start();
	update_status Update();
public:
	

	int gameState;
};
