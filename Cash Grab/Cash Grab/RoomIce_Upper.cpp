#include "RoomIce_Upper.h"
#include "EnvironmentSheetIndexes.h"
#include "ParticleSnow.h"

#define SNOWFLAKE_CHANCE 3

void RoomIce_Upper::Render(void)
{
	// Top Walls
	for (int _x = x+TILE_SIZE; _x < x + m_Size.x; _x += TILE_SIZE) 
		apply_surface(_x, y+m_Size.y-TILE_SIZE, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);

	// Side Walls
	for (int _y = y; _y < y + m_Size.y; _y += TILE_SIZE)
		apply_surface(x, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);
	for (int _y = y+10*TILE_SIZE; _y < y + m_Size.y; _y += TILE_SIZE)
		apply_surface(x + screen->w-TILE_SIZE, _y, m_imageSurface, screen, tiles[WALL_TOP][m_BaseE]);

	// Station
	RenderStationUpper(8*TILE_SIZE, 3*TILE_SIZE);
}

void RoomIce_Upper::Update(int delta)
{
	// Drop Snowflakes
	if (rand() % SNOWFLAKE_CHANCE == 0)
	{
		// Drop it above a random position within the world
		XY dropAbove = XY(
			rand()%int(m_Size.x-2*TILE_SIZE)+TILE_SIZE, 
			rand()%int(m_Size.y-5*TILE_SIZE)+4*TILE_SIZE
		);
		ParticleSnow* snowParticle = new ParticleSnow(x + dropAbove.x, y + dropAbove.y, 1000);
		//ParticleSimple* snowParticle = new ParticleSimple(100, 100, 100);

		g_game->addGameObject(snowParticle);

		snowParticle->Drop();
	}
}

