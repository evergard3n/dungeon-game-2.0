#include "Camera.h"
Camera* Camera::s_Instance = nullptr;
void Camera::update(float dt)
{
	if (m_target != nullptr) {
		m_charbox.x = m_target->X - SCREEN_WIDTH / 2;
		m_charbox.y = m_target->Y - SCREEN_HEIGHT / 2;
		if (m_charbox.x < 0) m_charbox.x = 0;
		if (m_charbox.y < 0) m_charbox.y = 0;
		if (m_charbox.x > (2 * SCREEN_WIDTH - m_charbox.w))
			m_charbox.x = (2 * SCREEN_WIDTH - m_charbox.w);
		if (m_charbox.y > ( SCREEN_WIDTH - m_charbox.h))
			m_charbox.y = ( SCREEN_WIDTH - m_charbox.h);
		m_pos = Vector2D(m_charbox.x, m_charbox.y);
	}
}