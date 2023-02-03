//
// Created by LEE KYOUNGHEON on 2023/02/03.
//

#ifndef SFML_MOUSEEVENTLISTENER_GROUPBOUNDARY_HPP
#define SFML_MOUSEEVENTLISTENER_GROUPBOUNDARY_HPP

#include <ObjectBoundary.hpp>

class GroupBoundary : public ObjectBoundary{
public:
    std::vector<std::shared_ptr<const ObjectBoundary>> boundaries;

    explicit GroupBoundary(std::initializer_list<std::shared_ptr<const ObjectBoundary>> boundaries);

    bool contains(sf::Vector2f position) const override;
};

#endif //SFML_MOUSEEVENTLISTENER_GROUPBOUNDARY_HPP
