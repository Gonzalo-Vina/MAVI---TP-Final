#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy {
	Texture textureEnemy_1;
	Texture textureEnemy_2;
	Texture textureEnemy_3;
	Texture textureEnemy_4;

	Sprite spriteEnemy;

	

public:
	Enemy(int numberTexture) {
		textureEnemy_1.loadFromFile("assets/Enemy_1.png");
		textureEnemy_2.loadFromFile("assets/Enemy_2.png");
		textureEnemy_3.loadFromFile("assets/Enemy_3.png");
		textureEnemy_4.loadFromFile("assets/Enemy_4.png");

		//Colocamos la textura dependiendo del enemigo elegido
		switch (numberTexture)
		{
		case 0:
			spriteEnemy.setTexture(textureEnemy_1);
			break;

		case 1:
			spriteEnemy.setTexture(textureEnemy_2);
			break;

		case 2:
			spriteEnemy.setTexture(textureEnemy_3);
			break;

		case 3:
			spriteEnemy.setTexture(textureEnemy_4);
			break;

		default:
			break;
		}

		spriteEnemy.setOrigin(32,42);
		spriteEnemy.setScale(2, 2);

		_isAttacking = false;
		_fired = true;
	}

	bool _isAttacking;
	bool _fired;

	bool CheckCollision(float x, float y) {
		FloatRect bounds = spriteEnemy.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(spriteEnemy);
	}

	bool IsAttacking() {
		return _isAttacking;
	}

	void SetPosition(Vector2f newPosition) {
		spriteEnemy.setPosition(newPosition);
	}
};
