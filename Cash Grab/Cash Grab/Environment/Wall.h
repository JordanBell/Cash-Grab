//
//  Wall.h
//  CashGrab
//
//  Created by Tristan Bell on 20/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __CashGrab__Wall__
#define __CashGrab__Wall__

#include "Collidable.h"

class Wall : public Collidable, public GameObject {
    
public:
    Wall(int x, int y) : Collidable(x, y), GameObject(x, y)
		{ m_IsMoveable = false; m_renderPriority = 99; }

	// Render if set to do so
	void Render(void);
};

#endif /* defined(__CashGrab__Wall__) */
