#include "Room.h"
#include "Game.h"
#include "toolkit.h"
#include "Resources.h"

std::vector<Room*> Room::s_Rooms;

Room::Room(const int x, const int y, const Dimensions& size, RoomElement element, const int renderPriority) 
	: GameObject(x, y), m_Size(size), m_BaseE(element)
{
	// TODO rename Environment spritesheet to Room spritesheet?
	m_imageSurface = g_resources->GetEnvironmentImage();

	//Set the bounds for the possible clips from the m_imageSurface
	for (int i = 0; i < SHEET_WIDTH; i++)
	{
		for (int j = 0; j < SHEET_HEIGHT; j++)
		{
			SDL_Rect* clip = new SDL_Rect();

			clip->x = TILE_SIZE * i;
			clip->y = TILE_SIZE * j;
			clip->w = clip->h = TILE_SIZE;

			// Add this to the sprites
			Room::tiles[i][j] = clip;
		}
	}

	// Set whether or not the given size spans across an area larger than the screen
	m_IsLarge = ((size.x > screen->w) || (size.y > screen->h));

	m_renderPriority = renderPriority;

	// Add this room to the vector of lists (only if it is the primary representation of the room: when it's the lower environment layer)
	if (m_renderPriority == LAYER_ENV_LOWER)
		Room::s_Rooms.push_back(this);
}

Room* Room::GetPlayerRoom(void)
{
	// All variables used for boundary checking
	Position playerPos(g_player->GetCenter().x, g_player->GetCenter().y);
	int roomLeft, roomRight, roomTop, roomBottom;
	bool inLeft, inRight, inTop, inBottom;

	// Check each room too see if the player is inside
	for (Room* r : s_Rooms)
	{
		SDL_Rect rect = r->GetRect();

		// Room Boundaries
		roomLeft = rect.x;
		roomTop = rect.y;
		roomRight = roomLeft + rect.w;
		roomBottom = roomTop + rect.h;

		// Check if the player is within all boundaries
		inLeft   = playerPos.x >= roomLeft;
		inRight  = playerPos.x <= roomRight;
		inTop	 = playerPos.y >= roomTop;
		inBottom = playerPos.y <= roomBottom;

		if (inLeft && inRight && inTop && inBottom)
			return r;
	}

	// If not in any rooms, return null
	return nullptr;
}
