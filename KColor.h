#ifndef KCOLOR_H
#define KCOLOR_H

#include <SDL.h>

/**
* Holds the value of an RBGA color
*/
struct KColor {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

#endif // !KCOLOR_H
