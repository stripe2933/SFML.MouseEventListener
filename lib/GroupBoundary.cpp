//
// Created by LEE KYOUNGHEON on 2023/02/03.
//

#include "GroupBoundary.hpp"

GroupBoundary::GroupBoundary(std::initializer_list<std::shared_ptr<const ObjectBoundary>> boundaries) : boundaries(
        boundaries) { }

bool GroupBoundary::contains(sf::Vector2f position) const {
    return std::any_of(boundaries.cbegin(), boundaries.cend(), [=](const auto &boundary){
        return boundary->contains(position);
    });
}
