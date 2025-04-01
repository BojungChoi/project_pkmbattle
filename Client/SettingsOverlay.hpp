#pragma once
#include "TimeManager.hpp"
#include "pch.h"
#include "BaseUI.hpp"
#include "UISlider.hpp"
#include "KeyManager.h"
#include "UImuteControl.hpp"
#include "FPSControl.hpp"
#include <functional>
#include "SoundManager.hpp"
#include "GameManager.h"

class SettingsOverlay {
private:
    sf::RenderWindow& window;
    sf::RectangleShape background;
    sf::Text title;
    sf::Font font;
    std::vector<std::unique_ptr<BaseUI>> uiElements;
    bool visible = false;

    /*�ʱ⺼��*/
    float volume = 50.f;

public:
    SettingsOverlay(const sf::Vector2f& size, const sf::Font& sharedFont)
        : font(sharedFont), title(font, "Settings", 36), window(GameManager::getInstance().getWindow())
    {
        background.setSize(size);
        background.setFillColor(sf::Color(50, 50, 50, 180));
        background.setPosition({ 0.f, 0.f });

        title.setFillColor(sf::Color::Black);
        title.setPosition({ 30.f, 20.f });
        /*������*/
        /*----------------------------------------------------------------------*/
        // ������ ��ư
        auto exitButton = new UIButton(
            { 0.f, 0.f },   // ��ư ��ġ
            { 120.f, 40.f },                     // ��ư ũ��
            "Exit",                              // ��ư �ؽ�Ʈ
            sf::Color(214, 181, 106, 255),                    // ��ư ����
            font,                                // ��Ʈ
            [this]() {                           // Ŭ�� �� ����� �Լ�
                std::cout << "������ ��ư ����" << std::endl;
                window.close();                    // ���� �ݱ�
            }
        );
        // ���� �����̴� ��ư
        auto volumeSlider = new UISlider(
            { 0.f, 0.f },
            { 150.f, 10.f },
            &this->volume);
        // ���� ��Ʈ ��ư
        auto muteControl = new UImuteControl({ 720,10.f });
        /* FPS ���� ��ư �߰� */
        auto fpsControl = new FPSControl(
            "FPS op",                  // �� �ؽ�Ʈ
            { 0.f, 0.f },            // ��ġ
            { 100.f, 40.f },            // ũ�� (�ʺ� 120, ���� 200)
            sf::Color(100, 100, 100, 255), // ����
            font,                        // ��Ʈ
            [](int fps) {                // FPS ���� �ݹ�
                TimeManager::getInstance().setFPS(fps);
            }
        );

        // addElement�� ������
        addElement(exitButton);
        addElement(std::move(muteControl));
        addElement(volumeSlider);
        addElement(fpsControl);

        // �뷡 ���� ��ġ
        if (!SoundManager::getInstance().playMusic("C:\\Source\\project_pkmbattle\\Client\\assets\\track1.mp3")) {
            std::cerr << "���� ���� �ε� ����!" << std::endl;
        }

        // �ʱ� ���� ����
        SoundManager::getInstance().setVolume(true);
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

        float offsetY = center.y - background.getSize().y / 2.f + 80.f;

        for (auto& ui : uiElements) {
            // exit ��ư ��ǥ
            if (auto* exit = dynamic_cast<UIButton*>(ui.get())) {
                exit->setPosition({
                    center.x + background.getSize().x / 2.f - exit->getSize().x - 10.f,
                    center.y + background.getSize().y / 2.f - exit->getSize().y - 10.f
                    });
            }
            // mute ��ư ��ǥ
            else if (auto* mute = dynamic_cast<UImuteControl*>(ui.get())) {
                mute->setPosition({
                    center.x + background.getSize().x / 2.f - 57.f,
                    center.y - background.getSize().y / 2.f - 10.f
                    });
            }
            // volume slider ��ǥ
            else if (auto* Slider = dynamic_cast<UISlider*>(ui.get())) {
                Slider->setPosition({
                    center.x + background.getSize().x / 2.f - 43.f,
                    center.y - background.getSize().y / 2.f + 90.f
                    });
            }
            // FPS ��ư ��ǥ
            else if (auto* fpsControl = dynamic_cast<FPSControl*>(ui.get())) {
                fpsControl->setPosition({
                    center.x - background.getSize().x / 15.f,
                    center.y - background.getSize().y / 30.f
                    });
            }
        }
    }



    void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (!visible) return;
        for (auto& ui : uiElements)
            ui->handleEvent(event, window);

        SoundManager::getInstance().setVolume(volume >= SoundManager::getInstance().getVolume());
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
        uiElements.emplace_back(std::move(ui));
    }

    void clear() {
        uiElements.clear();
    }
};