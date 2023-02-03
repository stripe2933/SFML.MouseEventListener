//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include "ObjectBoundary.hpp"

#include <CircleBoundary.hpp>
#include <AARectangleBoundary.hpp>
#include <ConvexBoundary.hpp>

std::shared_ptr<ObjectBoundary> ObjectBoundary::createBoundaryFrom(const sf::CircleShape &circle){
    auto radius = circle.getRadius();
    return std::make_shared<CircleBoundary>(sf::Vector2f{ radius, radius }, radius);
}

std::shared_ptr<ObjectBoundary> ObjectBoundary::createBoundaryFrom(const sf::RectangleShape &rect) {
    return std::make_shared<AARectangleBoundary>(sf::FloatRect { sf::Vector2f{}, rect.getSize() });
}

std::shared_ptr<ObjectBoundary> ObjectBoundary::createBoundaryFrom(const sf::ConvexShape &convex_polygon) {
    auto point_count = convex_polygon.getPointCount();

    std::vector<sf::Vector2f> points;
    points.reserve(point_count);
    std::generate_n(std::back_inserter(points), point_count, [&, i = 0U]() mutable {
        return convex_polygon.getPoint(i++);
    });

    return std::make_shared<ConvexBoundary>(std::move(points));
}
