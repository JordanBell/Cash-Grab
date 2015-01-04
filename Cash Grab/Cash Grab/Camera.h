#pragma once
#include "Player.h"
#include "Room.h"

class Camera
{
public:
	Camera(void) : m_RoomFocus(nullptr), m_DisableUpdate(false) {}
	~Camera(void) {}

	// Return the room that the player is in, without recalculating
	Room* GetRoomFocus(void)
		{ return m_RoomFocus; }

	// Find which room the player is in
	void FocusOnPlayerRoom(void)
		{ m_RoomFocus = Room::GetPlayerRoom(); }

	// Update the transition toward the room focus
	void UpdateFocus(void);

	void DisableUpdate(void) { m_DisableUpdate = true; }

private:
	Room* m_RoomFocus;
	bool m_DisableUpdate;
};

extern Camera* g_camera;
