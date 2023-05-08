#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"

TextureMgr* TextureMgr::s_Instance = nullptr;

TextureMgr::TextureMgr() {
    m_Renderer = Engine::Instance()->GetRenderer();
}

SDL_Texture* TextureMgr::Load(std::string filename) {

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        std::cout << "IMG_Load Failed: " << filename << " " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    if (texture == nullptr) {
        std::cout << "Failed to create surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

bool TextureMgr::Add(std::string id, std::string filename) {

    if (m_TextureMap.count(id) > 0) {
        std::cout << "Texture id: " << id << " already exist in map" << std::endl;
        return false;
    }
    else {
        SDL_Texture* texture = Load(filename);
        if (texture == nullptr) {
            std::cout << "Texture id: " << id << " is empty" << std::endl;
            return false;
        }
        m_TextureMap[id] = texture;
    }
    return true;
}

void TextureMgr::Draw(Transform* tf) {
    const Vector2D cam = Camera::Instance()->GetPosition() * tf->ScrollRatio;
    const SDL_Rect dstRect = { tf->X - cam.X, tf->Y - cam.Y, tf->Width * tf->ScaleX, tf->Height * tf->ScaleY };

    if (Camera::Instance()->GetInsectionWithViewPort(&dstRect)) {
        SDL_RenderCopyEx(m_Renderer, m_TextureMap[tf->TextureID], nullptr, &dstRect, tf->Rotation, nullptr, tf->Flip);
    }
}
void TextureMgr::DrawStatic(Transform* tf) {
    
    const SDL_Rect dstRect = { tf->X, tf->Y, tf->Width * tf->ScaleX, tf->Height * tf->ScaleY };

    if (Camera::Instance()->GetInsectionWithViewPort(&dstRect)) {
        SDL_RenderCopyEx(m_Renderer, m_TextureMap[tf->TextureID], nullptr, &dstRect, tf->Rotation, nullptr, tf->Flip);
    }
}
void TextureMgr::DrawFrame(Transform* tf, int row, int frame) {
    const Vector2D cam = Camera::Instance()->GetPosition() * tf->ScrollRatio;
    const SDL_Rect dstRect = { tf->X - cam.X, tf->Y - cam.Y, tf->Width * tf->ScaleX, tf->Height * tf->ScaleY };
    if (Camera::Instance()->GetInsectionWithViewPort(&dstRect)) {
        const SDL_Rect srcRect = { tf->Width * frame, tf->Height * row, tf->Width, tf->Height };
        SDL_RenderCopyEx(m_Renderer, m_TextureMap[tf->TextureID], &srcRect, &dstRect, tf->Rotation, nullptr, tf->Flip);
    }
}

void TextureMgr::DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio) {
    Vector2D cam = Camera::Instance()->GetPosition() * speedRatio;
    const SDL_Rect dstRect = { x - cam.X, y - cam.Y, tilesize, tilesize };
    if (Camera::Instance()->GetInsectionWithViewPort(&dstRect)) {
        SDL_Rect srcRect = { tilesize * col, tilesize * row, tilesize, tilesize };
        SDL_RenderCopyEx(m_Renderer, m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void TextureMgr::LoadText(std::string id, std::string text, int x, int y, SDL_Color text_color, TTF_Font* font)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    if (surface == nullptr) {
        std::cout << "Failed to load text surface\n";
        std::cout << "Error:" << TTF_GetError() << std::endl;

    }
    else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Instance()->GetRenderer(), surface);
        if (texture == nullptr) {
            std::cout << "Failed to load text texture from surface\n";
            std::cout << "Error:" << TTF_GetError() << std::endl;

        }
        else {
            m_TextureMap[id] = texture;
            SDL_Rect srcRect = { 0, 0, surface->w, surface->h };
            SDL_Rect dstRect = { x, y, surface->w, surface->h };
            SDL_RenderCopyEx(Engine::Instance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
        }
    }
}

void TextureMgr::QueryTexture(std::string id, int* out_w, int* out_h) {
    SDL_QueryTexture(m_TextureMap[id], NULL, NULL, out_w, out_h);
}

void TextureMgr::Clean() {
    for (TextureMap::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();
    std::cout << "Texture system cleaned!" << std::endl;
}

