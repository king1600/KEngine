#ifndef KWINDOW_H
#define KWINDOW_H

#include <SDL.h>
#include "KUtils.h"
#include "KRenderer.h"
#include "KAssetManager.h"

/****************************************************/
/* Window that manages most game objects including: */
/*     - Renderer                                   */
/*     - AssetManager                               */
/*     - SDL_Window                                 */
/****************************************************/
class KWindow 
{
public:

	/* Create window, renderer and asset manager with error display */
	KWindow(char *title = "KEngine Window",
		int width = 640, int height = 480,
		int xpos = SDL_WINDOWPOS_CENTERED,
		int ypos = SDL_WINDOWPOS_CENTERED)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_HIDDEN);
		if (window == NULL) {
			KPrintError("Failed to create window: ");
		}
		else {
			renderer = new KRenderer(window);
			if (renderer == NULL)
				KPrintError("Failed to create KRenderer: ");
			assets = new KAssetManager();
		}
	}

	~KWindow() {
		/* Destructor */
	}

	/* Destroy all objects related to window */
	void destroy()
	{
		if (window != NULL) {
			KPrint("[KWindow]", "Window destroyed");
			SDL_DestroyWindow(window);
			if (renderer != NULL) renderer->destroy();
			if (assets != NULL) assets->destroy();
			renderer = NULL;
			assets = NULL;
			window = NULL;
		}
	}

	/* Show window to user */
	void show()
	{
		SDL_ShowWindow(window);
	}

	/* Hide window from user */
	void hide()
	{
		SDL_HideWindow(window);
	}

	/* Minimize window into taskbar */
	void minimize()
	{
		SDL_MinimizeWindow(window);
	}

	/* Maximize window to screen */
	void maximize()
	{
		SDL_MaximizeWindow(window);
	}

	/**
	*	Restore to original size before
	*	maximizing or minimizing
	*/
	void restore()
	{
		SDL_RestoreWindow(window);
	}

	/*	Set the window frames per second 
	*	@param _fps the frames per second to set
	*/
	void setFPS(int _fps) {
		fps = (int)(1000 / _fps);
	}

	/* Wait on set FPS */
	void tick() {
		KDelay(fps);
	}

	/*	Set the window icon 
	*	@param icon the icon surface to set
	*/
	void setIcon(KSurface icon)
	{
		SDL_SetWindowIcon(window, icon);
	}

	/*	Set the window title 
	*	@param _title the title c-string to set
	*/
	void setTitle(char * _title)
	{
		SDL_SetWindowTitle(window, _title);
	}

	/*	Set the width 
	*	@param w the width in pixels of the window
	*	@param h the height in pixels of the window
	*/
	void setSize(int w, int h)
	{
		SDL_SetWindowSize(window, w, h);
	}

	/*	Set the maximum dimensions of the window
	*	@param w the width in pixels of the window
	*	@param h the height in pixels of the window
	*/
	void setMaxiumumSize(int w = -1, int h = -1)
	{
		if (w < 1) w = 1;
		else if (h < 1) h = 1;
		else if (w < 1 && h < 1) return;
		SDL_SetWindowMaximumSize(window, w, h);
	}

	/*	Set the minimum dimensions of the window
	*	@param w the width in pixels of the window
	*	@param h the height in pixels of the window
	*/
	void setMinimumSize(int w = -1, int h = -1)
	{
		if (w < 1) w = 1;
		else if (h < 1) h = 1;
		else if (w < 1 && h < 1) return;
		SDL_SetWindowMinimumSize(window, w, h);
	}

	/*	Set if window is has border or not
	*	@param value has border
	*/
	void setBordered(bool value)
	{
		SDL_bool _value = (value) ? SDL_TRUE : SDL_FALSE;
		SDL_SetWindowBordered(window, _value);
	}

	/*	Set if window is resizable or not
	*	@param value is resizable
	*/
	void setResizable(bool value)
	{
		SDL_bool _value = (value) ? SDL_TRUE : SDL_FALSE;
		SDL_SetWindowResizable(window, _value);
	}

	/*	Set the opacity of the window
	*	@param value ranging from 0.0 to 1.0
	*/
	void setOpacity(float value)
	{
		SDL_SetWindowOpacity(window, value);
	}

	/*	Set how bright the window is
	*	@param value ranging from 0.0 to 1.0
	*/
	void setBrightness(float value)
	{
		SDL_SetWindowBrightness(window, value);
	}

	/*	Set the position of the window
	*	@param x the X position of the screen to set the window
	*	@param y the Y position of the screen to set the window
	*/
	void setPosition(int x = -1, int y = -1)
	{
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		SDL_SetWindowPosition(window, x, y);
	}

	/* Get the current frames per second wait value */
	int getFPS() {
		return (int)(fps * 1000);
	}

	/* Get the internal Renderer */
	KRenderer getRenderer() {
		return (renderer == NULL) ? NULL : (*renderer);
	}

	/* Get the internal asset manager */
	KAssetManager getAssetManager() {
		return *assets;
	}

	/* Get the SDL_Window pointer of the current window */
	SDL_Window* getSDLWindow() {
		return (window == NULL) ? NULL : (window);
	}

private:
	SDL_Window *window = NULL;    // the window to draw and manipulate
	KRenderer *renderer = NULL;   // graphic accelerated renderer
	KAssetManager *assets = NULL; // asset manager
	int fps = 30;                 // the default fps value to wait for
};

#endif // !KWINDOW_H