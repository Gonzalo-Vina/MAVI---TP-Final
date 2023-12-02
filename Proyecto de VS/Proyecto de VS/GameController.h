#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Enemy.h"
#include "Innocent.h"


using namespace sf;

class GameController {

    RenderWindow* _wnd;

    Texture textureBackground_0;
    Texture textureBackground_1;
    Texture textureBackground_2;
    Texture textureBackground_3;
    Texture textureBackground_4;
    Texture textureBackground_5;

    Texture textureBANG;
    Texture textureGAMEOVER;

    Sprite spriteBackground;
    Sprite spriteBANG;
    Sprite spriteGAMEOVER;

    Vector2f* positionsToSpawn[5];

    Player* _player;
    Enemy* _enemy;
    Innocent* _innocent;

    int _life, _defeated;
    Text puntajeLife, puntajeDefeated;
    Font font;

    sf::Clock enemyShotTime;
    sf::Clock targetPositionTime;
    sf::Clock bangTime;

    float _timeWithTarget;

    float _maxTimeWithoutTarget;

    bool isBang;
    bool isGameOver;

    void ActualizarPuntaje() {
        if (_life > 0) {
            puntajeLife.setString("Life: " + std::to_string(_life));
        }
        else {
            puntajeLife.setString("Life: " + std::to_string(_life));

            spriteBackground.setTexture(textureBackground_0);
            isGameOver = true;
        }

        puntajeDefeated.setString("Defeated: " + std::to_string(_defeated));
    }

public:
    GameController() {
        _wnd = new RenderWindow(VideoMode(640, 640), "Windows Game");
        _wnd->setMouseCursorVisible(false);
        _wnd->setFramerateLimit(60);

        _player = new Player();
        _innocent = new Innocent();
        _enemy = new Enemy(10);

        _life = 3;
        _defeated = 0;

        targetPositionTime.restart();

        _timeWithTarget = 3;
        _maxTimeWithoutTarget = 3;

        textureBackground_0.loadFromFile("assets/Background_0.png");
        textureBackground_1.loadFromFile("assets/Background_1.png");
        textureBackground_2.loadFromFile("assets/Background_2.png");
        textureBackground_3.loadFromFile("assets/Background_3.png");
        textureBackground_4.loadFromFile("assets/Background_4.png");
        textureBackground_5.loadFromFile("assets/Background_5.png");

        spriteBackground.setTexture(textureBackground_0);

        positionsToSpawn[0] = new Vector2f(140,150);
        positionsToSpawn[1] = new Vector2f(500,150);
        positionsToSpawn[2] = new Vector2f(115,355);
        positionsToSpawn[3] = new Vector2f(320,355);
        positionsToSpawn[4] = new Vector2f(520,355);

        textureBANG.loadFromFile("assets/Icon BANG.png");
        spriteBANG.setTexture(textureBANG);
        isBang = false;

        textureGAMEOVER.loadFromFile("assets/Icon GAMEOVER.png");
        spriteGAMEOVER.setTexture(textureGAMEOVER);
        isGameOver = false;

        font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

        puntajeLife.setPosition(50, 500);
        puntajeLife.setFont(font);
        puntajeLife.setColor(Color::White);
        puntajeLife.setCharacterSize(50.0f);

        puntajeDefeated.setPosition(50, 570);
        puntajeDefeated.setFont(font);
        puntajeDefeated.setColor(Color::White);
        puntajeDefeated.setCharacterSize(50.0f);

        ActualizarPuntaje();
    }

    void MainLoop() {
        while (_wnd->isOpen()) {
            ProcesarEventos();
            Actualizar();
            Dibujar();
        }
    }

    void ProcesarEventos() {
        Event evt;
        while (_wnd->pollEvent(evt)) {

            switch (evt.type)
            {
            case Event::Closed:
                _wnd->close();
                break;

            case Event::MouseButtonPressed:
                if (evt.mouseButton.button == Mouse::Button::Left) {
                    PlayerShot();
                }
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape) == true)
                _wnd->close();
        }
    }

    void Actualizar() {
        _player->Posicionar(Mouse::getPosition(*_wnd));

        TimeTargetPosition();

        if (!_enemy->_fired) {
            EnemyShot();
        }

        if (isGameOver)
            targetPositionTime.restart();
    }

    void PlayerShot() {
        if (_enemy->_isAttacking) {
            if (_enemy->CheckCollision(_player->GetPosition().x, _player->GetPosition().y)) {
                spriteBackground.setTexture(textureBackground_0);
                _enemy->SetPosition(Vector2f(0, 0));
                _enemy->_isAttacking = false;
                _enemy->_fired = true;

                targetPositionTime.restart();

                _defeated++;
            }
        }

        if (_innocent->isVisible) {
            if (_innocent->CheckCollision(_player->GetPosition().x, _player->GetPosition().y)) {
                spriteBackground.setTexture(textureBackground_0);
                _innocent->SetPosition(Vector2f(0, 0));
                _innocent->isVisible = false;

                targetPositionTime.restart();

                _life--;
            }
        }

        ActualizarPuntaje();
    }

    void EnemyShot() {
        if (enemyShotTime.getElapsedTime().asSeconds() > 1) {
            _enemy->_fired = true;
            _life--;
            ActualizarPuntaje();

            spriteBackground.setTexture(textureBackground_0);
            bangTime.restart();
            isBang = true;
        }
    }

    void Dibujar() {
        _wnd->clear();

        if (_enemy->_isAttacking) {
            _enemy->Dibujar(_wnd);
        }        

        if (_innocent->isVisible) {
            _innocent->Dibujar(_wnd);
        }

        _wnd->draw(spriteBackground);

        if (isGameOver) {
            isBang = false;
            _wnd->draw(spriteGAMEOVER);
        }

        if (isBang && bangTime.getElapsedTime().asSeconds() < 2) _wnd->draw(spriteBANG);

        _player->Dibujar(_wnd);        

        _wnd->draw(puntajeLife);
        _wnd->draw(puntajeDefeated);

        _wnd->display();
    }

    void SetEnemyAndBackground() {
        SelectTarget();

        switch (RandomNumberBetween(0,4))
        {
        case 0:
            spriteBackground.setTexture(textureBackground_1);
            _enemy->SetPosition(*positionsToSpawn[0]);
            _innocent->SetPosition(*positionsToSpawn[0]);
            break;
        case 1:
            spriteBackground.setTexture(textureBackground_2);
            _enemy->SetPosition(*positionsToSpawn[1]);
            _innocent->SetPosition(*positionsToSpawn[1]);
            break;
        case 2:
            spriteBackground.setTexture(textureBackground_3);
            _enemy->SetPosition(*positionsToSpawn[2]);
            _innocent->SetPosition(*positionsToSpawn[2]);
            break;
        case 3:
            spriteBackground.setTexture(textureBackground_4);
            _enemy->SetPosition(*positionsToSpawn[3]);
            _innocent->SetPosition(*positionsToSpawn[3]);
            break;
        case 4:
            spriteBackground.setTexture(textureBackground_5);
            _enemy->SetPosition(*positionsToSpawn[4]);
            _innocent->SetPosition(*positionsToSpawn[4]);
            break;
        default:
            break;
        }
    }

    void TimeTargetPosition() {
        if (!_enemy->_isAttacking && !_innocent->isVisible) {
            if (targetPositionTime.getElapsedTime().asSeconds() > _maxTimeWithoutTarget) {
                targetPositionTime.restart();
                SetEnemyAndBackground();

                isBang = false;
            }
        }
        else if (_enemy->_isAttacking || _innocent->isVisible) {
            if (targetPositionTime.getElapsedTime().asSeconds() > _timeWithTarget) {
                targetPositionTime.restart();

                spriteBackground.setTexture(textureBackground_0);

                _enemy->SetPosition(Vector2f(0, 0));
                _enemy->_isAttacking = false;
                _enemy->_fired = true;

                _innocent->SetPosition(Vector2f(0, 0));
                _innocent->isVisible = false;
            }
        }
    }

    int RandomNumberBetween(int min, int max) {
        int nRandom = ( min + rand() % (max + 1 - min));
        return nRandom;
    }

    void SelectTarget() {
        switch (RandomNumberBetween(0,4))
        {
        case 0:
            _enemy = new Enemy(0);
            _enemy->_isAttacking = true;
            enemyShotTime.restart();
            _enemy->_fired = false;

            _innocent->isVisible = false;
            break;
        case 1:
            _enemy = new Enemy(1);
            _enemy->_isAttacking = true;
            enemyShotTime.restart();
            _enemy->_fired = false;

            _innocent->isVisible = false;
            break;
        case 2:
            _enemy = new Enemy(2);
            _enemy->_isAttacking = true;
            enemyShotTime.restart();
            _enemy->_fired = false;

            _innocent->isVisible = false;
            break; 
        case 3:
            _enemy = new Enemy(3);
            _enemy->_isAttacking = true;
            enemyShotTime.restart();
            _enemy->_fired = false;

            _innocent->isVisible = false;
            break;
        case 4:
            _innocent->isVisible = true;
            _enemy->_isAttacking = false;
            break;
        default:
            break;
        }
    }

    ~GameController() {
        delete _enemy;
        delete _player;
        delete _wnd;
    }
};