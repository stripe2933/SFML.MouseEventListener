//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include "AARectangleBoundary.hpp"

bool AARectangleBoundary::contains(sf::Vector2f position) const {
    return rect.contains(position);
}

AARectangleBoundary::AARectangleBoundary(const sf::FloatRect &rect) : rect(rect) { }
