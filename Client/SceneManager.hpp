#pragma once
#include "baseScene.hpp"


class SceneManager {
private:
    std::unordered_map<std::string, BaseScene*> scenes;
    BaseScene* currentScene = nullptr;
    std::string pendingSceneKey;

    // �̱���
    SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    // ���� ��Ŷ �ڵ鷯
    void handleEvent(std::string tag, std::string msg);

    // ----------------------------------------------------------------------
    // ���ӷ���
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    // ----------------------------------------------------------------------


    // --------------------------------------------------------------
    // �� ���, ��ȯ ����
    void registerAll();
    void registerScene(const std::string& key, BaseScene* scene);
    void changeScene(const std::string& key);
    void applyPendingScene();
    // --------------------------------------------------------------


    // ---------------------------------------------------------------
    // �� ����
    BaseScene* getScene(const std::string& key);
    BaseScene* getCurScene();
    // ---------------------------------------------------------------


    // ---------------------------------------------------------------
    // �޸𸮰���
    void cleanup();

    ~SceneManager();
    
    // ---------------------------------------------------------------

};