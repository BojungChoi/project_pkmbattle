#include "EventManager.hpp"
#include <sstream>

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

void EventManager::dispatch(const std::string& msg) {
    std::istringstream iss(msg);
    std::string tag;
    iss >> tag; // ù �ܾ �±�(��ɾ�)�� ���

    std::lock_guard<std::mutex> lock(eventMutex);
    eventMap[tag].push_back(msg);
}

std::vector<std::string> EventManager::getEvents(const std::string& tag) {
    std::lock_guard<std::mutex> lock(eventMutex);
    if (eventMap.find(tag) == eventMap.end()) return {};
    return eventMap[tag]; // ���纻 ��ȯ
}

void EventManager::clearEvents(const std::string& tag) {
    std::lock_guard<std::mutex> lock(eventMutex);
    eventMap.erase(tag);
}
