#ifndef KUTILS_H
#define KUTILS_H

/******************************************/
/* Utils used in other classes and engine */
/******************************************/

#include <iostream>
#include <utility>
#include <SDL.h>

/* Mapping SDL values to K values */
#define K_QUIT SDL_QUIT
#define K_KEYUP SDL_KEYUP
#define K_KEYDOWN SDL_KEYDOWN
#define K_MOUSEMOTION SDL_MOUSEMOTION
#define K_MOUSEDOWN SDL_MOUSEBUTTONDOWN
#define K_MOUSEUP SDL_MOUSEBUTTONUP
#define K_MOUSEWHEEL SDL_MOUSEWHEEL
#define K_TEXTEDIT SDL_TEXTEDITING
#define K_TEXTINPUT SDL_TEXTINPUT
#define K_USEREVENT SDL_USEREVENT
#define K_WINDOWEVENT SDL_WINDOWEVENT

typedef SDL_Rect KRect;
typedef SDL_Event KEvent;
typedef SDL_Texture* KTexture;
typedef SDL_Surface* KSurface;

/*
*	Block for a give amount of milliseconds
*
*	@param ms the amout of milliseconds to block for
*/
void KDelay(long ms)
{
	SDL_Delay(ms);
}

/**
*	Recursive call to "KPrint__()" on all arguments
*	passed by original function "KPrint()"
*/
template <typename T, typename ...Args>
void __KPrint(T && t, Args &&... args)
{
	KPrint__(t);
	__KPrint(std::forward<Args>(args)...);
}

/**
*	Called on each argument in the original
*	"KPrint()" function. Prints out argument
*	to stdout along with a seperated space.
*/
template <typename T>
void KPrint__(T obj)
{
	std::cout << obj << ' ';
}

/**
*	Function called when __KPrint
*	is finished iterating through arguments.
*/
void __KPrint()
{
	std::cout << std::endl;
}

/**
*	Original function to call with
*	as many arguments necessary to 
*	display to stdout seperated by space
*/
template <typename ...Args>
void KPrint(Args &&... args)
{
	__KPrint(std::forward<Args>(args)...);
}

/**
*	Function used to display SDL_Error
*	Messages by internal KEngine objects
*
*	@param err extra message to print before
*				the SDL_Error()
*/
void KPrintError(char *err = "")
{
	KPrint("[KError]", err, SDL_GetError());
}

#endif // !KUTILS_H
