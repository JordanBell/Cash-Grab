#ifndef toolkit_h
#define toolkit_h

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "XY.h"
#include <string>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 16

#define NUM_MIX_CHANNELS 50

extern SDL_Surface* screen;
extern SDL_Color textColor;
extern SDL_Color machineTextColor;
extern SDL_Event event;

extern Position cameraRenderingOffset;

// Functions
SDL_Surface* load_image(std::string filename);

class GameObject;

void toggleScreenFormat();
void exitFullScreen();

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = nullptr, bool applyRenderingOffset = true);
bool SDL_init();
bool load_files();
void SDL_deinit();

const bool RectIntersect(const SDL_Rect* r1, const SDL_Rect* r2);

// Comparison function for sorting GameObject lists
bool GameObject_Compare(const GameObject* first, const GameObject* second);

#endif