#pragma once
#include "pch.h"
#include "KeyManager.h"
#include "BaseScene.hpp"
#include "SceneManager.h"
#include "LoginScene.hpp"
#include "UIButton.hpp"
#include "UIManager.hpp"

class TitleScene : public BaseScene {
private:
    sf::Font font;
    sf::Text title;
    UIManager uiManager;
public:
    TitleScene() : font("C:/Windows/Fonts/arial.ttf"), title(font, "THIS IS TITLE", 60) {}

    void init() override {
        std::cout << "TitleScene::init() ȣ���\n";
        uiManager.addElement(new UIButton(
            { 300,400 },    // ��ư ��ġ 
            { 200,50 },     // ��ư ũ��
            "Start",        // ��ư �ؽ�Ʈ
            []() { SceneManager::getInstance().changeScene(new LoginScene()); } // command
        ));

        title.setFillColor(sf::Color::White);
        title.setPosition({ 200, 250 });
    }

    void update(sf::RenderWindow& window) override {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            KeyManager::getInstance().handleEvent(*event);
            uiManager.handleEvent(*event);
        }
        uiManager.update();
    }


    void render(sf::RenderWindow& window) override {
        window.draw(title);
        uiManager.render(window);
    }

};
