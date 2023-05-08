#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "Engine.h"
#include "Vector2D.h"

class Camera {

public:

    void TrackTarget();

    void TranslateX(int x);
    void TranslateY(int y);
    void Translate(Vector2D target);

    void SetPositionX(int targetX);
    void SetPositionY(int targetY);
    void SetPosition(Vector2D target);

    bool GetInsectionWithViewPort(const SDL_Rect* rect);

    inline const int GetMapWidth() { return m_MapWidth; }
    inline const int GetMapHeight() { return m_MapHeight; }

    inline const SDL_Rect GetViewPort() { return m_ViewPort; }
    inline const Vector2D GetPosition() { return m_Position; }

    inline void SetTarget(Vector2D* target) { m_Target = target; }
    inline void SetViewPort(SDL_Rect viewport) { m_ViewPort = viewport; }
    inline void SetMapLimit(int w, int h) { m_MapWidth = w; m_MapHeight = h; }
    inline static Camera* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

private:

    Camera();
    Vector2D* m_Target;
    Vector2D m_Position;
    SDL_Rect m_ViewPort;
    static Camera* s_Instance;
    int m_MapWidth, m_MapHeight;
};

#endif // CAMERA_H
