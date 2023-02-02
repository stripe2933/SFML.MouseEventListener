//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include "MouseEventSystem.hpp"

struct ZIndexComparer{
    bool operator()(const std::unique_ptr<MouseEventListener> &lhs, const std::unique_ptr<MouseEventListener> &rhs) const{
        return lhs->getZIndex() < rhs->getZIndex();
    }
    bool operator()(const std::unique_ptr<MouseEventListener> &lhs, int rhs_z_index) const{
        return lhs->getZIndex() < rhs_z_index;
    }
    bool operator()(int lhs_z_index, const std::unique_ptr<MouseEventListener> &rhs) const{
        return lhs_z_index < rhs->getZIndex();
    }
} z_index_comparer;

void MouseEventSystem::addListener(std::unique_ptr<MouseEventListener> listener) {
    listener->on_z_index_changed = [&](auto &sender, int old_z_index, int new_z_index){
        auto current_position = std::find_if(listeners.cbegin(), listeners.cend(),
                                             [p = &sender.target](const auto &listener) { return &listener->target == p; });
        auto new_position = std::upper_bound(listeners.cbegin(), listeners.cend(), new_z_index, z_index_comparer);
        listeners.splice(new_position, listeners, current_position, std::next(current_position, 1)); // current position always in [begin, end)
    };

    auto insert_pos = std::upper_bound(listeners.begin(), listeners.end(), listener->getZIndex(), z_index_comparer);
    listeners.insert(insert_pos, std::move(listener));
}

void MouseEventSystem::deleteListener(std::size_t index) {
    listeners.erase(std::next(listeners.begin(), index));
}

MouseEventSystem::MouseEventSystem(const std::function<sf::Vector2f(sf::Vector2i)> &coordination_converter)
        : coordination_converter(coordination_converter) { }

const std::list<std::unique_ptr<MouseEventListener>> &MouseEventSystem::getListeners() const {
    return listeners;
}
