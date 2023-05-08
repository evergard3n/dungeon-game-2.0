#include "SeqAnimation.h"
#include "tinyxml1.h"
#include "iostream"

SeqAnimation::SeqAnimation(bool repeat) :Animation(repeat) {}

void SeqAnimation::DrawFrame(Transform* tf) {
    tf->TextureID = m_CurrentSeq.TextureIDs[m_CurrentFrame];
    tf->Width = m_CurrentSeq.Width;
    tf->Height = m_CurrentSeq.Height;
    TextureMgr::Instance()->Draw(tf);
}

void SeqAnimation::Update(float dt) {
    m_CurrentFrame = (SDL_GetTicks() / m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
}

void SeqAnimation::SetCurrentSeq(std::string seqID) {
    if (m_SeqMap.count(seqID) > 0)
        m_CurrentSeq = m_SeqMap[seqID];
    else
        std::cout << "The given Sequence animation is not matching: " << seqID << std::endl;
}

void SeqAnimation::Parse(std::string source) {

    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error())
        std::cout << "Failed to load animation file: " << source << std::endl;

    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("sequence")) {
            Sequence seq;
            std::string seqID = e->Attribute("id");
            e->Attribute("speed", &seq.Speed);
            e->Attribute("width", &seq.Width);
            e->Attribute("height", &seq.Height);
            e->Attribute("frameCount", &seq.FrameCount);

            for (TiXmlElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
                seq.TextureIDs.push_back(frame->Attribute("textureID"));

            m_SeqMap[seqID] = seq;
        }
    }
}
