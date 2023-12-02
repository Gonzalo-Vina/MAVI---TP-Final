#pragma once

#include <stdio.h>
#include <tchar.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Player {
	Texture textureCrosshair;
	Sprite spriteCrosshair;

public:
	Player() {
		textureCrosshair.loadFromFile("assets/crosshair.png");
		spriteCrosshair.setTexture(textureCrosshair);
		spriteCrosshair.setOrigin(16, 16);


		/*textureCrosshair.loadFromFile("assets/Enemy_1.png");
		spriteCrosshair.setTexture(textureCrosshair);
		spriteCrosshair.setOrigin(32, 42);
		spriteCrosshair.setScale(2, 2);*/
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(spriteCrosshair);
	}

	void Posicionar(Vector2i mousePosition) {
		spriteCrosshair.setPosition(mousePosition.x, mousePosition.y);
	}

	Vector2f GetPosition() {
		return spriteCrosshair.getPosition();
	}
};