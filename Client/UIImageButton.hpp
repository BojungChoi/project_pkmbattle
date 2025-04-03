#pragma once
#include "BaseUI.hpp"
#include <functional>
#include <SFML/Graphics.hpp>

class UIImageButton : public BaseUI {
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    std::function<void()> onClick;
    bool focused = false;

public:
    // ������
    UIImageButton(const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const std::string& imagePath,
        std::function<void()> clickFunc)
        : onClick(clickFunc)
    {
        if (!texture.loadFromFile(imagePath)) {
            // �ؽ�ó �ε� ���� �� ���� ó��
            throw std::runtime_error("Failed to load texture");
        }

        shape.setPosition(pos);
        shape.setSize(size);
        shape.setTexture(&texture); // �ؽ�ó ����
    }

    // �̺�Ʈ �ڵ鷯
    void handleInput(const sf::Event& event, sf::RenderWindow& window) override {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();
            if (mouse &&
                mouse->button == sf::Mouse::Button::Left &&
                shape.getGlobalBounds().contains(mousePos)) {
                if (onClick) onClick();
            }
        }

        if (event.is<sf::Event::KeyPressed>()) {
            if (KeyManager::getInstance().isKeyPressed(sf::Keyboard::Key::Enter)) {
                if (onClick) onClick();
            }
        }
    }

    // ������Ʈ
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

    // ������
    void render(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    // ��Ŀ�� ����
    bool isFocusable() const override { return true; }
    bool isFocused() const override { return focused; }

    void setFocus(bool focus) override {
        focused = focus;
        // ��Ŀ�� �� �ܰ��� ���� ����
        shape.setOutlineColor(focus ? sf::Color::Yellow : sf::Color::Transparent);
        shape.setOutlineThickness(focus ? 3.f : 0.f);
    }

    // ��ġ ����
    void setPosition(const sf::Vector2f& position) {
        shape.setPosition(position);
    }
};