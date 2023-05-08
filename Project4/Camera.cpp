#include "Camera.h"
#include "Input.h"
#include "Engine.h"

Camera* Camera::s_Instance = nullptr;

Camera::Camera() {
    m_ViewPort = Engine::Instance()->GetViewPort();
}

void Camera::TrackTarget() {

    if (m_Target == nullptr) {
        return;
    }

    else {
        m_ViewPort.x = m_Target->X - (m_ViewPort.w / 2);
        m_ViewPort.y = m_Target->Y - (m_ViewPort.h / 2);

        m_ViewPort.x = (m_ViewPort.x < 0) ? 0 : m_ViewPort.x;
        m_ViewPort.y = (m_ViewPort.y < 0) ? 0 : m_ViewPort.y;

        m_ViewPort.x = (m_ViewPort.x > (m_MapWidth - m_ViewPort.w)) ? (m_MapWidth - m_ViewPort.w) : m_ViewPort.x;
        m_ViewPort.y = (m_ViewPort.y > (m_MapHeight - m_ViewPort.h)) ? (m_MapHeight - m_ViewPort.h) : m_ViewPort.y;

        m_Position = Vector2D(m_ViewPort.x, m_ViewPort.y);
    }
}

bool Camera::GetInsectionWithViewPort(const SDL_Rect* rect) {
    const SDL_Rect screen = Engine::Instance()->GetViewPort();
    return SDL_HasIntersection(&screen, rect);
}

void Camera::TranslateX(int x) {
    m_Position.X += x;
    m_Position.X = (m_Position.X <= 0) ? 0 : m_Position.X;
    m_Position.X = (m_Position.X >= (m_MapWidth - m_ViewPort.w)) ? (m_MapWidth - m_ViewPort.w) : m_Position.X;
}

void Camera::TranslateY(int y) {
    m_Position.Y += y;
    m_Position.Y = (m_Position.Y <= 0) ? 0 : m_Position.Y;
    m_Position.Y = (m_Position.Y >= (m_MapHeight - m_ViewPort.h)) ? (m_MapHeight - m_ViewPort.h) : m_Position.Y;
}

void Camera::Translate(Vector2D target) {
    TranslateX(target.X);
    TranslateY(target.Y);
}

void Camera::SetPositionX(int targetX) {
    m_Position.X = (targetX <= 0) ? 0 : targetX;
    m_Position.X = (targetX >= (m_MapWidth - m_ViewPort.w)) ? (m_MapWidth - m_ViewPort.w) : targetX;
}

void Camera::SetPositionY(int targetY) {
    m_Position.Y = (targetY <= 0) ? 0 : targetY;
    m_Position.Y = (targetY >= (m_MapHeight - m_ViewPort.h)) ? (m_MapHeight - m_ViewPort.h) : targetY;
}

void Camera::SetPosition(Vector2D target) {
    SetPositionX(target.X);
    SetPositionY(target.Y);
}
