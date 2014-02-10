#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

SDL_Surface* screen = NULL;
TTF_Font* font = NULL;
SDL_Color textColor = { 255, 255, 255 };
SDL_Event event;

SDL_Surface* load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
bool SDL_init();
bool load_files();
void SDL_deinit();
