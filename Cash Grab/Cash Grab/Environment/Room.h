#pragma once
#include "XY.h"
#include "GameObject.h"
#include "Game.h"
#include "Machine.h"

#define FRICTION_DEFAULT 0.90f
#define FRICTION_ICE 0.1f
#define SHEET_WIDTH 30
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

	// The element tile palette of this room
	enum RoomElement {
		NORMAL, ICE, FIRE
	} m_BaseE;

	virtual void Render(void) override = 0;

	// Get a rectangle of this room's position and size
	SDL_Rect GetRect(void) { SDL_Rect r = {(Sint16)x, (Sint16)y, (Uint16)m_Size.x, (Uint16)m_Size.y}; return r; }

	// Whether or not the room spans an area larger than the screen
	const bool IsLarge(void) { return m_IsLarge; }

	// Get the room's friction
	virtual float GetFriction(void)
		{ return FRICTION_DEFAULT; }

	// Return a pointer to the room that the player is in
	static Room* GetPlayerRoom(void);

	// If this room has a machine, dispense from it.
	void Dispense() 
		{ if (m_Machine) m_Machine->Dispense(); }

	// Get this room's machine
	Machine* GetMachine(void)
		{ return m_Machine; }

protected:
	Room(const int x, const int y, const Dimensions& size, const RoomElement element, const int renderPriority);

	// Spritesheet Rects for rooms
	SDL_Rect* tiles[SHEET_WIDTH][SHEET_HEIGHT];
	
	Dimensions m_Size;

	// Set this room's machine
	void SetMachine(Machine* machine)
		{ m_Machine = machine; }

private:
	static std::vector<Room*> s_Rooms;
	Machine* m_Machine;
	bool m_IsLarge;
};
	