//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_CIRCLEBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_CIRCLEBOUNDARY_HPP

#include <ObjectBoundary.hpp>

class CircleBoundary : public ObjectBoundary {
public:
    sf::Vector2f center;
    float radius;

    constexpr CircleBoundary(sf::Vector2f center, float radius);

    bool contains(sf::Vector2f position) const override;
};

#endif //SFML_MOUSEEVENTLISTENER_CIRCLEBOUNDARY_HPP
