#ifndef prompt_h
#define prompt_h

#include "Sprite.h"

class Player;

#define MS_OF_FLASH 500
class Prompt :
	public Sprite
{
public:
	Prompt(Player* player);
	~Prompt(void) {}

	void Update(int delta) override final;
	void Render(void) override final { 
		if (m_Visible) 
			GameObject::Render(); 
	}
	void SetVisible(bool b) { m_Visible = b; }

protected:
	void InitSprites(void) override final;
	void UpdateImageRect(void) { m_imageRect = sprites[m_cycle/m_animationSpeed]; }

private:
	Player* m_Source;
	bool m_Visible;
	SDL_Rect* sprites[4];
};

#endif