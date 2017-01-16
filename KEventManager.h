#ifndef KEVENTMANAGER_H
#define KEVENTMANAGER_H

#include <SDL.h>
#include "KUtils.h"

class KEventManager {
public:
	KEventManager()
	{
		/* constructor */
	}
	~KEventManager()
	{
		/* deconstructor */
	}

	/**
	*	Check if another event is ready to be processed.
	*	(For-loop compatible)
	*
	*	@param currentPos an integer that will be incremented if success
	*	@return 0 if no event available or currentPos + 1 if available
	*/
	int hasNext(int currentPos) {
		return (SDL_PollEvent(&buffer)) ? currentPos + 1 : 0;
	}

	/**
	*	Returns the current event in the SDL_EventQueue.
	*/
	KEvent nextEvent() {
		return buffer;
	}

private:
	KEvent buffer; // the current SDL_Event
};

#endif // !KEVENTMANAGER_H
