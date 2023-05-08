#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {}

void SpriteAnimation::Draw(Transform* tf) {
    TextureMgr::Instance()->DrawFrame(tf, m_SpriteRow, m_CurrentFrame);
}

void SpriteAnimation::Update(float dt) {
    m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void SpriteAnimation::SetProps(int spriteRow, int frameCount, int speed) {
    m_Speed = speed;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
}
