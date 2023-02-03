//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include "ObjectBoundary.hpp"

#include <CircleBoundary.hpp>
#include <AARectangleBoundary.hpp>

std::shared_ptr<ObjectBoundary> ObjectBoundary::createBoundaryFrom(const sf::CircleShape &circle){
    auto radius = circle.getRadius();
    return std::make_shared<CircleBoundary>(sf::Vector2f{ radius, radius }, radius);
}

std::shared_ptr<ObjectBoundary> ObjectBoundary::createBoundaryFrom(const sf::RectangleShape &rect) {
    return std::make_shared<AARectangleBoundary>(sf::FloatRect { sf::Vector2f{}, rect.getSize() });
}
