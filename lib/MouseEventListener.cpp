//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include <MouseEventListener.hpp>

#include <CircleBoundary.hpp>
#include <AARectangleBoundary.hpp>

MouseEventListener::MouseEventListener(sf::Transformable &target, std::shared_ptr<const ObjectBoundary> boundary,
                                       int z_index)
        : target { target },
          target_boundary { std::move(boundary) },
          z_index { z_index } { }

std::unique_ptr<MouseEventListener> MouseEventListener::createListenerFrom(sf::CircleShape &circle) {
    auto radius = circle.getRadius();
    auto boundary = std::make_unique<CircleBoundary>(sf::Vector2f{ radius, radius }, radius);
    return std::make_unique<MouseEventListener>(circle, std::move(boundary));
}

std::unique_ptr<MouseEventListener> MouseEventListener::createListenerFrom(sf::RectangleShape &rect) {
    auto boundary = std::make_unique<AARectangleBoundary>(sf::FloatRect { sf::Vector2f{}, rect.getSize() });
    return std::make_unique<MouseEventListener>(rect, std::move(boundary));
}

int MouseEventListener::getZIndex() const noexcept { return z_index; }

void MouseEventListener::setZIndex(int value) {
    int old_value = z_index;
    z_index = value;
    if (on_z_index_changed){
        on_z_index_changed(*this, old_value, value);
    }
}

