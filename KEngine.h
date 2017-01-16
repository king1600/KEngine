#ifndef KENGINE_H
#define KENGINE_H

/**********************************************/
/* Groups together all modules of the library */
/* and implements other neccesary functions   */
/**********************************************/

#include "KUtils.h"
#include "KWindow.h"
#include "KRenderer.h"
#include "KEventManager.h"
#include "KAssetManager.h"

#include <SDL.h>
#include <csignal>
#include <cstdlib>

// To check if KQuit() has already been called
bool K__exitted__ = false;

/**	
*	Create a new Window with default/optional settings.
*
*	@param title the caption/title of the window to create
*	@param width the width of the window to create
*	@param height the height of the window to create
*	@param xpos the X position of the screen to create the window
*	@param ypos the Y position of the screen to create the window
*/
KWindow KCreateWindow(char *title = "KEngine Window",
	int width = 640, int height = 480,
	int xpos = SDL_WINDOWPOS_CENTERED,
	int ypos = SDL_WINDOWPOS_CENTERED)
{
	KWindow win(title, width, height, xpos, ypos);
	return (win.getSDLWindow() == NULL) ? nullptr : win;
}

/*	Destroy all links to SDL Subsystems
*	@param sig optional signal code on exit
*/
void KQuit(int sig = 0)
{
	if (K__exitted__) return;
	else K__exitted__ = true;
	KPrint("[KEngine]", "Quitting");

	SDL_Quit();
}

/* Initialize all needed libs and objs for KEngine */
void KInit() {
	KPrint("[KEngine]", "Initializing");

	// Initialize SDL libraries
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |
			 SDL_INIT_EVENTS | SDL_INIT_TIMER);

	// register the end event
	std::atexit([]() { KQuit(); });  // on normal exit
	signal(SIGINT, KQuit);           // ^C
	signal(SIGABRT, KQuit);          // abort()
	signal(SIGTERM, KQuit);          // sent by 'kill' command
}

#endif // !KENGINE_H