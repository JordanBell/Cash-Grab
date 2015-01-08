#include "IcicleSmasher.h"
#include "Game.h"
#include "Icicle.h"
#include "Resources.h"
#include <cmath>

#define TOTAL_ICICLES 9
#define DROP_RATE 5
#define POS -0.5*screen->w, 3*TILE_SIZE-screen->h

IcicleSmasher::IcicleSmasher(void)
	: Dispenser(POS, Element::ICE), m_RemainingIcicles(0)
{
	m_imageSurface = g_resources->GetIceSmasher();
	m_renderPriority = LAYER_ENV_UPPER;
}

void IcicleSmasher::OnDispense(void)
{
	// Remaining icicles to drop equals the total number of icicles
	m_RemainingIcicles = TOTAL_ICICLES; 

	// Find the number of throwables per icicle (may not divide perfectly, but that's fine - will be handled in DropIcicles)
	float perIcicle = (float)GetListTotal() / (float)TOTAL_ICICLES;
	m_ThrowablesPerIcicle = ceil(perIcicle);
}


void IcicleSmasher::OnDump(DispenseList& dispenseList)
{
	// Dispense all at once
	DropIcicles(dispenseList, TOTAL_ICICLES);
}

void IcicleSmasher::OnBurst(DispenseList& dispenseList)
{
	if (m_BurstTicker == 0)
	{
		// TODO add burst stutter
		// Dispense three icicles per burst
		DropIcicles(dispenseList, 3);
	}
			
	m_BurstTicker++;

	if (m_BurstTicker == BURST_DELAY*4) // Reset at max
		m_BurstTicker = 0;
}

void IcicleSmasher::OnSputter(DispenseList& dispenseList)
{
	// Dispense one icicle per frame
	if (m_SerpentineTicker % DROP_RATE == 0)
		DropIcicles(dispenseList, 1);

	m_SerpentineTicker++;
}

void IcicleSmasher::OnSerpentine(DispenseList& dispenseList)
{
	// TODO make this serpentine
	// Dispense one icicle per frame
	if (m_SerpentineTicker % DROP_RATE == 0)
		DropIcicles(dispenseList, 1);

	m_SerpentineTicker++;
}

void IcicleSmasher::DropIcicles(DispenseList& dispenseList, const int maxNumIcicles)
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
		Position iciclePos = GetLaunchTo();

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

const Position IcicleSmasher::GetLaunchTo(void)
{
	// Get a random position in the enclosure
	Position center = Position(-0.5*screen->w, 4.5*TILE_SIZE-screen->h);

	// Find a point around the center that isn't on the machine
	// Which means, anywhere from 3*TILE_SIZE to 7*TILE_SIZE
	//int randDistanceFromCenter = rand()%(int)(4*TILE_SIZE) + 3*TILE_SIZE;
	int randDistanceFromCenter = 5*TILE_SIZE;
	float randAngle = rand()%(628) / 100.0f;

	Position launchToHere = Position();
	launchToHere.x = center.x + (randDistanceFromCenter * cos(randAngle));
	launchToHere.y = center.y + (randDistanceFromCenter * sin(randAngle));
	launchToHere.y *= 0.80f;

	return launchToHere;
}

