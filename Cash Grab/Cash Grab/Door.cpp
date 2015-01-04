#include "Door.h"
#include "EnvironmentSheetIndexes.h"
#include "Game.h"
#include "Resources.h"
#include "Key.h"
#include "Inventory.h"

Door::Door(const int _x, const int _y, const int ele, const int doorID, bool isOpen)
	: GameObject(_x, _y), m_IsOpen(isOpen), m_Wall(nullptr), m_Element(ele), m_InteractZone(nullptr), m_ID(doorID)
{ 
	m_imageSurface = g_resources->GetEnvironmentImage();

	// Initialise as opened or closed depending on the set value
	m_IsOpen? Open() : Close(); 

	// Initialise the InteractZone
	SDL_Rect* interactArea = new SDL_Rect();
	interactArea->x = x;
	interactArea->y = y + m_imageRect->h; // Place below
	interactArea->w = m_imageRect->w;
	interactArea->h = TILE_SIZE/3;

	m_InteractZone = new InteractZone(interactArea, [this] { OnInteract();}, Player::Direction::UP);

	// Set interact zone's activeness according to whether or not this is open
	m_IsOpen? m_InteractZone->Deactivate() : m_InteractZone->Activate();
}

void Door::OnInteract(void)
{
	bool canOpen = false;

	vector<int> const& ownedKeys = Inventory::GetInstance().GetKeys();

	for (auto keyID : ownedKeys)
		if (keyID == m_ID)
			canOpen = true;

	if (canOpen)
		Open();
	else
		g_player->Say("I don't have the key.");
}


void Door::Open(void)
{
	// Get the spritesheet clip for the open doors
	SDL_Rect newDoorRect = RECT_DEF_DOOR_OPEN;

	// Delete the current image rect
	if (m_imageRect) delete m_imageRect;

	// Copy over the value
	m_imageRect = new SDL_Rect(newDoorRect);
	m_imageRect->y = m_Element * TILE_SIZE; // Set the clip to the right element

	// Remove any existing wall
	ReplaceWallWith( nullptr );
	if (m_InteractZone) m_InteractZone->Deactivate();
}

void Door::Close(void)
{
	// Get the spritesheet clip for the open doors
	SDL_Rect newDoorRect = RECT_DEF_DOOR_LOCKED;

	// Delete the current image rect
	if (m_imageRect) delete m_imageRect;

	// Copy over the value
	m_imageRect = new SDL_Rect(newDoorRect);
	m_imageRect->y = m_Element * TILE_SIZE; // Set the clip to the right element

	// Replace any existing wall
	ReplaceWallWith( new Wall(x, y, 2*TILE_SIZE, TILE_SIZE) );
	if (m_InteractZone) m_InteractZone->Activate();
}

void Door::ReplaceZoneWith(InteractZone* zPtr)
{
	// Delete
	if (m_InteractZone) 
		delete m_InteractZone;

	// Replace
	m_InteractZone = zPtr;
}


void Door::ReplaceWallWith(Wall* wPtr)
{
	// Delete
	if (m_Wall) 
		g_game->removeCollidable(m_Wall);

	// Replace
	m_Wall = wPtr;

	// Add new Wall
	if (m_Wall != nullptr) g_game->addCollidable(m_Wall);
}

