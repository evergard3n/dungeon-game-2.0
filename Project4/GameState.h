#ifndef STATES_H
#define STATES_H

#include <SDL.h>
#include <iostream>

const SDL_Color SKYBLUE = { 30, 191, 242 };
const SDL_Color SKYDARK = { 45, 80, 82 };

class GameState {

public:
    virtual bool Init() = 0;
    virtual bool Exit() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    SDL_Color m_ClearColor;
    SDL_Renderer* m_Ctxt;
};

#endif // STATES_H
