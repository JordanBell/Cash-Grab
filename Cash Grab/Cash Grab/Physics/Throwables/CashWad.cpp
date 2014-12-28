#include "CashWad.h"
#include "Resources.h"
#include "Game.h"
#include "Wallet.h"

#define CASH_TIER_1 100
#define CASH_TIER_2 200
#define CASH_TIER_3 300

CashWad::CashWad(const int x1, const int y1, const int x2, const int y2, const int value)
	: Throwable(x1, y1, x2, y2), m_Value(value)
{
	m_imageSurface = g_resources->GetCoinSheet();

	// Determine the image to be used based on the value
	if (value <= CASH_TIER_1)
		m_WadType = SINGLE;
	else if (value <= CASH_TIER_2)
		m_WadType = DOUBLE;
	else
		m_WadType = TRIPLE;

	m_imageRect = new SDL_Rect();
	m_imageRect->x = TILE_SIZE * m_WadType;
	m_imageRect->y = TILE_SIZE * 3;
	m_imageRect->w = TILE_SIZE;
	m_imageRect->h = TILE_SIZE;
}

void CashWad::OnCollect(void)
{
	Wallet::AddCash(m_Value);
	printf("Cash: %d\n", Wallet::GetCash());
}

