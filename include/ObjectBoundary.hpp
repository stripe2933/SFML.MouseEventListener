//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP

#include <SFML/System/Vector2.hpp>

class ObjectBoundary {
public:
    virtual ~ObjectBoundary() noexcept { }

    virtual bool contains(sf::Vector2f position) const = 0;
};

#endif //SFML_MOUSEEVENTLISTENER_OBJECTBOUNDARY_HPP
