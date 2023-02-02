//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP
#define SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP

#include <ObjectBoundary.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class MouseEventListener {
public:
    sf::Transformable &target;
    std::shared_ptr<const ObjectBoundary> target_boundary; /// Boundary of target that used for hit test.

    std::function<void(MouseEventListener&, const sf::Event::MouseButtonEvent&)> on_mouse_button_pressed; /// Event callback for mouse button pressing.
    std::function<void(MouseEventListener&, const sf::Event::MouseButtonEvent&)> on_mouse_button_released; /// Event callback for mouse button releasing.
    std::function<void(MouseEventListener&, const sf::Event::MouseMoveEvent&)> on_mouse_moved; /// Event callback for mouse moving (on target).
    std::function<void(MouseEventListener&, const sf::Event::MouseWheelScrollEvent&)> on_mouse_wheel_scrolled; /// Event callback for mouse wheel scrolling (on target).
    std::function<void(MouseEventListener&, int, int)> on_z_index_changed; /// Event callback executed for z-index change.

    MouseEventListener(sf::Transformable &target, std::shared_ptr<const ObjectBoundary> boundary, int z_index = 0);

    int getZIndex() const noexcept;
    void setZIndex(int value);

    static std::unique_ptr<MouseEventListener> createListenerFrom(sf::CircleShape &circle);
    static std::unique_ptr<MouseEventListener> createListenerFrom(sf::RectangleShape &rect);

private:
    int z_index; /// For overlapped MouseEventListeners, only the highest z-indexed listener's event executed.
};

#endif //SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP
