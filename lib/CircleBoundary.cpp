//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include "CircleBoundary.hpp"

CircleBoundary::CircleBoundary(sf::Vector2f center, float radius) : center(center), radius(radius) { }

bool CircleBoundary::contains(sf::Vector2f position) const {
    return (position - center).lengthSq() <= radius * radius;
}
