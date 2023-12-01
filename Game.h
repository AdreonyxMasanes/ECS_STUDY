#pragma once
#include "EntityManager.h"
#include "Assets.h"

struct PlayerConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig {int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
struct BulletConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};


class Game
{
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_text;
    std::shared_ptr<Entity> m_player;
    EntityManager m_entities;
    Assets m_assets;

    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;

    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    int m_activeEnemies = 0;
    bool m_paused = false;
    bool m_running = true;

    void init(const std::string &  config);
    void loadAssets(const std::string & config);
    void update();
    void setPaused(bool paused); 
    

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity>  & entity, const Vec2 & mousePos);
    void spawnSpecialMove(std::shared_ptr<Entity> & entity);

    void sMovement();
    void sUserInput();
    void sRender();
    void sEnemySpawner();
    void sCollison();
    void sLifespan();
    void sAnimation();
    public:
    Game(const std::string & config, const std::string & assets);
    void run();
    // void configLoadTest();  
    
};