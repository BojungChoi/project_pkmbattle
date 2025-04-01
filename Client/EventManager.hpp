#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>

class EventManager {
private:
    EventManager() = default;

    // �޽��� �з� �����: <"TAG", {"msg1","msg2",...}>
    std::unordered_map<std::string, std::vector<std::string>> eventMap;
    std::mutex eventMutex;

public:
    static EventManager& getInstance();

    void dispatch(const std::string& msg); // ���ŵ� �޽����� �з�
    std::vector<std::string> getEvents(const std::string& tag); // �±׺� �޽��� ��ȸ
    void clearEvents(const std::string& tag); // ��� �Ϸ�� �޽��� ����

};
