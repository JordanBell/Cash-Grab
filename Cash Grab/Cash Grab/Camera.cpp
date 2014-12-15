#include "Camera.h"
#include "Room.h"

#define TRANSITION_SPEED 10

Camera* g_camera = nullptr;

void Camera::UpdateFocus(void)
{
	if (m_RoomFocus != nullptr)
	{
		int targetX = (-m_RoomFocus->x);
		int targetY = (-m_RoomFocus->y);

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

