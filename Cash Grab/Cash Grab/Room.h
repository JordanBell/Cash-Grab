#pragma once
#include "XY.h"
#include "GameObject.h"
#include "Game.h"
#define SHEET_WIDTH 27
#define SHEET_HEIGHT 4

class Room : public GameObject
{
public:
	~Room(void)
	{
		for (int i = 0; i < SHEET_WIDTH; i++)
			for (int j = 0; j < SHEET_HEIGHT; j++)
				delete tiles[i][j];
	}

	virtual void Render(void) override = 0;

	// Get a rectangle of this room's position and size
	SDL_Rect GetRect(void) { SDL_Rect r = {(Sint16)x, (Sint16)y, (Uint16)m_Size.x, (Uint16)m_Size.y}; return r; }

	// Return a pointer to the room that the player is in
	static Room* GetPlayerRoom(void);

protected:
	// The element tile palette of this room
	enum RoomElement {
		NORMAL, ICE, FIRE
	} m_BaseE;

	Room(const int x, const int y, const Dimensions& size, const RoomElement element, const int renderPriority);

	// Spritesheet Rects for rooms
	SDL_Rect* tiles[SHEET_WIDTH][SHEET_HEIGHT];
	
private:
	Dimensions m_Size;
	static std::vector<Room*> s_Rooms;
};
	