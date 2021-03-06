#include "RoomFire_Lower.h"
#include "Wall.h"
#include "EnvironmentSheetIndexes.h"
#include "Sinkhole_Top.h"
#include "InteractZone.h"
#include "FirePit.h"

RoomFire_Lower::RoomFire_Lower(void)
	: Room(screen->w, -screen->h*2, Dimensions(screen->w, screen->h*2), FIRE, LAYER_ENV_LOWER)
{
	InitialiseDispenser();
	CreateStationWalls(8*TILE_SIZE, 3*TILE_SIZE);
	SDL_Rect* stationInteractZone = new SDL_Rect();
	stationInteractZone->x = x + 8*TILE_SIZE;
	stationInteractZone->y = y + 7*TILE_SIZE;
	stationInteractZone->w = 4*TILE_SIZE;
	stationInteractZone->h = TILE_SIZE/2;
	InteractZone* i = new InteractZone(stationInteractZone, [] { g_player->Say("It's not working..."); }, Player::UP);

	// Top & Bottom Walls
	for (int _x = x+TILE_SIZE; _x < x + m_Size.x; _x += TILE_SIZE) 
	{
		g_game->addCollidable(new Wall(_x, y+m_Size.y-TILE_SIZE));
		g_game->addCollidable(new Wall(_x, y+3*TILE_SIZE));
	}

	// Side Walls
	for (int _y = y; _y < y + m_Size.y; _y += TILE_SIZE)
	{
		// Left Walls
		if ((_y != y+8*TILE_SIZE) && (_y != y+9*TILE_SIZE))
			g_game->addCollidable(new Wall(x, _y));
		
		// Right Walls
		g_game->addCollidable(new Wall(x+screen->w-TILE_SIZE, _y));
	}

	// Mid Walls
	for (int _x = x+TILE_SIZE; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE) {
		if ((_x <= x+6*TILE_SIZE) || (_x >= x+screen->w-7*TILE_SIZE))
		{
			int _y = y + 10*TILE_SIZE;
			g_game->addCollidable(new Wall(_x, _y+0*TILE_SIZE));
			g_game->addCollidable(new Wall(_x, _y+1*TILE_SIZE));
			g_game->addCollidable(new Wall(_x, _y+2*TILE_SIZE));
			g_game->addCollidable(new Wall(_x, _y+3*TILE_SIZE));
		}
	}

	// Create locations for the FirePits. This is kept in a member list so that the dispenser can get their positions
	m_PitPositions.push_back( Position(x+6*TILE_SIZE, y+16.5*TILE_SIZE) );
	m_PitPositions.push_back( Position(x+screen->w-7*TILE_SIZE, y+16.5*TILE_SIZE) );

	m_PitPositions.push_back( Position(x+3*TILE_SIZE, y+20.5*TILE_SIZE) );
	m_PitPositions.push_back( Position(x+screen->w-4*TILE_SIZE, y+20.5*TILE_SIZE) );

	m_PitPositions.push_back( Position(x+6*TILE_SIZE, y+25*TILE_SIZE) );
	m_PitPositions.push_back( Position(x+screen->w-7*TILE_SIZE, y+25*TILE_SIZE) );

	// Create firepits at those positions
	for (Position& pitPos : m_PitPositions)
		g_game->addGameObject( new FirePit(pitPos.x, pitPos.y) );
}

void RoomFire_Lower::InitialiseDispenser(void)
{
	SDL_Rect* targetBounds = new SDL_Rect();
	targetBounds->x = x+TILE_SIZE;
	targetBounds->y = y+14*TILE_SIZE;
	targetBounds->w = 17*TILE_SIZE;
	targetBounds->h = 14*TILE_SIZE;

	Sinkhole_Top* dispenseSinkhole = new Sinkhole_Top(targetBounds, this);
	g_game->addGameObject( dispenseSinkhole );
	SetDispenser(dispenseSinkhole);

	// Top Interact Zone
	SDL_Rect* zoneRect = new SDL_Rect();
	zoneRect->x = dispenseSinkhole->x+TILE_SIZE*3/2;
	zoneRect->y = dispenseSinkhole->y + 1.75*TILE_SIZE;
	zoneRect->w = 7*TILE_SIZE;
	zoneRect->h = TILE_SIZE*1.25;
	InteractZone* sinkholeActivation1 = new InteractZone(zoneRect, [dispenseSinkhole] { dispenseSinkhole->Dispense();}, Player::Direction::DOWN);

	// Bottom Interact Zone
	zoneRect = new SDL_Rect();
	zoneRect->x = dispenseSinkhole->x+TILE_SIZE*3/2;
	zoneRect->y = dispenseSinkhole->y + 3.5*TILE_SIZE;
	zoneRect->w = 7*TILE_SIZE;
	zoneRect->h = TILE_SIZE*1.25;
	InteractZone* sinkholeActivation2 = new InteractZone(zoneRect, [dispenseSinkhole] { dispenseSinkhole->Dispense();}, Player::Direction::UP);

	// Right Interact Zone
	zoneRect = new SDL_Rect();
	zoneRect->x = dispenseSinkhole->x+9*TILE_SIZE;
	zoneRect->y = dispenseSinkhole->y + 2.5*TILE_SIZE;
	zoneRect->w = 0.5*TILE_SIZE;
	zoneRect->h = TILE_SIZE*1.5;
	InteractZone* sinkholeActivation3 = new InteractZone(zoneRect, [dispenseSinkhole] { dispenseSinkhole->Dispense();}, Player::Direction::LEFT);

	// Left Interact Zone
	zoneRect = new SDL_Rect();
	zoneRect->x = dispenseSinkhole->x+0.5*TILE_SIZE;
	zoneRect->y = dispenseSinkhole->y + 2.5*TILE_SIZE;
	zoneRect->w = 0.5*TILE_SIZE;
	zoneRect->h = TILE_SIZE*1.5;
	InteractZone* sinkholeActivation4 = new InteractZone(zoneRect, [dispenseSinkhole] { dispenseSinkhole->Dispense();}, Player::Direction::RIGHT);
}


void RoomFire_Lower::Render(void)
{
	RenderBasic();
	RenderInterior();
}

void RoomFire_Lower::RenderBasic(void)
{
	// Floor
	for (int _x = x; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE)
		for (int _y = y+4*TILE_SIZE; _y < y + m_Size.y-TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
	
	// Top Wall
	for (int _x = x; _x < x + screen->w; _x += TILE_SIZE)
		for (int _y = y+4*TILE_SIZE; _y < y-TILE_SIZE; _y += TILE_SIZE)
			apply_surface(_x, _y, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

	for (int _x = x+TILE_SIZE; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE) {
		apply_surface(_x, y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
		apply_surface(_x, y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
		apply_surface(_x, y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);
	}

	// Left Column
	apply_surface(x, y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+4*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	apply_surface(x, y+5*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x, y+6*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
	apply_surface(x, y+7*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);

	apply_surface(x, y+8*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
	apply_surface(x, y+9*TILE_SIZE, m_imageSurface, screen, tiles[FLOOR][m_BaseE]);
}

void RoomFire_Lower::RenderInterior(void)
{
	RenderStationLower(8*TILE_SIZE, 3*TILE_SIZE);

	for (int _x = x+TILE_SIZE; _x < x + screen->w-TILE_SIZE; _x += TILE_SIZE) {
		if ((_x <= x+6*TILE_SIZE) || (_x >= x+screen->w-7*TILE_SIZE))
		{
			int _y = y + 10*TILE_SIZE;
			apply_surface(_x, _y+0*TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
			apply_surface(_x, _y+1*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
			apply_surface(_x, _y+2*TILE_SIZE, m_imageSurface, screen, tiles[WALL][m_BaseE]);
			apply_surface(_x, _y+3*TILE_SIZE, m_imageSurface, screen, tiles[WALL_BASE][m_BaseE]);
		}
	}
}

const Position& RoomFire_Lower::GetRandPitPos(const string pitSelection) const
{
	// Get pits whose x coord in left of this center
	const int centerX = x + screen->w/2;
	const int numLeftPits = (pitSelection == "any") ? m_PitPositions.size() : m_PitPositions.size() / 2;
	const int randPitCount = rand() % numLeftPits; // Determines which pit in sequence is selected
	int count = 0;

	function<bool (Position)> isValidPit;

	// The above function has a different definition based on the pitSelection parameter
	if (pitSelection == "left")
	{
		// Pit position is valid when left of center
		isValidPit = [centerX](Position pos) { return (pos.x <= centerX); };
	}
	else if (pitSelection == "right")
	{
		// Pit position is valid when right of center
		isValidPit = [centerX](Position pos) { return (pos.x > centerX); };
	}
	else // pitSelection == "any"
	{
		// Pit position is always valid
		isValidPit = [](Position pos) { return true; };
	}

	// Loop through and return a random pit position
	for (Position const& pitPos : m_PitPositions)
	{
		// Use isValidPit to filter out positions
		if (isValidPit(pitPos))
		{
			if (randPitCount == count)
				return pitPos;

			count++;
		}
	}

	throw runtime_error("No pits found.");
}
