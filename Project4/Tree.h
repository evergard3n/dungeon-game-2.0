#ifndef TREE_H
#define TREE_H

#include "Helper.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "ObjectFactory.h"
#include "SeqAnimation.h"

class Tree : public GameObject {

public:
    Tree(Transform* tf) :GameObject(tf) {
        TextureMgr::Instance()->QueryTexture(tf->TextureID, &m_Tf->Width, &m_Tf->Height);
    }

    virtual void Update(float dt) override {
        //m_CurrFrame = (Uint8)((SDL_GetTicks()/1000) % 2);
        //m_Tf->TextureID = (m_CurrFrame == 0)? "tree2" : "tree2";
    }

private:
    Uint8 m_CurrFrame;

};

static Registrar<Tree> tree("TREE");

#endif // TREE_H
#pragma once
