#include "Animation.h"
#include "TextureManager.h"
#include<SDL.h>
void Animation::Update()
{
	m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;

}

void Animation::Draw(float x, float y, int spritWidth, int spriteHeight)
{
	TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spritWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);

}

void Animation::SetProps(string textureID, int spritRow, int FrameCount, int animSpeed, SDL_RendererFlip flip)
{
	m_TextureID = textureID;
	m_SpriteRow = spritRow;
	m_FrameCount = FrameCount;
	m_AnimSpeed = animSpeed;
	m_Flip = flip;
}
