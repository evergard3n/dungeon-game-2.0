#include "Play.h"
#include "Menu.h"
#include "GameOver.h"
#include "Button.h"
#include "Helper.h"
#include <SDL_mixer.h>

int temp = 0;
Play::Play() {}
float absolute(float a, float b)
{
    if (a - b >= 0) return a - b;
    else return b - a;
}

bool Play::Init() {
    m_ClearColor = SKYBLUE;
    m_Ctxt = Engine::Instance()->GetRenderer();

    //Parser::Instance()->ParseTextures("assets/textures.tml");
    //Parser::Instance()->ParseTextures("assets/gui_textures.tml");
    m_TilelMap = Parser::Instance()->ParseMap("assets/maps/map.tmx");
    
    ShowInfo = false;
    
    TileLayer* layer = m_TilelMap->GetLayers().back();
    CollisionHandler::Instance()->SetCollisionLayer(layer);
    Camera::Instance()->SetMapLimit(layer->GetWidth(), layer->GetHeight());

    m_Player = new Warrior(new Transform(200, 500, 136, 96, "player_idle"));
    Camera::Instance()->SetTarget(m_Player->GetOrigin());
    
    
    menubtn = new Button(100, 50, OpenMenu, {"home_n", "home_h", "home_p"});
    font = TTF_OpenFont("textures2/HelveticaWorld-Regular.ttf", 24);
    TextureMgr::Instance()->Add("background", "textures2/map/bg full.jpg");
    m_EnemyWaveLeft = 5;
    spawnEnemy(GetEnemyNumberNextWave());
    //m_UiObjects.push_back(optbtn);
    m_UiObjects.push_back(menubtn);
    music = Mix_LoadMUS("assets/sounds/valley.ogg");
    if (music == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());

    }
    Mix_PlayMusic(music, -1);
    return true;
}

void Play::Render() {

    SDL_SetRenderDrawColor(m_Ctxt, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    SDL_RenderClear(m_Ctxt);
    TextureMgr::Instance()->Draw(new Transform(0, 0, 1980, 1020, "background",SDL_FLIP_NONE,1,1,0,0.5));
    //TextureMgr::Instance()->Draw(new Transform(0, 0, 1980, 1020, "enemies_idle", SDL_FLIP_NONE, 1, 1, 0, 0.5));
    if (ShowInfo) {
        //SDL_Rect m_Something = { 200 , 50, 500,100 };
        //SDL_RenderFillRect(m_Ctxt, &m_Something);
        TextureMgr::Instance()->LoadText("text", "Enemies Waves Left: " + s, 210, 53, {0,0,0,255}, font);
        TextureMgr::Instance()->LoadText("text2", "Enemies Left This Wave: " + s2, 210, 53 + 30, { 0,0,0,255 }, font);
    }

    m_TilelMap->Render();
    m_Player->Draw();
    for (auto& it : m_Enemies) {
        int id = it.first;
        Enemy* enemies = it.second;
        enemies->Draw();
    }
    for (auto object : m_UiObjects)
        object->Draw();
    //std::cout << m_Enemy->GetId() << std::endl;
    if (m_Player->m_IsDead) {
        TextureMgr::Instance()->LoadText("text2", "NIGGA", 200, 200, {0,0,0,255}, font);
    }
    SDL_RenderPresent(m_Ctxt);
}

inline int Play::GetEnemyNumberNextWave()
{
   
    


        switch (m_EnemyWaveLeft)
        {
        case(5):
        {
            m_ThisWaveEnemy = 5;
            break;
        }
        case(4):
        {
            m_ThisWaveEnemy = 8;
            break;
        }
        case(3):
        {
            m_ThisWaveEnemy = 10;
            break;
        }
        case(2):
        {   m_ThisWaveEnemy = 13;
        break;
        }
        case(1):
        {
            m_ThisWaveEnemy = 16;
            break;
        }
        case(0):
        {
            m_ThisWaveEnemy = 20;
            break;
        }
        default:
        {
            m_ThisWaveEnemy = 0;
            break;
        }
        }
        return m_ThisWaveEnemy;

    

}

void Play::spawnEnemy(int n)
{
    for (int i = 1; i <= n; i++) {
        srand(time(0));
        
        int x = Helpers::RandI(3, 200) + 300 * i;

        Enemy* enemy = new Enemy(new Transform(x % 2500, 435,48,48,"enemies_idle"));
        addCharacter(enemy);
    }
}

Vector2D Play::GetPlayerPos()
{
    Vector2D temp;
    
    return temp;
}



void Play::Update() {
    
    s = std::to_string(m_EnemyWaveLeft);
    s2 = std::to_string(m_ThisWaveEnemy - temp);
    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_Player->Update(dt);
    //m_Enemy->Update(dt);
    std::vector<int> m_removedIds;
    Camera::Instance()->TrackTarget();
    if (CollisionHandler::Instance()->ConditionCollision(m_Player->m_Collider->Get(), m_TilelMap->GetLayers().front()) == 615) {
        //std::cout << "YES" << std::endl;
        m_Player->m_HPcap = 200;
        m_Player->m_HealthPoint = 200;
    }
    for (auto& it : m_Enemies) {
        int id = it.first;
        Enemy* enemies = it.second;
        if (enemies->IsDead()) {
            m_removedIds.push_back(id);
            m_Player->m_HealthPoint += 10;
            temp++;
            if (temp == m_ThisWaveEnemy && m_EnemyWaveLeft >= 0) {
                m_EnemyWaveLeft--;
                temp = 0;
                m_removedIds.clear();
                spawnEnemy(GetEnemyNumberNextWave());
                temp--;
            }
        }
    }
    for (auto& id : m_removedIds) {
        removeCharacter(m_Enemies[id]);
    }
    for (auto& it : m_Enemies) {
        int id = it.first;
        Enemy* enemies = it.second;

        if (!enemies->IsDead()) {
            if (WavesLeft() > 3) {
                enemies->m_HealthPoint;
                enemies->m_Damage = 0.06;
            }
            else if (WavesLeft() == 3) {
                enemies->m_HealthPoint = enemies->m_HealthPoint *1.5;
                enemies->m_Damage = 0.08;
            }
            else {
                enemies->m_HealthPoint = enemies->m_HealthPoint * 2;
                enemies->m_Damage = 0.015;
            }
            if (absolute((m_Player->m_Tf->X+60), enemies->m_Tf->X) <= 32 * 5) {
                if ((m_Player->m_Tf->X+60) == enemies->m_Tf->X) {
                    enemies->m_IsIdle = true;
                    enemies->m_IsWalking = false;
                    enemies->m_EneRigidbody->UnSetForce();
                    
                    enemies->m_Tf->TextureID = "enemies_idle";
                    enemies->m_Animation->SetProps(0, 4, 100);
                }
                if ((m_Player->m_Tf->X+60) < enemies->m_Tf->X) {
                    
                    enemies->m_IsWalking = true;
                    enemies->m_Tf->TextureID = "enemies_walking";
                    enemies->m_Animation->SetProps(0, 6, 100);
                    enemies->m_EneRigidbody->ApplyForceX(2 * BACKWARD);
                    enemies->m_Tf->Flip = SDL_FLIP_NONE;
                    std::cout << "No" << std::endl;
                }

                if ((m_Player->m_Tf->X+60) > enemies->m_Tf->X) {
                    
                    enemies->m_IsWalking = true;
                    enemies->m_Tf->TextureID = "enemies_walking";
                    enemies->m_Animation->SetProps(0, 6, 100);
                    enemies->m_EneRigidbody->ApplyForceX(2 * FORWARD);
                    enemies->m_Tf->Flip = SDL_FLIP_HORIZONTAL;
                    std::cout << "Yes" << std::endl;
                }

            }
            else
            {
                enemies->m_EneRigidbody->UnSetForce();
                enemies->m_IsIdle = true;
                enemies->m_Tf->TextureID = "enemies_idle";
                enemies->m_Animation->SetProps( 0, 4, 100);
                
            }
            if (CollisionHandler::Instance()->CheckCollision(enemies->m_Collider->Get(), m_Player->m_Collider->Get())) {
                enemies->m_EneRigidbody->UnSetForce();
                if (m_Player->m_IsAttacking == false) {
                    enemies->m_IsAttacking = true;
                    enemies->m_Animation->SetProps( 0, 4, 100);
                    enemies->m_Tf->TextureID = "enemies_attacking";
                    //Engine::GetInstance()->GetPlayer()->m_HealthPoint -= m_Damage;
                    m_Player->m_HealthPoint -= enemies->m_Damage;
                }
                else {
                    enemies->m_IsAttacking = false;
                    enemies->m_Animation->SetProps( 0, 2, 400);
                    enemies->m_Tf->TextureID = "enemies_hurt";
                    enemies->m_HealthPoint -= 2.0;
                }

            }
            enemies->Update(dt);
        }
        
        //std::cout << m_Enemy->GetId() << m_Enemy2->GetId() << std::endl;
        m_TilelMap->Update();
        //m_Enemy->m_IsWalking = true;

        for (auto object : m_UiObjects)
            object->Update(dt);
        if(m_Player->m_IsDead) StateMgr::Instance()->PushState(new GameOver());
        if (m_EnemyWaveLeft == -1) OpenMenu();
        //m_Enemy->m_IsAttacking = true;
        //rEmttr->UpdateParticles(dt);
    }
}

void Play::addCharacter(Enemy* enemy)
{
    m_Enemies[enemy->GetId()] = enemy;
}

void Play::removeCharacter(Enemy* enemy)
{
    m_Enemies.erase(enemy->GetId());
}

void Play::Events() {

    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        StateMgr::Instance()->PushState(new Menu());

    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_P))
        ShowInfo = true;
    if (Input::Instance()->GetKeyDown(SDL_SCANCODE_O))
        ShowInfo = false;
    
}

bool Play::Exit() {
    m_GameObjects.clear();
    TextureMgr::Instance()->Clean();
    return true;
}

void Play::OpenMenu() {
    StateMgr::Instance()->PushState(new Menu());
    
}

void Play::Options() {
    std::cout << "open option" << std::endl;
}

void Play::QuitGame()
{
    Engine::Instance()->Close();
}
