#include "Camera.h"
#include "Room.h"

#define TRANSITION_SPEED 10

Camera* g_camera = nullptr;

void Camera::UpdateFocus(void)
{
	if (!m_DisableUpdate)
	{
		if (m_RoomFocus != nullptr)
		{
			int targetX;
			int targetY;

			if (m_RoomFocus->IsLarge())
			{
				// Center on the player, but don't reveal the area beyond the rooms bounds. Set the target X/Y accordingly
				SDL_Rect roomRect = m_RoomFocus->GetRect();

				// X-Direction, check if not revealing the left side
				if (g_player->x-screen->w/2 > roomRect.x) 
				{
					// Check if not revealing right side
					if (g_player->x+screen->w/2 < roomRect.x + roomRect.w)
						targetX = -g_player->x +screen->w/2;
					else 
						targetX = -(roomRect.x + roomRect.w) +screen->w;
				}
				else
					targetX = (-m_RoomFocus->x);

				// Y-Direction, check if not revealing the top side
				if (g_player->y-screen->h/2 > roomRect.y) 
				{
					// Check if not revealing the bottom side
					if (g_player->y+screen->h/2 < roomRect.y + roomRect.h) 
						targetY = -g_player->y +screen->h/2;
					else 
						targetY = -(roomRect.y + roomRect.h) +screen->h;
				}
				else
					targetY = (-m_RoomFocus->y);
			}
			else
			{
				targetX = (-m_RoomFocus->x);
				targetY = (-m_RoomFocus->y);
			}



			// Only bother updating if update is needed
			if ((s_renderingOffset_x != targetX) || (s_renderingOffset_y != targetY))
			{
				// Find the difference between the current offset and the target offset
				int diffX = targetX - s_renderingOffset_x;
				int diffY = targetY - s_renderingOffset_y;

				int polX = (diffX < 0)? -1 : 1;
				int polY = (diffY < 0)? -1 : 1;
				int speedX = min(TRANSITION_SPEED, abs(diffX));
				int speedY = min(TRANSITION_SPEED, abs(diffY));
				speedX *= polX;
				speedY *= polY;

				// Change the rendering offset
				s_renderingOffset_x += speedX;
				s_renderingOffset_y += speedY;
			}
		}
		else printf("Could not find player room.");
	}
}

