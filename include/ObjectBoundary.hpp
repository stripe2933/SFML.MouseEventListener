//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class ObjectBoundary {
public:
    virtual ~ObjectBoundary() noexcept { }

    virtual bool contains(sf::Vector2f position) const = 0;

    static std::shared_ptr<ObjectBoundary> createBoundaryFrom(const sf::CircleShape &circle);
    static std::shared_ptr<ObjectBoundary> createBoundaryFrom(const sf::RectangleShape &rect);
};

#endif //SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP
