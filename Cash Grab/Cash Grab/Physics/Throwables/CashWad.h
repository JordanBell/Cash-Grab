#pragma once
#include "throwable.h"

// A Wad of Cash
class CashWad :
	public Throwable
{
public:
	CashWad(const int x1, const int y1, const int x2, const int y2, const int value);

protected:
	void UpdateImageRect(void) override final {}
	void InitSprites(void) override final {}

	void OnCollect(void);

private:
	int m_Value;

	enum WadType {
		SINGLE, DOUBLE, TRIPLE
	} m_WadType;
};

typedef CashWad Cash;

