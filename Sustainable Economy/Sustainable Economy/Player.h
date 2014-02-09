#include "Entity.h"

class Player : public Entity {
public:
	static const int UP		= 0;
	static const int RIGHT	= 1;
	static const int DOWN	= 2;
	static const int LEFT	= 3;
	
	//De/Constructors
	Player(void);
	Player(SDL_Surface* spriteSheet) : Entity(spriteSheet), direction(DOWN) {Player();}
	~Player() {}

	//Defined Here
	void face_direction (int direction) {direction = direction;};
	
	//Defined in cpp
	void update();
	void render();

private:
	int direction;
	SDL_Rect* sprites[ 4 ][ 3 ];

	//Defined in cpp
	void set_skin();
};