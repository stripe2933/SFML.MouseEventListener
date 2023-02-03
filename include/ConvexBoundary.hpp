//
// Created by LEE KYOUNGHEON on 2023/02/03.
//

#ifndef SFML_MOUSEEVENTLISTENER_CONVEXBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_CONVEXBOUNDARY_HPP

#include <ObjectBoundary.hpp>

class ConvexBoundary : public ObjectBoundary{
public:
    /// Vertices of convex polygon. The order of the points must be counterclockwise.
    std::vector<sf::Vector2f> points;

    explicit ConvexBoundary(const std::vector<sf::Vector2f> &points);

    bool contains(sf::Vector2f position) const override;
};

#endif //SFML_MOUSEEVENTLISTENER_CONVEXBOUNDARY_HPP
