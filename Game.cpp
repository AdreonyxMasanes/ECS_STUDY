#include "Game.h"
#include <fstream>
#include <iostream>
#include <math.h>
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
            if(!m_font.loadFromFile(fontPath));
            {
                std::cout << "Font not Found" << std::endl;
            }
            m_text.setFont(m_font);
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
    entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

    m_player = entity;
}

void Game::spawnEnemy()
{
    auto entity = m_entities.addEntity("Enemy");
    
    float randSpeed = m_enemyConfig.SMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX / (m_enemyConfig.SMAX-m_enemyConfig.SMIN))));
    // Rand float pos between 0 and max window width minus 50
    float randPosX = static_cast <float> (rand() / (static_cast <float> (RAND_MAX / (m_window.getSize().x - 50))));
    float randPosY = static_cast <float> (rand() / (static_cast <float> (RAND_MAX / (m_window.getSize().y - 50))));
    Vec2 eSpeed(rand() % m_window.getSize().x - 50, rand() % m_window.getSize().y - 50);
    eSpeed.normalize();
    eSpeed *= randSpeed;
    // Pos are set to - 50 from max size of window to prevent them from spawning directly on the edge
    entity->cTransform = std::make_shared<CTransform>(Vec2( randPosX, randPosY), eSpeed, 0.0f);

    int vertices = rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1) + m_enemyConfig.VMIN;
    int r = rand() % (255 - 0 + 1) + 0;
    int g = rand() % (255 - 0 + 1) + 0;
    int b = rand() % (255 - 0 + 1) + 0;

    entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(r, g, b), 
    sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

    entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
    entity->cScore = std::make_shared<CScore>(vertices * 100);
    std::cout << "EnemyID" << entity->getId() << "X:" << entity->cTransform->pos.x << std:: endl;
    std::cout << "EnemyID" << entity->getId() << "Y:" << entity->cTransform->pos.y << std:: endl;
    // Keep track of frame when an enemy was spawned
    m_lastEnemySpawnTime = m_currentFrame;

}

void Game::spawnBullet(std::shared_ptr<Entity>  & entity, const Vec2 & mousePos)
{
    Vec2 directionVector = mousePos - m_player->cTransform->pos;
    directionVector.normalize();
    directionVector *= m_bulletConfig.S;
    
    Vec2 playerPos(m_player->cShape->circle.getPosition().x, m_player->cShape->circle.getPosition().y);
    entity->cTransform = std::make_shared<CTransform>(playerPos, directionVector, 0.0f);

    entity->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, 
    sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
    sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
    entity->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
    entity->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);

}

void Game::sUserInput()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if(event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::W :
                    m_player->cInput->isUp = true;
                    break;
                case sf::Keyboard::S :
                    m_player->cInput->isDown = true;
                    break;
                case sf::Keyboard::A :
                    m_player->cInput->isLeft = true;
                    break;
                case sf::Keyboard::D :
                    m_player->cInput->isRight = true;
                    break;
                case sf::Keyboard::P :
                    m_paused = !m_paused;
                        break;
                case sf::Keyboard::Escape :
                    m_running = false;
                    break;
                default: break;
            }
        }

        if(event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::W :
                    m_player->cInput->isUp = false;
                    break;
                case sf::Keyboard::S :
                    m_player->cInput->isDown = false;
                    break;
                case sf::Keyboard::A :
                    m_player->cInput->isLeft = false;
                    break;
                case sf::Keyboard::D :
                    m_player->cInput->isRight = false;
                    break;
                default: break;
            }
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
           Vec2 mousePos(event.mouseButton.x, event.mouseButton.y);
           std::shared_ptr<Entity> bullet = m_entities.addEntity("Bullet");
           std::cout << "MouseX: " << mousePos.x << std::endl;
           std::cout << "MouseY: " << mousePos.y << std::endl;
           spawnBullet(bullet, mousePos);
        }

    }
}

void Game::sMovement()
{
    m_player->cTransform->velocity = {0.0f, 0.0f};
    Vec2 playerSpeed(m_window.getSize().x, m_window.getSize().y);
    playerSpeed.normalize();
    playerSpeed *= m_playerConfig.S;

    if(m_player->cInput->isUp)
    {
        m_player->cTransform->velocity.y = playerSpeed.y * -1.0f;
    }
    if(m_player->cInput->isDown)
    {
        m_player->cTransform->velocity.y = playerSpeed.y;
    }
    if(m_player->cInput->isLeft)
    {
        m_player->cTransform->velocity.x = playerSpeed.x * -1.0f;
    }
    if(m_player->cInput->isRight)
    {
        m_player->cTransform->velocity.x = playerSpeed.x;
    }

    for(auto &e : m_entities.getEntities())
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
}

void Game::sEnemySpawner()
{
    m_activeEnemies = m_entities.getEntities("Enemy").size();

    std::cout << "Active Enemies: " << m_activeEnemies << std::endl;
    if(m_currentFrame - m_lastEnemySpawnTime > m_enemyConfig.SI)
    {
        if(m_activeEnemies < 15)
        {
            spawnEnemy();
        }
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
        if(e->cLifespan)
        {
            int FR = e->cShape->circle.getFillColor().r;
            int FG = e->cShape->circle.getFillColor().g;
            int FB = e->cShape->circle.getFillColor().b;

            int OR = e->cShape->circle.getOutlineColor().r;
            int OG = e->cShape->circle.getOutlineColor().g;
            int OB = e->cShape->circle.getOutlineColor().b;
            float alphaPercent =  (static_cast <float> (e->cLifespan->remaining) / static_cast <float> (e->cLifespan->initial));
            float alpha = alphaPercent * 255;
            e->cShape->circle.setFillColor(sf::Color(FR,FG,FB,alpha));
            e->cShape->circle.setOutlineColor(sf::Color(OR, OG, OB, alpha));
        }
        m_text.setString("Score: " + std::to_string(m_score));
        m_window.draw(e->cShape->circle);
        m_window.draw(m_text);
    }
    m_window.display();

}

void Game::sCollison()
{
    for(auto &b : m_entities.getEntities("Bullet"))
    {
        for(auto &e : m_entities.getEntities("Enemy"))
        {
            Vec2 diffVector = e->cTransform->pos - b->cTransform->pos;
            float distance = diffVector.length();
            if(distance < e->cCollision->radius + b->cCollision->radius)
            {
                m_score += e->cScore->score;
                e->destroy();
            }
        }
    }
    for(auto &e : m_entities.getEntities("Enemy"))
    {
        if(e->cTransform->pos.x >= m_window.getSize().x || e->cTransform->pos.x <= 0)
        {
            e->cTransform->velocity.x *= -1.0f;
        }
        if(e->cTransform->pos.y >= m_window.getSize().y || e->cTransform->pos.y <= 0)
        {
            e->cTransform->velocity.y *= -1.0f;
        }

        if(e->cTransform->pos.distance(m_player->cTransform->pos) < e->cCollision->radius + m_player->cCollision->radius)
        {
            m_player->cTransform->pos = Vec2(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
        }
    }
}

void Game::sLifespan()
{
    for(auto &b: m_entities.getEntities("Bullet"))
    {
        if(b->cLifespan->remaining == 0)
        {
            b->destroy();
        }
        else
        {
            b->cLifespan->remaining--;
        }
    }
}

void Game::run()
{
    while(m_running)
    {
        m_entities.update();
        
        
        if(!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollison();
            sLifespan();
        }
        sUserInput();
        sRender();
        m_currentFrame++;
    }    
}

