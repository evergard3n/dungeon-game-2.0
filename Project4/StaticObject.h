#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "SDL.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "ObjectFactory.h"

class StaticObject : public GameObject {

public:
    StaticObject(Transform* tf) : GameObject(tf) {
        TextureMgr::Instance()->QueryTexture(tf->TextureID, &m_Tf->Width, &m_Tf->Height);
    }
};

static Registrar<StaticObject> sobject("SOBJECT");

#endif // STATICOBJECT_H

#pragma once
