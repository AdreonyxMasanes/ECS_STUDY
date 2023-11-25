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

            if(fullscreen == 1)
            {
                m_window.create(sf::VideoMode(winWidth , winHeight), "Game");   
            }else
            {
                m_window.create(sf::VideoMode(winWidth , winHeight), "Game",sf::Style::Fullscreen);
            }
            m_window.setFramerateLimit(frameLimit);
            std::cout << "Window Successfull loaded!" << std::endl;

            std::cout << "Window Properties: " << winWidth << " " << winHeight << " " << frameLimit << " " << fullscreen << std::endl;
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