#pragma once
#include "Throwable.h"
#include "Door.h"
#include "Resources.h"

class Key : public Throwable
{
public:
	Key(const int x1, const int y1, const int x2, const int y2, const int id);

	void OnCollect(void);

	void InitSprites(void);

	void UpdateImageRect(void) { m_imageRect = m_Sprites[m_cycle]; }

protected:
	int m_ID;
	bool m_OnScreen;
	SDL_Rect* m_Sprites[8];
	Room::RoomElement m_Element;
};

