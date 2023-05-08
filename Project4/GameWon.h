

#include "GameState.h"
#include "GameObject.h"
#include "Parser.h"
#include <vector>

class GameWon : public GameState {

public:
    GameWon();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();


private:
    static void StartGame();
    static void QuitGame();
    static void Settings();

private:
    std::vector<GameObject*> m_GuiObjects;
};


