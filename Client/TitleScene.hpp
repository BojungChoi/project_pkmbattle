#pragma once
#include "BaseScene.hpp"


class TitleScene : public BaseScene {
private:
    sf::Font font;
    sf::Text title;

public:
    TitleScene() : font("C:/Windows/Fonts/arial.ttf"), title(font, "PKM BATTLE", 60) {} // ���� �ڽ��� ��Ʈ �� �ν��� ���� ��

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
