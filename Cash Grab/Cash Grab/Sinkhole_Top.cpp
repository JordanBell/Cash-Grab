#include "Sinkhole_Top.h"
#include "Resources.h"
#include "Game.h"
#include "Wall.h"
#include "XY.h"
#include "RoomFire_Lower.h"
#include "FirePit.h"

#include "CoinBronze.h"
#include "CoinSilver.h"
#include "CoinGold.h"

#define ANGLE_SUPPRESSION 1
#define MULTISHOT_QUANTITY_THRESHOLD 20
#define POS 1.5*screen->w-5*TILE_SIZE, 3*TILE_SIZE-screen->h

Sinkhole_Top::Sinkhole_Top(const SDL_Rect* targetBounds, RoomFire_Lower* roomPointer)
	: Dispenser(POS, Element::FIRE), m_TargetBounds(targetBounds), m_RoomPointer(roomPointer)
{
	m_imageSurface = g_resources->GetSinkholeSheet();
	// Get the top rect
	m_imageRect = new SDL_Rect();
	m_imageRect->w = m_imageSurface->w;
	m_imageRect->h = 0.75f*m_imageSurface->h;

	m_renderPriority = LAYER_ENV_UPPER;
}

#undef POS

void Sinkhole_Top::OnDump(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;

		for (amount; amount > 0; amount--)
		{
			Position startOffset = Position(TILE_SIZE, 3*TILE_SIZE);
			Position start = Position(x + startOffset.x, y + startOffset.y);

			Position launchPos(start);
			launchPos.x += rand()%(6*TILE_SIZE);
			int launchAmount = 1;

			DispenseByType(launchPos, launchAmount, type);
		}
	}
}

void Sinkhole_Top::OnBurst(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;

		if (amount > 0)
		{
			// Shoot a number of throwables from that slot, proportional to the total number being shot out. This will reduce times for large amounts of throwables to a maximum number of shot
			int leftToLaunch;

			if (m_BurstAmount <= 5)
				leftToLaunch = amount;
			else
				leftToLaunch = min(amount, m_BurstAmount);


			// Dispense a set of throwables for each row
			for (leftToLaunch; leftToLaunch > 0; leftToLaunch--)
			{
				Position startOffset = Position(TILE_SIZE, 3*TILE_SIZE);
				Position start = Position(x + startOffset.x, y + startOffset.y);

				Position launchPos(start);
				launchPos.x += rand()%(6*TILE_SIZE);

				int launchAmount = 1;

				// Launch that number of throwables from this slot
				DispenseByType(launchPos, launchAmount, type);

				amount--;
			}
		}
	}
}

void Sinkhole_Top::OnSerpentine(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;
		int total = amount;

		// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
		const int maxPerShot = (amount / MULTISHOT_QUANTITY_THRESHOLD) + 1;
		int launchAmount = amount;
		if (launchAmount > maxPerShot)
			launchAmount = maxPerShot;

		int slotNum = 0;

		int n = m_SingleShotTicker % (12*2); // SlotNum in a NUM_SLOTS*2 idea of slots (as it loops over the NUM_SLOTS twice in the pattern)
		slotNum = (n < 12) ?
					n :
					((12*2)-1) - n;

		Position startOffset = Position(2*TILE_SIZE, 3*TILE_SIZE);
		Position start = Position(x + startOffset.x, y + startOffset.y);

		Position launchPos(start.x + slotNum*TILE_SIZE/2, start.y);

		// Launch that number of throwables from this slot
		DispenseByType(launchPos, launchAmount, type);

		amount -= launchAmount;
	}
}

void Sinkhole_Top::OnSputter(DispenseList& dispenseList)
{
	for (auto& dispensePair : dispenseList)
	{
		const string type = dispensePair.first;
		int& amount = dispensePair.second;
		int total = amount;

		// Shoot a number of coins from that slot, proportional to the total number being shot out. This will reduce times for large amounts of coins to a maximum number of shot
		const int maxPerShot = (amount / MULTISHOT_QUANTITY_THRESHOLD) + 1;
		int launchAmount = amount;
		if (launchAmount > maxPerShot)
			launchAmount = maxPerShot;

		int slotNum = rand()%12;

		Position startOffset = Position(2*TILE_SIZE, 3*TILE_SIZE);
		Position start = Position(x + startOffset.x, y + startOffset.y);

		Position launchPos(start.x + slotNum*TILE_SIZE/2, start.y);

		// Launch that number of throwables from this slot
		DispenseByType(launchPos, launchAmount, type);

		amount -= launchAmount;
	}
}

const Position Sinkhole_Top::GetLaunchTo(void) const
{
	Position to;

	const int left = m_TargetBounds->x;
	const int right = m_TargetBounds->x + m_TargetBounds->w;
	const int top = m_TargetBounds->y;
	const int bottom = m_TargetBounds->y + m_TargetBounds->h;

	DispensePattern dispensePattern = m_LaunchData->pattern;

	// Find a landing position based on the type of dispensing
	if (dispensePattern == LaunchData::POINT)
	{
		to.x = left + m_TargetBounds->w/2;
		to.y = bottom - m_TargetBounds->h/4;
	}
	else if (dispensePattern == LaunchData::CORNERS)
	{
		to.x = (screen->w / 2);
		to.y = (screen->h / 2) + (TILE_SIZE/2);

		// Get a random point from here
		int r = rand() % 4;
		
		// A random corner of the target bounding box
		if (r==0) {
			to.x = left;
			to.y = top;
		}
		else if (r==1) {
			to.x = right;
			to.y = top;
		}
		else if (r==2) {
			to.x = left;
			to.y = bottom;
		}
		else if (r==3) {
			to.x = right;
			to.y = bottom;
		}

	}
	else if (dispensePattern == LaunchData::LINES_H)
	{
		do {
			to.x = left + rand() % m_TargetBounds->w;
			to.y = top + (rand() % 8) * (2*TILE_SIZE); // 9 possible lines, 2*TILE_SIZEs apart
		} while (InSinkhole(to));
	}
	else if (dispensePattern == LaunchData::LINES_V)
	{
		do {
			to.x = left + TILE_SIZE/2 + (rand() % 9) * (2 * TILE_SIZE);
			to.y = top + rand() % m_TargetBounds->h; 
		} while (InSinkhole(to));
	}
	else if ((dispensePattern == LaunchData::LEFT) || (dispensePattern == LaunchData::RIGHT) || (dispensePattern == LaunchData::BOTH))
	{
		if (dispensePattern == LaunchData::LEFT) to = m_RoomPointer->GetRandPitPos("left");
		else if (dispensePattern == LaunchData::RIGHT) to = m_RoomPointer->GetRandPitPos("right");
		else // (dispensePattern == LaunchData::BOTH)
		{
			to = m_RoomPointer->GetRandPitPos("any");
		}
	}
	else // NORM, randomise within the box
	{
		do {
			to.x = left + rand() % m_TargetBounds->w;
			to.y = top + rand() % m_TargetBounds->h; 
		} while (InSinkhole(to));
	}

	return to;
}

const bool Sinkhole_Top::InSinkhole(const Position& pos) const
{
	bool inX, inY, in;

	inX = ((pos.x > x-TILE_SIZE/2) && (pos.x < x+m_imageRect->w-TILE_SIZE/2));
	inY = ((pos.y > y+TILE_SIZE) && (pos.y < y+4*TILE_SIZE)); // height*2 to include bottom of sinkhole

	in = inX && inY;

	return in;
}
