#pragma once
#include "gameobject.h"
#include "Wall.h"
#include "InteractZone.h"
#include "Room.h"

#define DOOR_ID_TOHUB 0
#define DOOR_ID_TOICE 1
#define DOOR_ID_TOFIRE 2

class Door :
	public GameObject
{
public:
	Door(const int _x, const int _y, const Room::RoomElement ele, const int doorID, bool isOpen = false);
	~Door(void) {}

	void Open(void);
	void Close(void);

	int GetID(void) { return m_ID; }

private:
	bool m_IsOpen;
	int m_ID;

	void OnInteract(void);
	void ReplaceWallWith(Wall* wPtr);
	void ReplaceZoneWith(InteractZone* zPtr);
	
	// Pointer to the door's wall, which is deleted when opened and constructed when closed.
	Wall* m_Wall;

	// The interaction zone in front of the door.
	InteractZone* m_InteractZone;

	// The room element of this door graphic.
	Room::RoomElement m_Element;
};

