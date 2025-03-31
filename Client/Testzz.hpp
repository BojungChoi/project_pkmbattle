#pragma once

#include "pch.h"
#include "KeyManager.h"
#include "BaseScene.hpp"
#include "SceneManager.hpp"
#include "LoginScene.hpp"
#include "worldScene.hpp"
#include "AnimatedObject.hpp"
#include "AnimationManager.hpp"
#include "UIButton.hpp"
#include "UITextBox.hpp"
#include "UIManager.hpp"
#include "Player.h"
#include "ResourceManager.hpp"
#include "NetworkManager.hpp"
#include "GameManager.h"

class Testzz : public BaseScene {
public:
    Testzz() {}

    void init() override {
        // �ʱ�ȭ ���� ����
        std::cout << "[TestScene] init() ȣ���\n";
    }

    void handleInput(const sf::Event& event, sf::RenderWindow& window) override {
        // ����������� �׽�Ʈ��
        if (KeyManager::getInstance().isKeyPressed(sf::Keyboard::Key::F5)) {
            SceneManager::getInstance().changeScene("world");
        }
 /*       if (KeyManager::getInstance().isKeyDown(sf::Keyboard::Key::Num1) && selectCooldown <= 0.f) {
            selectOverlay.toggle();
            selectOverlay.setCenter(camera.getCenter());
            std::cout << "SelectOverlay Visible: " << selectOverlay.isVisible() << "\n";
            selectCooldown = 0.5f;
        }*/
    }

    void update(sf::RenderWindow& window) override {
        // �ƹ� ������Ʈ�� �� ��
    }

    void render(sf::RenderWindow& window) override {
        // �׳� �Ͼ� ������� Ŭ���
        window.clear(sf::Color::White);
        // �߰� ���� ����
    }
};
