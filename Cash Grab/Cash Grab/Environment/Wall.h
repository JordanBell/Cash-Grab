#pragma once

#include "Collidable.h"

class Wall : public Collidable, public GameObject {
    
public:
	// Construct using default 32x32 size
    Wall(const int x, const int y);

	// Construct using given dimensions
    Wall(const int x, const int y, const int w, const int h);

	// Render, if set to do so.
	void Render(void);
};
