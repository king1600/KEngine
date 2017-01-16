#ifndef KASSETMANAGER_H
#define KASSETMANAGER_H

#include <SDL.h>
#include <map>
#include <vector>
#include <iterator>
#include "KUtils.h"

/**
*	Class to hold on to and manage surfaces & textures.
* 
*	- Reuse image pointers instead of creating new ones
*	- get image pointers by nickname
*	- free image pointers when obj finish using
*/
class KAssetManager {
public:
	KAssetManager()
	{
		/* Constructor */
	}
	~KAssetManager()
	{
		/* Destructor */
	}

	/* Destroy all surfaces and textures */
	void destroy()
	{
		if (destroyed) return;
		auto surfIter = surfaces.begin();
		auto textIter = textures.begin();
		while (surfIter != surfaces.end()) {
			if (surfIter->second != NULL)
				SDL_FreeSurface(surfIter->second);
			surfaces[surfIter->first] = NULL;
			surfIter++;
		}
		while (textIter != textures.end()) {
			if (textIter->second != NULL)
				SDL_DestroyTexture(textIter->second);
			textures[textIter->first] = NULL;
			textIter++;
		}
		destroyed = true;
	}

private:
	std::map<char *, KSurface> surfaces; // map nickname to surface
	std::map<char *, KTexture> textures; // map nickname to texture
	bool destroyed = false;              // check if object has been destroyed
};

#endif // !KASSETMANAGER_H
