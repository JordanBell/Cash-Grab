#include "IcicleSmasher.h"
#include "Game.h"
#include "Icicle.h"
#include "Resources.h"
#include "Wall.h"
#include <cmath>

#define TOTAL_ICICLES 25
#define DROP_RATE 5
#define POS -0.5*screen->w - 1.25*TILE_SIZE, 4.5*TILE_SIZE-screen->h
#define HAMMER_TIME 10

IcicleSmasher::IcicleSmasher(void)
	: Dispenser(POS, Element::ICE), m_RemainingIcicles(0), m_HammerTicker(0)
{
	m_imageSurface = g_resources->GetIceSmasher();
	m_renderPriority = LAYER_GROUND;

	// The image rect will later be defined in the render function
	m_imageRect = new SDL_Rect();


	// Set up wall
	g_game->addCollidable( new Wall(POS + 0.5*TILE_SIZE, 3.5*TILE_SIZE, 2.25*TILE_SIZE ));

	SetBurstDelay(DEFAULT_BURST_DELAY*4);
	SetFireRate(5);
}

void IcicleSmasher::Render(void)
{
	if (m_HammerTicker == 0)
	{
		// Hammer up
		m_imageRect->x = 0;
		m_imageRect->y = 0;
		m_imageRect->w = 6*TILE_SIZE;
		m_imageRect->h = 3*TILE_SIZE;
	}
	else
	{
		// Hammer down
		m_imageRect->x = 6*TILE_SIZE;
		m_imageRect->y = 0;
		m_imageRect->w = 6*TILE_SIZE;
		m_imageRect->h = 3*TILE_SIZE;
	}

	// Render normally using this new imageRect
	GameObject::Render();
}


void IcicleSmasher::OnDispense(void)
{
	// Remaining icicles to drop equals the total number of icicles
	m_RemainingIcicles = TOTAL_ICICLES;

	// Find the number of throwables per icicle (may not divide perfectly, but that's fine - will be handled in DropIcicles)
	float perIcicle = (float)GetListTotal() / (float)TOTAL_ICICLES;
	m_ThrowablesPerIcicle = ceil(perIcicle);

	m_HammerTicker = HAMMER_TIME;
}

void IcicleSmasher::OnDump(DispenseList& dispenseList)
{
	// Dispense all at once
	DropIcicles(dispenseList, TOTAL_ICICLES);
}

void IcicleSmasher::OnBurst(DispenseList& dispenseList)
{
	// Dispense three icicles per burst
	DropIcicles(dispenseList, 3);
}

void IcicleSmasher::OnSputter(DispenseList& dispenseList)
{
	// Dispense one icicle per frame
	DropIcicles(dispenseList, 1);
}

void IcicleSmasher::OnSerpentine(DispenseList& dispenseList)
{
	// Dispense one icicle per frame
	DropIcicles(dispenseList, 1, true);
}

void IcicleSmasher::DropIcicles(DispenseList& dispenseList, const int maxNumIcicles, const bool isSerpentine)
{
	// The number of icicles dropped should not go over the number of remaining icicles
	int numIcicles = min(maxNumIcicles, m_RemainingIcicles);

	// Change the icicle count so that the number of icicles is up to date.
	m_RemainingIcicles -= numIcicles; 

	// Construct that many icicles, with the appropriate throwables held within
	for (numIcicles; numIcicles > 0; numIcicles--)
	{
		// The number of throwables held within the icicle. This list will be passed to create the icicle, but first we need to build it.
		DispenseList* icicleDispenseList = GetIcicleDispenseList(dispenseList);
		Position iciclePos;
		if (isSerpentine)
			iciclePos = GetSerpentineLaunchTo();
		else
			iciclePos = GetLaunchTo();

		// Create an icicle with this information, and drop it
		Icicle* icicle = new Icicle(icicleDispenseList, iciclePos);
		icicle->Drop();
		g_game->addGameObject(icicle);
	}
}

DispenseList* IcicleSmasher::GetIcicleDispenseList(DispenseList& dispenseList)
{
	// The number of throwables held within the icicle. This list will be passed to create the icicle, but first we need to build it.
	DispenseList* r_icicleDispenseList = new DispenseList();

	// The number of remaining throwables to allocate
	int toAllocate = min(m_ThrowablesPerIcicle, GetListTotal());

	// There are two checks for whether or not we should keep looking through the dispense list. As defines, they will reassess.
#define LIST_NOT_EMPTY (!dispenseList.empty())
#define MORE_TO_ALLOCATE (toAllocate > 0)

	// Ends when proper amount reached, or list becomes empty.
	while (MORE_TO_ALLOCATE && LIST_NOT_EMPTY)
	{
		auto& frontPair = dispenseList.front();
		int& frontAmount = frontPair.second;

		// Maybe the amount is 0, in which case we should pop it out
		if (frontAmount == 0)
		{
			// No more quantity, remove from the list
			dispenseList.pop_front();
		}
		else
		{
			// Otherwise, find out how many of that throwable should be put in the icicle. Don't go past the number left to allocate
			int thisIcicleAmount = min(frontAmount, toAllocate);

			string frontType = frontPair.first;

			// Add this number of throwables to the icicle's list
			r_icicleDispenseList->push_back( pair<string, int>(frontType, thisIcicleAmount));

			// Some more has been allocated
			toAllocate -= thisIcicleAmount;
			frontAmount -= thisIcicleAmount; // As a reference, this affects the dispenser's dispenseList directly
		}
	} // The icicle's dispense list has now been allocated.

	return r_icicleDispenseList;
}

const Position IcicleSmasher::GetSerpentineLaunchTo(void)
{
	// Get a random position in the enclosure
	Position center = Position(-0.5*screen->w, 3*TILE_SIZE-screen->h);

	// Find a point around the center that isn't on the machine
	int distanceFromCenter = 6*TILE_SIZE;

	// Get an angle that naturally changes each call (using the ticker for single shot dispense methods)
	float serpProgress = (((m_SingleShotTicker/GetFireRate())%TOTAL_ICICLES) / (float)TOTAL_ICICLES);
	float serpAngle = serpProgress * 6.28f;

	Position launchToHere = Position();
	launchToHere.x = center.x + (distanceFromCenter * cos(serpAngle));
	launchToHere.y = center.y + (distanceFromCenter * sin(serpAngle));
	launchToHere.y *= 0.75f;

	return launchToHere;
}

const Position IcicleSmasher::GetLaunchTo(void) const
{
	// Get a somewhat random position around the enclosure
	Position center = Position(-0.5*screen->w, 3*TILE_SIZE-screen->h);

	int distanceFromCenter = 6*TILE_SIZE;
	float randAngle = rand()%(628) / 100.0f;

	Position launchToHere = Position();
	launchToHere.x = center.x + (distanceFromCenter * cos(randAngle));
	launchToHere.y = center.y + (distanceFromCenter * sin(randAngle));
	launchToHere.y *= 0.75f;

	return launchToHere;
}

