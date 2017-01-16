#ifndef KRENDERER_H
#define KRENDERER_H

#include "KColor.h"
#include "KUtils.h"
#include <SDL.h>

/*************************************************************/
/* Object used to draw textures, surfaces, rects, and points */
/* to a window using graphically accelerated rendering.      */
/*************************************************************/
class KRenderer {
public:

	KRenderer(SDL_Window *window)
	{
		// create the SDL renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	~KRenderer()
	{
		/* Deconstructor */
	}

	/* Destroy the SDL renderer */
	void destroy() {
		if (renderer == NULL) return;
		KPrint("[KRenderer]", "Renderer destroyed");
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	/**
	*	Render a texture to the screen cut at given dimensions
	* 
	*	@param text The Texture to cut and render
	*	@param x the X position in the viewport to render the texture
	*	@param y the Y position in the viewport to render the texture
	*	@param w the width size of part of the texture to render
	*	@param h the height size of part of the texture to render
	*/
	void render(KTexture text, int x = 0, int y = 0, int w = -1, int h = -1)
	{
		if (w < 0)
			SDL_QueryTexture(text, NULL, NULL, &w, nullptr);
		else if (h < 0)
			SDL_QueryTexture(text, NULL, NULL, nullptr, &h);
		else if (w < 0 && h < 0)
			SDL_QueryTexture(text, NULL, NULL, &w, &h);
		renderRect.x = x;
		renderRect.y = y;
		renderRect.w = w;
		renderRect.h = h;
		SDL_RenderCopy(renderer, text, NULL, &renderRect);
	}

	/* Draw a rect outline to the window using current renderColor */
	void drawLineRect(KRect rect)
	{
		SDL_RenderDrawRect(renderer, &rect);
	}

	/* Draw a filled in rect to the window using current renderColor */
	void drawFullRect(KRect rect)
	{
		SDL_RenderFillRect(renderer, &rect);
	}

	/* Draw a line to the window using current renderColor */
	void drawLine(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
	{
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}

	/* Clear the renderer of any loaded objects */
	void clear() {
		SDL_RenderClear(renderer);
	}

	/* Display loaded objects to window */
	void display()
	{
		SDL_RenderPresent(renderer);
	}

	/* Set the render color of the renderer for the next object */
	void setRenderColor(KColor color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}

	/* Get the SDL_Renderer pointer */
	SDL_Renderer *getRenderer()
	{
		return renderer;
	}

private:
	SDL_Renderer *renderer = NULL; // the SDL_Renderer used to render to screen
	SDL_Rect renderRect;           // Dummy rect used to draw textures to screen
};

#endif // !KRENDERER_H