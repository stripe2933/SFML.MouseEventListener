//
// Created by LEE KYOUNGHEON on 2023/02/02.
//

#ifndef SFML_MOUSEEVENTLISTENER_DRAGOBSERVER_HPP
#define SFML_MOUSEEVENTLISTENER_DRAGOBSERVER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class DragObserver{
public:
    static constexpr unsigned int DRAG_DISTANCE_THRESHOLD_SQ = 4; /// Squared distance of dragging for determine if
                                                                  /// the click is really drag, or just clicking.

    std::function<void(sf::Vector2i)> on_drag_start;
    std::function<void(sf::Vector2i)> on_dragging;
    std::function<void()> on_drag_end;

    void processMouseButtonPressedEvent(const sf::Event::MouseButtonEvent &event){
        if (event.button == sf::Mouse::Left){
            drag_state = DragState::Intermediate;
            initial_drag_position = { event.x, event.y };
        }
    }

    void processMouseMovedEvent(const sf::Event::MouseMoveEvent &event){
        sf::Vector2i current_position { event.x, event.y };

        if (drag_state == DragState::Dragging){
            if (on_dragging){
                on_dragging(current_position);
            }
        }
        else if (drag_state == DragState::Intermediate &&
                 (current_position - initial_drag_position).lengthSq() >= DRAG_DISTANCE_THRESHOLD_SQ){
            drag_state = DragState::Dragging;
            if (on_drag_start){
                on_drag_start(initial_drag_position);
            }
        }
    }

    void processMouseButtonReleasedEvent(const sf::Event::MouseButtonEvent &event){
        if (drag_state == DragState::Dragging && on_drag_end){
            on_drag_end();
        }
        drag_state = DragState::NotDragging;
    }

private:
    enum class DragState{
        NotDragging,
        Intermediate,
        Dragging
    };

    DragState drag_state { DragState::NotDragging };
    sf::Vector2i initial_drag_position { };
};

#endif //SFML_MOUSEEVENTLISTENER_DRAGOBSERVER_HPP
