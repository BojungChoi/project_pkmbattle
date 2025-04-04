#pragma once
#include "pch.h"
#include "Player.hpp"
#include "UIChattingBox.hpp"

class PlayerManager {
private:
    Player MyPlayer;
    std::unordered_map<int, Player> otherPlayers;
    UIChattingBox chatting;
    PlayerManager() = default;
    int capHolderId = -1;
    int lostId = -1;

public:
    // �̱��� ������
    static PlayerManager& getInstance() {
        static PlayerManager instance;
        return instance;
    }

    // ���� ����
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;

    void make_MyPlayer(int id, std::string nickname, int _x, int _y, int _win, int _lose, int _level, int _exp);
    // ������ 3����Ʈ
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);

    // ���� ���� ó��
    void handleEvent(std::string tag, std::string msg);

    // �÷��̾� ����
    void addPlayer(int id, std::string nickname, int _x, int _y, int _win, int _lose, int _level, int _exp);
    void removePlayer(int id);

    Player* getPlayer(int id);
    Player& getMyPlayer();
    std::unordered_map<int, Player>& getPlayers();
    UIChattingBox& getChatUI() { return chatting; }

    int getCapHolderId() { return capHolderId; }
    int getLostId() { return lostId; }
    void setLostId(int id) {
        lostId = id;
    }
    void setCapHolderId(int id) {
        capHolderId = id;
    }
};
