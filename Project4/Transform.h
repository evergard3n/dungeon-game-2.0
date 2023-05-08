#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL.h>
#include <string>
#include "Vector2D.h"

class Transform {

public:

    Transform(float x = 0, float y = 0, int width = 0, int height = 0, std::string textureID = "",
        SDL_RendererFlip flip = SDL_FLIP_NONE, float scaleX = 1.0f, float scaleY = 1.0f,
        float rotation = 0.0f, float scrollRatio = 0.0f) {

        X = x; Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        ScaleX = scaleX;
        ScaleY = scaleY;
        Rotation = rotation;
        TextureID = textureID;
        ScrollRatio = scrollRatio;
        Origin = new Vector2D((X + Width), (Y + Height / 2));
    }

    inline void TranslateX(float x) { X += x; }
    inline void TranslateY(float y) { Y += y; }
    inline void Translate(Vector2D v) { X += v.X; Y += v.Y; }


public:

    float X, Y;
    float Rotation;
    Vector2D* Origin;
    float ScrollRatio;
    int Width, Height;
    float ScaleX, ScaleY;
    SDL_RendererFlip Flip;
    std::string TextureID;
};

#endif // TRANSFORM_H

