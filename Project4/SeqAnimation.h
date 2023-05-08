#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Transform.h"

struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<const char*> TextureIDs;
};

class SeqAnimation : public Animation {

public:
    SeqAnimation(bool repeat = true);

    virtual void Update(float dt);
    void DrawFrame(Transform* tf);
    void Parse(std::string source);
    void SetCurrentSeq(std::string seqID);

private:
    Sequence m_CurrentSeq;
    std::map<std::string, Sequence> m_SeqMap;
};

#endif // SEQANIMATION_H
