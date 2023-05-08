#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL.h>
#include "IObject.h"
#include "Transform.h"
#include "TextureManager.h"
class GameObject : public IObject {

public:
    GameObject(Transform* tf) : m_Tf(tf) {
        m_Id = S_n;
        S_n++;
    }

    virtual void Draw() {
        TextureMgr::Instance()->Draw(m_Tf);
    }

    virtual void Update(float dt) {
        m_Tf->Origin->X = m_Tf->X + m_Tf->Width / 2;
        m_Tf->Origin->Y = m_Tf->Y + m_Tf->Height / 2;
    }

    virtual void Clean() {}

    inline Vector2D* GetOrigin() { return m_Tf->Origin; }
    virtual int GetId() { return m_Id; }

protected:
    Transform* m_Tf;
    int m_Id;
    static int S_n;
};


#endif // GAMEOBJECT_H
