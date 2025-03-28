#pragma once
#include "pch.h"
#include "BaseUI.hpp"
#include "KeyManager.h"
#include <functional>

class SettingsOverlay {
private:
    sf::RectangleShape background;
    sf::Text title;
    sf::Font font;

    std::vector<std::unique_ptr<BaseUI>> uiElements;
    bool visible = false;

    /*������*/
    /*----------------------------------------------------------------------*/
    float volume = 50.f;
    /*----------------------------------------------------------------------*/

public:
    SettingsOverlay(const sf::Vector2f& size, const sf::Font& sharedFont)
        : font(sharedFont), title(font, "Settings", 36)
    {
        background.setSize(size);
        background.setFillColor(sf::Color(50, 50, 50, 180));
        background.setPosition({ 0.f, 0.f });

        title.setFillColor(sf::Color::Black);
        title.setPosition({ 30.f, 20.f });

        // ����: ���� ����, ������ ��ư �� �߰� ����
        // �̰��� UIButton �� UI �߰� ����
        /*������*/
        /*----------------------------------------------------------------------*/
        auto exitButton = new UIButton(
            {  0.f, 0.f },   // ��ư ��ġ
            { 120.f, 40.f },                     // ��ư ũ��
            "Exit",                              // ��ư �ؽ�Ʈ
            sf::Color(214, 181, 106, 255),                    // ��ư ����
            font,                                // ��Ʈ
            [this]() {                           // Ŭ�� �� ����� �Լ�
                std::cout << "������ ��ư ����" << std::endl;
                this->toggle();                  // SettingsOverlay �ݱ�
            }
        );
        addElement(exitButton);
        /*----------------------------------------------------------------------*/
    }

    void toggle() {
        visible = !visible;
    }

    bool isVisible() const {
        return visible;
    }

    void setCenter(const sf::Vector2f& center) {
        background.setPosition({ center - background.getSize() / 2.f });
        title.setPosition({ center.x - title.getLocalBounds().size.x / 2.f, center.y - background.getSize().y / 2.f + 20.f });
        // ���� ��ư, �ؽ�Ʈ�ڽ� � center �������� ����
        /*������*/
        /*----------------------------------------------------------------------*/
        for (auto& ui : uiElements) {
            auto* exit = dynamic_cast<UIButton*>(ui.get());
            if (exit) {
                // ����: ��ư�� �������� ȭ���� ������ �ϴܿ� ��ġ (10px ����)
                exit->setPosition({
                    center.x + background.getSize().x / 2.f - exit->getSize().x - 10.f,  // ������ ������ 10px ����
                    center.y + background.getSize().y / 2.f - exit->getSize().y - 10.f   // �Ʒ��� ������ 10px ����
                    });
            }
        }
        /*----------------------------------------------------------------------*/
    }


    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (!visible) return;
        for (auto& ui : uiElements)
            ui->handleEvent(event, window);
    }

    void update(sf::RenderWindow& window) {
        if (!visible) return;
        for (auto& ui : uiElements)
            ui->update(window);
    }

    void render(sf::RenderWindow& window) {
        if (!visible) return;
        window.draw(background);
        window.draw(title);
        for (auto& ui : uiElements)
            ui->render(window);
    }

    void addElement(BaseUI* ui) {
        uiElements.emplace_back(ui);
    }

    void clear() {
        uiElements.clear();
    }
};