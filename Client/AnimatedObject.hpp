#pragma once
#include "TimeManager.hpp"
#include "pch.h"
#include <cmath>

class AnimatedObject {
private:
    std::shared_ptr<sf::Texture> texture;
    std::optional<sf::Sprite> sprite;
    sf::Vector2f basePos;
    float time = 0.f;
    float speed = 0.f;
    float amplitude = 0.f;
    float freq = 0.f;
    int direction;
    sf::Vector2f m_pos;

public:
    AnimatedObject() = default;

    AnimatedObject(const std::string& texPath, sf::Vector2f pos,
        float speed = 0.f, 
        float amplitude = 0.f, 
        float freq = 0.f, 
        int dir = -1)
        : basePos(pos)
        , speed(speed)
        , amplitude(amplitude)
        , freq(freq)
        , direction(dir) 
    {
        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(texPath)) {
            std::cerr << "�̹��� �ε� ����: " << texPath << "\n";
        }
        sprite.emplace(*texture);
        sprite->setPosition(pos);
        m_pos = sprite->getPosition();
    }

    void update(float dt,float windowWidth = 800.f) {
        time += dt;
        if (speed != 0.f) {
            m_pos.x += speed * dt * direction;
            if (windowWidth > 0.f && m_pos.x <= -300) {
                m_pos.x = windowWidth + 200;
            }
        }

        if (amplitude != 0.f && freq != 0.f) {
            m_pos.y = basePos.y + std::sin(time * freq) * amplitude;
        }

        sprite->setPosition(m_pos);
    }
    
    void bounce(float dt,float top, float down) {
        if (m_pos.y <= top) { direction = 1; }
        else if (m_pos.y >= down) { direction = -1; }
        m_pos.y += speed * dt * direction;

        sprite->setPosition(m_pos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(*sprite);
    }

    void setScale(sf::Vector2f scale) {
        sprite->setScale(scale);
    }

    void setPosition(sf::Vector2f pos) {
        basePos = pos;
        sprite->setPosition(pos);
    }

    void setOriginCenter() {
        auto bounds = sprite->getLocalBounds();
        sprite->setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    }

    sf::Sprite& getSprite() {
        return *sprite;
    }
};
