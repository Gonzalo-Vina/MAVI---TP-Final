#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Innocent {
	Texture textureInnocent;
	Sprite spriteInnocent;

	

public:
	Innocent(){
		textureInnocent.loadFromFile("assets/Innocent.png");
		spriteInnocent.setTexture(textureInnocent);
		spriteInnocent.setOrigin(32, 42);
		spriteInnocent.setScale(2, 2);

		isVisible = false;
	}

	bool isVisible;

	bool CheckCollision(float x, float y) {
		FloatRect bounds = spriteInnocent.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(spriteInnocent);
	}

	void SetPosition(Vector2f newPosition) {
		spriteInnocent.setPosition(newPosition);
	}
};