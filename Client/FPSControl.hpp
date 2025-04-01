//#pragma once
//#include "BaseUI.hpp"
//#include "UIButton.hpp"
//#include "TimeManager.hpp"
//#include <functional>
//#include <vector>
//#include <memory> // unique_ptr ����� ���� ��� �߰�
//
//class FPSControl : public BaseUI {
//private:
//    sf::RectangleShape shape;
//    sf::Text text;  // FPS ǥ�� �ؽ�Ʈ
//    std::function<void(int)> onFpsChange; // FPS ���� �ݹ� �Լ�
//    sf::Font& font; // ��Ʈ ����
//    std::vector<std::unique_ptr<UIButton>> buttons; // FPS ���� ��ư��
//    sf::Color defaultColor;
//
//public:
//    // FPSControl ������
//    FPSControl(const std::string& label
//        , const sf::Vector2f& position
//        , const sf::Vector2f& size
//        , sf::Color Color
//        , sf::Font& sharedFont
//        , std::function<void(int)> fpsChangeFunc)
//        : font(sharedFont)
//        , text(sharedFont, label, 48)
//        , defaultColor(Color) 
//    {
//        // ��� ����
//        shape.setPosition(position);
//        shape.setSize(size);
//        shape.setFillColor(Color);
//
//        // FPS ǥ�� �ؽ�Ʈ ����
//        text.setFont(font);
//        text.setCharacterSize(24);
//        text.setFillColor(sf::Color::Black);
//        text.setString(label);
//        const auto bounds = text.getLocalBounds();  // �ؽ�Ʈ ũ�⸦ ������
//        text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
//        text.setPosition(
//            { shape.getPosition().x + shape.getSize().x / 2.f,
//            shape.getPosition().y + shape.getSize().y / 2.f }
//        );
//
//        // FPS ���� ��ư ���� (�� ��ư�� Ŭ���ϸ� FPS ����)
//        buttons.push_back(std::make_unique<UIButton>(
//            sf::Vector2f(position.x, position.y + 40.f),
//            sf::Vector2f(100.f, 40.f),
//            "FPS: 10",
//            sf::Color(214, 181, 106, 255),
//            font,
//            [this]() {
//                TimeManager::getInstance().setFPS(10);
//                text.setString("FPS: 10");
//            }
//        ));
//
//        buttons.push_back(std::make_unique<UIButton>(
//            sf::Vector2f(position.x, position.y + 90.f),
//            sf::Vector2f(100.f, 40.f),
//            "FPS: 20",
//            sf::Color(214, 181, 106, 255),
//            font,
//            [this]() {
//                TimeManager::getInstance().setFPS(20);
//                text.setString("FPS: 20");
//            }
//        ));
//
//        buttons.push_back(std::make_unique<UIButton>(
//            sf::Vector2f(position.x, position.y + 140.f),
//            sf::Vector2f(100.f, 40.f),
//            "FPS: 30",
//            sf::Color(214, 181, 106, 255),
//            font,
//            [this]() {
//                TimeManager::getInstance().setFPS(30);
//                text.setString("FPS: 30");
//            }
//        ));
//    }
//
//    // FPS ��ư ��� ��ȯ
//    std::vector<std::unique_ptr<UIButton>>& getButtons() {
//        return buttons;
//    }
//
//    void setPosition(const sf::Vector2f& position) {
//        shape.setPosition(position);
//        // �ؽ�Ʈ ��ġ ����
//        text.setPosition(
//            { shape.getPosition().x + shape.getSize().x / 2.f,
//            shape.getPosition().y + shape.getSize().y / 2.f }
//        );
//    }
//
//    // �̺�Ʈ ó�� (��ư Ŭ�� ����)
//    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override {
//        for (auto& button : buttons) {
//            button->handleEvent(event, window);
//        }
//    }
//
//    // ������Ʈ (�ʿ� �� ��ư ���� ����)
//    void update(sf::RenderWindow& window) override {
//        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
//        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            shape.setFillColor(sf::Color::White);
//        }
//        else {
//            shape.setFillColor(defaultColor);
//        }
//    }
//
//    // ȭ�鿡 FPS �ؽ�Ʈ �� ��ư ������
//    void render(sf::RenderWindow& window) override {
//        window.draw(text);
//        window.draw(shape);
//        for (auto& button : buttons) {
//            button->render(window);
//        }
//    }
//};

#pragma once
#include "BaseUI.hpp"
#include "UIButton.hpp"
#include "TimeManager.hpp"
#include <functional>
#include <vector>
#include <memory> // unique_ptr ����� ���� ��� �߰�

class FPSControl : public BaseUI {
private:
    sf::RectangleShape shape;
    sf::Text text;  // FPS ǥ�� �ؽ�Ʈ
    std::function<void(int)> onFpsChange; // FPS ���� �ݹ� �Լ�
    sf::Font& font; // ��Ʈ ����
    std::vector<std::unique_ptr<UIButton>> buttons; // FPS ���� ��ư��
    sf::Color defaultColor;

public:
    // FPSControl ������
    FPSControl(const std::string& label
        , const sf::Vector2f& position
        , const sf::Vector2f& size
        , sf::Color Color
        , sf::Font& sharedFont
        , std::function<void(int)> fpsChangeFunc)
        : font(sharedFont)
        , text(sharedFont, label, 48)
        , defaultColor(Color)
    {
        // ��� ����
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(Color);

        // FPS ǥ�� �ؽ�Ʈ ����
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        const auto bounds = text.getLocalBounds();
        text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });  // �ؽ�Ʈ �߾� ����
        text.setPosition(
            { shape.getPosition().x + shape.getSize().x / 2.f,
            shape.getPosition().y + shape.getSize().y / 2.f }
        ); // ��ġ ����

        // FPS ���� ��ư ���� (�� ��ư�� Ŭ���ϸ� FPS ����)
        buttons.push_back(std::make_unique<UIButton>(
            sf::Vector2f(position.x, position.y + 40.f),
            sf::Vector2f(100.f, 40.f),
            "FPS: 10",
            sf::Color(214, 181, 106, 255),
            font,
            []() {
                TimeManager::getInstance().setFPS(10);  // FPS ����
            }
        ));

        buttons.push_back(std::make_unique<UIButton>(
            sf::Vector2f(position.x, position.y + 90.f),
            sf::Vector2f(100.f, 40.f),
            "FPS: 20",
            sf::Color(214, 181, 106, 255),
            font,
            []() {
                TimeManager::getInstance().setFPS(20);  // FPS ����
            }
        ));

        buttons.push_back(std::make_unique<UIButton>(
            sf::Vector2f(position.x, position.y + 140.f),
            sf::Vector2f(100.f, 40.f),
            "FPS: 30",
            sf::Color(214, 181, 106, 255),
            font,
            []() {
                TimeManager::getInstance().setFPS(30);  // FPS ����
            }
        ));
    }

    // FPS ��ư ��� ��ȯ
    std::vector<std::unique_ptr<UIButton>>& getButtons() {
        return buttons;
    }

    void setPosition(const sf::Vector2f& position) {
        shape.setPosition(position);
        text.setPosition({ position.x + shape.getSize().x / 2.f, position.y - 30.f }); // �ؽ�Ʈ ��ġ ����
    }

    // �̺�Ʈ ó�� (��ư Ŭ�� ����)
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override {
        for (auto& button : buttons) {
            button->handleEvent(event, window);
        }
    }

    // ������Ʈ (�ʿ� �� ��ư ���� ����)
    void update(sf::RenderWindow& window) override {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(sf::Color::White);
        }
        else {
            shape.setFillColor(defaultColor);
        }
    }

    // ȭ�鿡 FPS �ؽ�Ʈ �� ��ư ������
    void render(sf::RenderWindow& window) override {
        window.draw(text);
        window.draw(shape);
        for (auto& button : buttons) {
            button->render(window);  // ��ư ������
        }
    }
};