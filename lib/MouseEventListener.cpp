//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include <MouseEventListener.hpp>

#include <CircleBoundary.hpp>
#include <AARectangleBoundary.hpp>

MouseEventListener::MouseEventListener(sf::Transformable &target, std::shared_ptr<const ObjectBoundary> boundary,
                                       int z_index)
        : target { target },
          target_boundary { std::move(boundary) },
          z_index { z_index } { }

int MouseEventListener::getZIndex() const noexcept { return z_index; }

void MouseEventListener::setZIndex(int value) {
    int old_value = z_index;
    z_index = value;
    if (on_z_index_changed){
        on_z_index_changed(*this, old_value, value);
    }
}

