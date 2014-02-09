//The headers
#include <string>
#include "toolkit.h"

bool init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

	//Init Screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	SDL_WM_SetCaption("SDL Tutorials", NULL);
	if (screen == NULL) return false;

	//Init SDL_ttf
	if (TTF_Init() == -1) return false;

	return load_files();
}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);

		if (optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

int main(int argc, char* args[])
{
	//<start>
	if (init() == false)
	{
		return 1;
	}
	if (load_files() == false)
	{
		return 1;
	}
	//</start>

	message = TTF_RenderText_Solid(font, "Testing out some good ol' TTL!", textColor);

	apply_surface(0, 0, background, screen);
	apply_surface(50, 150, message, screen);

	if (SDL_Flip(screen) == -1)
	{
		return 1;
	}

	SDL_Delay(2000);

	//Quit SDL
	deinit();

	return 0;
}