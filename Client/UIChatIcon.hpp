#pragma once
#include "pch.h"
#include "BaseUI.hpp"
#include "UIButton.hpp"
#include "UIManager.hpp"
#include "KeyManager.hpp"
#include "TimeManager.hpp"

class UIChatIcon : public BaseUI {
private:
    sf::RectangleShape rectangle;
    sf::ConvexShape triangle; // ��ǳ�� ����
    sf::Text text;
    sf::Font font;

    float elapsed = 0.f;
    int dotCount = 0;
    float animationInterval = 0.5f;

    bool isOpen = false;

public:
    UIChatIcon(const sf::Vector2f& pos, const sf::Vector2f& size, int fontSize)
        : font(ResourceManager::getInstance().getFontByName("POKEMONGSKMONO.TTF"))
        , text(font,"", fontSize)
    {
        // ��ǳ�� ��Ÿ�� �ڽ�
        rectangle.setPosition(pos);
        rectangle.setSize(size);
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineThickness(3.f);
        rectangle.setOutlineColor(sf::Color::Black);

        // ���� �ﰢ��
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(10.f, 0.f));     // ���� ������
        triangle.setPoint(1, sf::Vector2f(20.f, 15.f));    // �Ʒ� �߾�
        triangle.setPoint(2, sf::Vector2f(30.f, 0.f));     // ������ ������
        triangle.setFillColor(sf::Color::White);
        triangle.setOutlineThickness(3.0f);
        triangle.setOutlineColor(sf::Color::Black);
        sf::Vector2f tailPos = { pos.x + size.x / 2.f - 15.f, pos.y + size.y }; // ���� �ȸ¾Ƽ��ٲ�
        triangle.setPosition(tailPos);
        
        text.setFont(font);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::Black);
        text.setString(std::wstring(L"���� ��ȭâ ����"));

        centerText(pos, size);
    }

    void centerText(const sf::Vector2f& pos, const sf::Vector2f& size) {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({ textBounds.size.x / 2.0f, textBounds.size.y / 2.0f });
        text.setPosition(pos + size / 2.0f);
    }


    void handleInput(const sf::Event& event, sf::RenderWindow& window) override {
    }

    void update(sf::RenderWindow& window) override {
        
        elapsed += TimeManager::getInstance().getDeltaTime();

        // . -> .. -> ... ������ 0.5�ʸ��� ��ȭ�ϴ´������� ����� �κ�

        if (elapsed >= animationInterval) {
            elapsed = 0.f;
            dotCount = (dotCount + 1) % 4; // 0 ~ 3
            text.setString(std::wstring(dotCount, L'.'));
            centerText(rectangle.getPosition(), rectangle.getSize());
        }

    }

    void render(sf::RenderWindow& window) override {
        window.draw(triangle);
        window.draw(rectangle);
        window.draw(text);
    }

    void setPos(const sf::Vector2f& pos) {
        rectangle.setPosition(pos);
        sf::Vector2f size = rectangle.getSize();

        float tailX = pos.x + (size.x / 2.f) - 20.f;
        float tailY = pos.y + size.y;
        triangle.setPosition({ tailX, tailY });

        // �ؽ�Ʈ �߾� ����
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({
            textBounds.position.x + textBounds.size.x / 2.f,
            textBounds.position.y + textBounds.size.y / 2.f
            });
        text.setPosition(pos + size / 2.f);
    }


    

    virtual bool isFocusable() const override { return false; }
    virtual bool isFocused() const override { return false; }
    virtual void setFocus(bool focus) override {}
};
