//The headers
#include "toolkit.h"
#include "Resources.h"
#include "Sprite.h"
#include "Coin.h"
#include "UI.h"

SDL_Surface* screen;
TTF_Font* font;
SDL_Color machineTextColor = { 60, 175, 60 }; // Text color on the machine's displays
SDL_Color textColor = { 120, 10, 20 };
SDL_Event event;

// Rendering offset are not applicable at the beginning
float s_renderingOffset_x = 0; 
float s_renderingOffset_y = 0;

bool inFullScreen;

void toggleScreenFormat()
{
	screen = inFullScreen ? 
		SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE) :
			 SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
	inFullScreen = !inFullScreen;
}

void exitFullScreen()
{
	if (inFullScreen) screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
}

bool SDL_init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
	//Init Screen
	inFullScreen = true;
	toggleScreenFormat();
	
	SDL_WM_SetCaption("Sustainable Economy", nullptr);
	if (screen == nullptr) return false;
    
	//Init SDL_ttf
	if (TTF_Init() == -1) return false;
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        return false;
    
    Mix_AllocateChannels(NUM_MIX_CHANNELS);
    
    // Pan each channel differently, for variety
    for (int i = 0; i < NUM_MIX_CHANNELS; ++i) {
        int offset = NUM_MIX_CHANNELS - i * 2;
        int left = 127 + offset;
        
        if (i % 2 == 0) {
            left = 127 - offset;
        }
        
//        printf("Panning for channel %d: left = %d, right = %d\n", i, left, 254-left);
        if (!Mix_SetPanning(i, left, 254-left)) {
            printf("Couldn't set panning for channel %d: %s\n", i, Mix_GetError());
        }
    }
    
	return load_files();
}

void SDL_deinit()
{
	//Free all of this
	delete g_resources;

	//Quit all of that
	TTF_Quit();
    Mix_CloseAudio();
	SDL_Quit();
}

bool load_files() //Load files, and check for the success of each one
{
	try {
		g_resources = new Resources();
        g_UI = new UI();
	}
	catch (std::exception &e) {
		printf("%s\n", e.what());
		return false;
	}

	return true;
}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadedImage = nullptr;
	SDL_Surface* optimizedImage = nullptr;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != nullptr)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);

		if (optimizedImage != nullptr)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x + s_renderingOffset_x;
	offset.y = y + s_renderingOffset_y;

	//// Only blit if it is within the screen
	//bool shouldBlit = true;

	//// Only check overlapping as necessary, checking another side if no sides overlap thus far
	//bool rightOverlap = (offset.x + (clip==nullptr)? source->w : clip->w) > 0;
	//if (!rightOverlap) {
	//	bool leftOverlap = offset.x < destination->w;
	//	if (!leftOverlap) {
	//		bool bottomOverlap = (offset.y + (clip==nullptr)? source->h : clip->h) > 0;
	//		if (!bottomOverlap) {
	//			bool topOverlap = offset.y < destination->h;
	//			if (!topOverlap) {
	//				shouldBlit = false;
	//				printf("CULLING... ");
	//			}
	//		}
	//	}
	//}

	//if (shouldBlit)
		SDL_BlitSurface(source, clip, destination, &offset);
}

bool GameObject_Compare(const GameObject* first, const GameObject* second)
{
	// Get each gameObject's rendering priority
	const int priority1 = first->GetRenderPriority();
	const int priority2 = second->GetRenderPriority();

	if (priority1 != priority2)
	{
		// Primary sort criteria: rendering priorities
		return priority1 < priority2;
	}
	else
	{
		// If we're dealing with two coins, compare by their y coordinate
		const Coin* coin1 = dynamic_cast<const Coin*>(first);
		const Coin* coin2 = dynamic_cast<const Coin*>(second);
    
		// If either or both are not coins, return false
		if (!coin1 || !coin2)
			return false;
        
		return first->y < second->y;
	}
}