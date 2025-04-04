#pragma once
#include "pch.h"
#include "BaseUI.hpp"
#include "UIButton.hpp"
#include "KeyManager.hpp"
#include "GameManager.hpp"
#include "UIManager.hpp"
#include "ResourceManager.hpp"
#include "AnimatedObject.hpp"
#include "AnimationManager.hpp"

#include <functional>
#include <memory>
#include <vector>
#include <iostream> // ����� �޽����� ���� �߰�
#include <stdexcept> // ���� ó���� ���� �߰�

class SettingsOverlay {
private:
    sf::RenderWindow& window;
    sf::RectangleShape background;
    sf::Text title;
    sf::Font font;
    std::vector<std::unique_ptr<BaseUI>> uiElements;
    bool visible = false;

    // Yes�� No ��ư�� �ε����� ������ ����
    int yesButtonIndex = -1;
    int noButtonIndex = -1;
    int exitButtonIndex = -1;
    int backButtonIndex = -1;

    AnimationManager aniManager;
    sf::Sprite back = sf::Sprite(ResourceManager::getInstance().getTextureByName("settingsback.png"));
public:
    SettingsOverlay(const sf::Vector2f& size, const sf::Font& sharedFont)
        : font(ResourceManager::getInstance().getFontByName("POKEMONGSKMONO.TTF")), title(font, "Settings", 36), window(GameManager::getInstance().getWindow())
    {
        background.setSize(size);
        background.setFillColor(sf::Color(50, 50, 50, 180));
        background.setPosition({ 0.f, 0.f });

        title.setFillColor(sf::Color::Black);
        title.setPosition({ 30.f, 20.f });

        back.setPosition({ background.getPosition().x + 400.f, background.getPosition().y + 300.f });

        // "Back" �̹��� ��ư ����
        auto backButton = std::make_unique<UIButton>(
            sf::Vector2f(0.f, 0.f), // ��ư ��ġ
            sf::Vector2f(30.f, 30.f), // ��ư ũ��
            "",
            24, // �ؽ�Ʈ ũ��
            sf::Color(214, 181, 106, 50), // ��ư ����
            [this]() { // Ŭ�� �� ����� �Լ�
                toggle(); // ���� ȭ���� �ݱ�
            }
        );
        backButton->setHoverEffect(true);
        // addElement�� "Back" �̹��� ��ư �߰�
        addElement(std::move(backButton));
        backButtonIndex = uiElements.size() - 1;

        // "Exit" ��ư ����
        auto exitButton = std::make_unique<UIButton>(
            sf::Vector2f(0.f, 0.f), // ��ư ��ġ
            sf::Vector2f(120.f, 40.f), // ��ư ũ��
            "EXIT", // ��ư �ؽ�Ʈ
            24, // �ؽ�Ʈ ũ��
            sf::Color(214, 181, 106, 255), // ��ư ����
            [this]() { // Ŭ�� �� ����� �Լ�
                if (yesButtonIndex == -1 && noButtonIndex == -1) {
                    std::cout << "������ ��ư ����" << std::endl;
                    // "Yes"�� "No" ��ư ǥ��
                    showYesNoButtons();
                }
            }
        );

        // addElement�� "Exit" ��ư �߰�
        addElement(std::move(exitButton));
        exitButtonIndex = uiElements.size() - 1;
    }

    void toggle() {
        visible = !visible;
    }

    bool isVisible() const {
        return visible;
    }

    void setCenter(const sf::Vector2f& center) {
        background.setPosition({ center - (background.getSize() / 2.f) });
        title.setPosition({ center.x - title.getLocalBounds().size.x / 2.f, center.y - background.getSize().y / 2.f + 20.f });

        // ��ư ��ġ�� ����
        for (size_t i = 0; i < uiElements.size(); ++i) {
            if (auto* button = dynamic_cast<UIButton*>(uiElements[i].get())) {
                if (i == yesButtonIndex) {
                    // "Yes" ��ư�� ��ġ ����
                    button->setPosition({
                        center.x - 130.f,
                        center.y + 10.f
                        });
                }
                else if (i == noButtonIndex) {
                    // "No" ��ư�� ��ġ ����
                    button->setPosition({
                        center.x + 10.f,
                        center.y + 10.f
                        });
                }
                else if (i == exitButtonIndex) {
                    // "Exit" ��ư�� ��ġ ����
                    button->setPosition({
                        center.x - button->getSize().x / 2.f ,
                        center.y - button->getSize().y / 2.f + 200.f
                        });
                }
                else if (i == backButtonIndex) {
                    // "Back" �̹��� ��ư�� ��ġ ����
                    button->setPosition({
                        background.getPosition().x + 30.f,
                        background.getPosition().y + 20.f
                        });
                }
            }
        }
        back.setPosition({ background.getPosition().x + 30.f, background.getPosition().y + 20.f });
    }

    void handleInput(const sf::Event& event, sf::RenderWindow& window) {
        if (!visible) return;
        for (auto& ui : uiElements)
            ui->handleInput(event, window);
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
        window.draw(back);
    }

    void addElement(std::unique_ptr<BaseUI> ui) {
        uiElements.push_back(std::move(ui));
    }

    // "Yes"�� "No" ��ư�� ǥ���ϴ� �Լ�
    void showYesNoButtons() {
        if (yesButtonIndex == -1 && noButtonIndex == -1) { // "Yes"�� "No" ��ư�� �̹� �ִ� ��� �ߺ� �߰� ����
            // "Yes" ��ư ����
            auto yesButton = std::make_unique<UIButton>(
                sf::Vector2f(0.f, 0.f), // ��ư ��ġ
                sf::Vector2f(120.f, 40.f), // ��ư ũ��
                "Yes", // ��ư �ؽ�Ʈ
                24, // �ؽ�Ʈ ũ��
                sf::Color(100, 200, 100, 255), // ��ư ����
                [this]() { // Ŭ�� �� ����� �Լ�
                    std::cout << "Yes ��ư ����" << std::endl;
                    NetworkManager::getInstance().send("EXIT\n");
                }
            );

            // "No" ��ư ����
            auto noButton = std::make_unique<UIButton>(
                sf::Vector2f(0.f, 0.f), // ��ư ��ġ
                sf::Vector2f(120.f, 40.f), // ��ư ũ��
                "No", // ��ư �ؽ�Ʈ
                24, // �ؽ�Ʈ ũ��
                sf::Color(200, 100, 100, 255), // ��ư ����
                [this]() { // Ŭ�� �� ����� �Լ�
                    std::cout << "No ��ư ����" << std::endl;
                    hideYesNoButtons(); // "Yes"�� "No" ��ư �����
                }
            );

            // addElement�� "Yes"�� "No" ��ư �߰��ϰ� �ε��� ����
            addElement(std::move(yesButton));
            yesButtonIndex = uiElements.size() - 1; // �ε��� ����

            addElement(std::move(noButton));
            noButtonIndex = uiElements.size() - 1; // �ε��� ����

            // "Yes"�� "No" ��ư�� ��ġ ����
            setCenter({ window.getSize().x / 2.f, window.getSize().y / 2.f });
        }
    }

    // "Yes"�� "No" ��ư�� ����� �Լ�
    void hideYesNoButtons() {
        if (noButtonIndex != -1 && noButtonIndex < uiElements.size()) {
            uiElements.erase(uiElements.begin() + noButtonIndex);
            noButtonIndex = -1; // �ε��� �ʱ�ȭ
        }

        if (yesButtonIndex != -1 && yesButtonIndex < uiElements.size()) {
            uiElements.erase(uiElements.begin() + yesButtonIndex);
            yesButtonIndex = -1; // �ε��� �ʱ�ȭ
        }
    }
};