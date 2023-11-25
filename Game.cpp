#include "Game.h"
#include <fstream>
#include <iostream>
Game::Game(const std::string & config)
{
    init(config);
}

void Game::init(const std::string & path)
{
    std::ifstream fin(path);
    std::string configType;
    while(fin >> configType)
    {
        if(configType == "Window")
        {
            int winWidth;
            int winHeight;
            int frameLimit;
            int fullscreen;
            fin >> winWidth >> winHeight >> frameLimit >> fullscreen;

            if(fullscreen == 0)
            {
                m_window.create(sf::VideoMode(winWidth , winHeight), "Game");   
            }else
            {
                m_window.create(sf::VideoMode(winWidth , winHeight), "Game",sf::Style::Fullscreen);
            }
            m_window.setFramerateLimit(frameLimit);
            std::cout << "Window Successfull loaded!" << std::endl;
        }
        else if(configType == "Player")
        {
            fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG
            >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT
            >> m_playerConfig.V;
            std::cout << "Player Successfull loaded!" << std::endl;
        }
        else if(configType == "Bullet")
        {
            fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG
            >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT
            >> m_bulletConfig.V >> m_bulletConfig.L;
            std::cout << "Bullet Successfull loaded!" << std::endl;
        }
        else if(configType == "Enemy")
        {
            fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMAX >> m_enemyConfig.SMAX >> m_enemyConfig.OR
            >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
            >> m_enemyConfig.L >> m_enemyConfig.SI;
            std::cout << "Enemy Successfull loaded!" << std::endl;
        }
        else if(configType == "Font")
        {
            std::string fontPath;
            int fontSize, fontR, fontG, fontB;
            fin >> fontPath >> fontSize >> fontR >> fontG >> fontB;
            m_font.loadFromFile(fontPath);
            m_text.setCharacterSize(fontSize);
            m_text.setFillColor(sf::Color(fontR, fontG, fontB));
            std::cout << "Font Successfull loaded!" << std::endl;
        }

    }
    // Generate new random seed
    srand(static_cast <unsigned> (time(0)));
    spawnPlayer();

}

void Game::spawnPlayer()
{
    auto entity = m_entities.addEntity("Player");
    
    entity->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f), Vec2(1.0f, 1.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), 
    sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::spawnEnemy()
{
    auto entity = m_entities.addEntity("Enemy");
    
    float eSpeedX = m_enemyConfig.SMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX / (m_enemyConfig.SMAX-m_enemyConfig.SMIN))));
    float eSpeedY = m_enemyConfig.SMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX / (m_enemyConfig.SMAX-m_enemyConfig.SMIN))));
    // Pos are set to - 50 from max size of window to prevent them from spawning directly on the edge
    entity->cTransform = std::make_shared<CTransform>(Vec2( rand() % m_window.getSize().x - 50, rand() % m_window.getSize().y - 50), Vec2(eSpeedX, eSpeedY), 0.0f);

    int vertices = rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1) + m_enemyConfig.VMIN;
    int r = rand() % (255 - 0 + 1) + 0;
    int g = rand() % (255 - 0 + 1) + 0;
    int b = rand() % (255 - 0 + 1) + 0;

    entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(r, g, b), 
    sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

    // Keep track of frame when an enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;

}

void Game::sEnemySpawner()
{
    if(m_currentFrame - m_lastEnemySpawnTime > m_enemyConfig.SI)
    {
        spawnEnemy();
    }
}

void Game::sRender()
{
    m_window.clear();
    int winWidthTest = m_window.getSize().x;
    int winHeightTest = m_window.getSize().y;
    // Set Pos of player
    for(auto& e : m_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }
    m_window.display();

}

void Game::run()
{
    while(m_running)
    {
        m_entities.update();
        sEnemySpawner();
        sRender();
        m_currentFrame++;

        //Test Case
        if(m_currentFrame == 30000)
        {
            m_running = false;
        }
    }    
}


// void Game::configLoadTest()
// {
//     std::cout << "Enemy Properties: ";
//     std::cout << m_enemyConfig.SR << " " << m_enemyConfig.CR << " "  << m_enemyConfig.SMAX << " "  << m_enemyConfig.SMAX << " "  << m_enemyConfig.OR
//     << " " << m_enemyConfig.OG << " "  << m_enemyConfig.OB << " "  << m_enemyConfig.OT << " "  << m_enemyConfig.VMIN << " "  << m_enemyConfig.VMAX
//     << " " << m_enemyConfig.L << " "  << m_enemyConfig.SI << std::endl;

//     std::cout << "Bullet Properties: ";
//     std::cout << m_bulletConfig.SR << " " << m_bulletConfig.CR << " "  << m_bulletConfig.S << " "  << m_bulletConfig.FR << " "  << m_bulletConfig.FG
//     << " " << m_bulletConfig.FB << " "  << m_bulletConfig.OR << " "  << m_bulletConfig.OG << " "  << m_bulletConfig.OB << " "  << m_bulletConfig.OT
//     << " " << m_bulletConfig.V << " " << m_bulletConfig.L << std::endl;

//     std::cout << "Player Properties: ";
//     std::cout << m_playerConfig.SR << " " << m_playerConfig.CR << " "  << m_playerConfig.S << " "  << m_playerConfig.FR << " "  << m_playerConfig.FG
//     << " " << m_playerConfig.FB << " "  << m_playerConfig.OR << " "  << m_playerConfig.OG << " "  << m_playerConfig.OB << " "  << m_playerConfig.OT
//     << " " << m_playerConfig.V << std::endl;
// }