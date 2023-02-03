//
// Created by LEE KYOUNGHEON on 2023/02/03.
//

#include "ConvexBoundary.hpp"

ConvexBoundary::ConvexBoundary(const std::vector<sf::Vector2f> &points) : points(points) {
    if (points.size() < 3){ // (# of points) < 3: not polygon
        throw std::runtime_error { "At least three sides must exist to form a polygonal boundary." };
    }
}

bool ConvexBoundary::contains(sf::Vector2f position) const {
    /** To determine whether point is inside the convex polygon (in CCW ordered vertices),
     * calculate the vectors from point to each vertices, and check if their vectors are in CCW
     * orientation. This can be done by calculate the cross product of adjacent vectors and
     * its sign is (+).
     */

    auto prev_vector = points.front() - position;
#if __cplusplus >= 202002L // since c++20
    for (std::ptrdiff i = 1; i < std::ssize(points); ++i){
#else
    for (auto i = 1U; i < points.size(); ++i){
#endif
        auto current_vector = points[i] - position;
        if (prev_vector.cross(current_vector) <= 0){
            return false;
        }
        prev_vector = current_vector;
    }

    return true;
}
