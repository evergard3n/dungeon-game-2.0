#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL.h"

class Collider {

public:
    inline SDL_Rect Get() { return m_Box; }
    inline SDL_Rect GetHitbox() { return m_HitBox; }
    inline void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x, y, w, h }; }

    void Set(int x, int y, int w, int h) {
        m_Box = {
            x - m_Buffer.x,
            y - m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h
        };
    }
    void SetHitBox(int x, int y, int w, int h) {
        m_HitBox = {
            x = m_Box.x,
            y = m_Box.y,
            w + m_Box.w,
            h = m_Box.h

        };
    }

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
    SDL_Rect m_HitBox;
};

#endif // COLLIDER_H
