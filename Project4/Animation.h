#pragma once
#include<SDL.h>

#include <string>
using namespace std;
class Animation
{
public: 
	Animation(){}
	void Update();
	void Draw(float x, float y, int spritWidth, int spriteHeight);
	void SetProps(string textureID, int spritRow, int FrameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	int m_SpriteRow, m_SpriteFrame;
	int m_AnimSpeed, m_FrameCount;
	string m_TextureID;
	SDL_RendererFlip m_Flip;
};

