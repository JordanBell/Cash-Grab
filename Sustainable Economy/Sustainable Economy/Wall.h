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
    Wall(int x, int y, SDL_Surface* sheet, SDL_Rect* clip);
	void Render(void) { GameObject::Render(); }
};

#endif /* defined(__CashGrab__Wall__) */
