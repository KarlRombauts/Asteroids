//
// Created by Karl Rombauts on 14/3/21.
//

#ifndef UNTITLED_EVENTMANAGER_H
#define UNTITLED_EVENTMANAGER_H

#include <typeindex>
#include <unordered_map>

class BaseEventListener {

};
template<typename EventType>
class EventListener : public BaseEventListener {
public:
    virtual void notify(EventType event) = 0;
};

class EventManager {
private:
    std::unordered_multimap<std::type_index, BaseEventListener*> observers;

public:
    template<typename EventType, typename ... Args>
    void emit(Args &&... args);

    template<typename EventType, typename EventListener>
    void subscribe(EventListener *eventListener);

    template<typename EventType>
    void unsubscribe();
};

template<typename EventType, typename... Args>
void EventManager::emit(Args &&... args) {
    auto result = observers.equal_range(typeid(EventType));
    for (auto it = result.first; it != result.second; it++) {
        auto listener = static_cast<EventListener<EventType>*>(it->second);
        listener->notify(EventType(std::forward<Args>(args)...));
    }
}

template<typename EventType, typename EventListener>
void EventManager::subscribe(EventListener* eventListener) {
    observers.insert(std::pair<std::type_index, BaseEventListener*>(typeid(EventType), eventListener));
}

#endif //UNTITLED_EVENTMANAGER_H
