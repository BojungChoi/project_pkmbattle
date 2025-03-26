#pragma once
#include "BaseScene.hpp"


class LoginScene : public BaseScene {
private:
    sf::Font font;
    sf::Text title;

public:
    LoginScene() : font("C:/Windows/Fonts/arial.ttf"), title(font, "LOGIN SCENE", 60) {} 

    void init() override {
        title.setFillColor(sf::Color::White);
        title.setPosition({ 200, 250 });
    }

    void update(sf::RenderWindow& window) override {
        // Ű �Է� �޾Ƽ� �� ��ȯ ó�� ����
    }

    void render(sf::RenderWindow& window) override {
        window.draw(title);
    }
};
