
#ifndef __MODULE_IN_GAME_UI_H__
#define __MODULE_IN_GAME_UI_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleInGameUI : public Module
{
public:
	//Constructor
	ModuleInGameUI(Application* app, bool start_enabled = true);

	//Destructor
	~ModuleInGameUI();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	// Disables the ui
	bool CleanUp();

public:
	
	int puntos;
	int scoreFont;
	char scoreText[10] = { "\0" };

};

#endif