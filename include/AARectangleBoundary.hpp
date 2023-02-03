//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_AARECTANGLEBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_AARECTANGLEBOUNDARY_HPP

#include <ObjectBoundary.hpp>
#include <SFML/Graphics/Rect.hpp>

class AARectangleBoundary : public ObjectBoundary {
public:
    sf::FloatRect rect;

    explicit AARectangleBoundary(const sf::FloatRect &rect);

    bool contains(sf::Vector2f position) const override;
};

#endif //SFML_MOUSEEVENTLISTENER_AARECTANGLEBOUNDARY_HPP
