#include "ModuleInGameUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"


#include "SDL/include/SDL.h"

#include <stdio.h>



ModuleInGameUI::ModuleInGameUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	

}

ModuleInGameUI::~ModuleInGameUI()
{

}

// Load assets
bool ModuleInGameUI::Start()
{
	puntos = 5;
	char lookupTable1[] = { "0123456789 " };
	scoreFont = App->fonts->Load("Assets/ScoreFont.png", lookupTable1, 1);

	return true;
}

update_status ModuleInGameUI::Update()
{
	

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleInGameUI::PostUpdate()
{
	sprintf_s(scoreText, 10, "%2d", puntos);
	for (int i = 0; i < 50; i++)
	{
		App->fonts->BlitText(10+(i*10), 10 + (i * 10), scoreFont, scoreText);
	}
	
	//422x 256y
	return UPDATE_CONTINUE;
}



bool ModuleInGameUI::CleanUp()
{
	App->fonts->UnLoad(scoreFont);

	return true;
}

