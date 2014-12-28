#include "SpeechBubble.h"
#include "Game.h"
#include "Resources.h"

void SpeechBubble::Init(const string phrase)
{
	// Render this as UI
	m_renderPriority = LAYER_UI;

	// Get the speech bubble resource sheet
	if (m_imageSurface == nullptr) 
		m_imageSurface = g_resources->GetSpeechBubble();

	// Initialise the text surface
	InitText(phrase);

	// Fit the speechbubble around the text
	const Dimensions textSize = Dimensions(m_TextSurface->w, m_TextSurface->h);
	Dimensions bubbleSize = Dimensions(textSize.x / TILE_SIZE, textSize.y / TILE_SIZE); // In terms of tiles
	bubbleSize.x = (int)(bubbleSize.x + 1); // Round up
	bubbleSize.y = (int)bubbleSize.y; // Round down
	bubbleSize.x++; // Increment for margin.
	bubbleSize.y++; // Increment for margin.

	int textTileWidth = bubbleSize.x;
	int textTileHeight = bubbleSize.y;

	// Construct the speechbubble image
	Dimensions imageSize = Dimensions((textTileWidth +1)*TILE_SIZE,
									  (textTileHeight+1)*TILE_SIZE);

	// Initialise the speech bubble segment information (rendering pairs)
	int count = 0;
	m_RenderPairs.clear();
	for (int i = 0; i <= textTileWidth; i++) // Note: Inclusive of textTile size bounds, as a minimum size speech bubble will be 2x2 tiles (four corners)
	{
		for (int j = 0; j <= textTileHeight; j++)
		{
			count++;

			int horiIndex;
			int vertIndex;
			
			if (i == 0)					 horiIndex = 0; // Left
			else if (i == textTileWidth) horiIndex = 2; // Right
			else						 horiIndex = 1; // Mid
			//horiIndex = rand() % 3; // Manual override for testing
			//horiIndex = 2; // Manual override for testing
			
			if (j == 0)					  vertIndex = 0; // Top
			else if (j == textTileHeight) vertIndex = 2; // Bottom
			else						  vertIndex = 1; // Mid
			//vertIndex = rand() % 3; // Manual override for testing
			//vertIndex = 2; // Manual override for testing

			// Use this to figure out the rendering information for this segment
			SDL_Rect* smartClip = new SDL_Rect();
			smartClip->x = horiIndex*TILE_SIZE;
			smartClip->y = vertIndex*TILE_SIZE;
			smartClip->w = smartClip->h = TILE_SIZE;

			Position pos(i*TILE_SIZE, j*TILE_SIZE);

			m_RenderPairs.push_back(pair<SDL_Rect*, Position>(smartClip, pos));
		}
	}

	// Calculate the rendering position of the text surface
	Position bubbleCenter((textTileWidth+1)*TILE_SIZE/2, (textTileHeight+1)*TILE_SIZE/2);
	m_TextPosition = Position(bubbleCenter.x-textSize.x/2, bubbleCenter.y-textSize.y/2);

	// Round the pixels to avoid decimal blur
	m_TextPosition.x = (int)m_TextPosition.x;
	m_TextPosition.y = (int)m_TextPosition.y;
}

void SpeechBubble::InitText(const string phrase)
{
	// Close any existing font
	if (m_Font == nullptr)
		TTF_CloseFont(m_Font);

	// Create a new text object with the phrase
	m_Font = TTF_OpenFont("joystix monospace.ttf", TEXT_SIZE);

	SDL_Color black;
	black.r = black.g = black.b = 0;

	// Free any existing surface
	if (m_TextSurface == nullptr)
		SDL_FreeSurface(m_TextSurface);

	// Replace it with a new TTF text surface
	m_TextSurface = TTF_RenderText_Solid(m_Font, m_Phrase.c_str(), black);
}

void SpeechBubble::Render(void)
{
	if (!deactivated)
	{
		// Render each of the bubble segments
		for (pair<SDL_Rect*, Position> pair : m_RenderPairs)
			apply_surface(x + pair.second.x, y + pair.second.y, m_imageSurface, screen, pair.first);

		// Render the text surface
		//apply_surface(x-m_TextPosition.x+2, y-m_TextPosition.y+TILE_SIZE/2+3, m_TextSurface, screen, nullptr);
		apply_surface(x+m_TextPosition.x, y+m_TextPosition.y, m_TextSurface, screen, nullptr);
	}
}

void SpeechBubble::Update(int delta)
{
	if (!deactivated)
	{
		if (m_Timeout == -10)
			BooleanUpdate();
		else
			TimeoutUpdate();
	}
}

void SpeechBubble::BooleanUpdate(void)
{
	if (!deactivated)
	{
		// Follow the source
		if (m_Source)
		{
			x = m_Source->x + OFFSET_X;
			y = m_Source->y + OFFSET_Y;
		}
	}
}

void SpeechBubble::TimeoutUpdate(void)
{
	if ((m_Timeout > 0) && (!deactivated))
	{
		m_Timeout--;

		// Follow the source
		if (m_Source)
		{
			x = m_Source->x + OFFSET_X;
			y = m_Source->y + OFFSET_Y;
		}
	}
	else 
		Deactivate();
}

void SpeechBubble::SetPhrase(string phrase)
{
	m_Phrase = phrase;
	Init(phrase);
}

