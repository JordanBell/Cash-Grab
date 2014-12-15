#pragma once
#include "Player.h"
#include "Room.h"

class Camera
{
public:
	Camera(void) : m_RoomFocus(nullptr) {}
	~Camera(void) {}

	// Find which room the player is in
	void FocusOnPlayerRoom(void)
		{ m_RoomFocus = Room::GetPlayerRoom(); }

	// Update the transition toward the room focus
	void UpdateFocus(void);

private:
	Room* m_RoomFocus;
};

extern Camera* g_camera;
