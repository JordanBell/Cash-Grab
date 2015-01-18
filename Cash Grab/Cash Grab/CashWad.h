#pragma once
#include "throwable.h"
#include "Game.h"

// A Wad of Cash
class CashWad :
	public Throwable
{
public:
	CashWad(const int x1, const int y1, const int x2, const int y2, const int value, const int ele = NORMAL);

protected:
	void UpdateImageRect(void) override final {}
	void InitSprites(void) override final {}

	void OnCollect(void);

private:
	int m_Value;
	int m_Element;

	enum WadType {
		SINGLE, DOUBLE, TRIPLE
	} m_WadType;
};

typedef CashWad Cash;

