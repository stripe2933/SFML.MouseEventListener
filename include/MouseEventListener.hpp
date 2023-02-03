//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP
#define SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP

#include <ObjectBoundary.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class MouseEventListener {
public:
    //////////////////////////////////////////////////
    /// Fields
    //////////////////////////////////////////////////

    sf::Transformable &target;
    /// Boundary of target that used for hit test.
    std::shared_ptr<const ObjectBoundary> target_boundary;

    /// Event callback for mouse button pressing.
    std::function<void(MouseEventListener&, const sf::Event::MouseButtonEvent&)> on_mouse_button_pressed;
    /// Event callback for mouse button releasing.
    std::function<void(MouseEventListener&, const sf::Event::MouseButtonEvent&)> on_mouse_button_released;
    /// Event callback for mouse moving (on target).
    std::function<void(MouseEventListener&, const sf::Event::MouseMoveEvent&)> on_mouse_moved;
    /// Event callback for mouse wheel scrolling (on target).
    std::function<void(MouseEventListener&, const sf::Event::MouseWheelScrollEvent&)> on_mouse_wheel_scrolled;

    /// Event callback executed for z-index change. Second int parameter is old z-index value, and third int parameter is new z-index value.
    std::function<void(MouseEventListener&, int, int)> on_z_index_changed;

    //////////////////////////////////////////////////
    /// Constructors and destructor.
    //////////////////////////////////////////////////

    ~MouseEventListener() noexcept = default;
    MouseEventListener(sf::Transformable &target, std::shared_ptr<const ObjectBoundary> boundary, int z_index = 0);
    MouseEventListener(const MouseEventListener&) = delete; // The copy constructor was intentionally deleted. Because
                                                            // different z-indexes for the same target are meaningless,
                                                            // only one MouseEventListener should correspond to one target.
    MouseEventListener(MouseEventListener&&) = default; // Default move constructor

    //////////////////////////////////////////////////
    /// Getters and setters.
    //////////////////////////////////////////////////

    /**
     * Get current listener's z-index.
     * @return Z-index value.
     */
    int getZIndex() const noexcept;

    /**
     * Set listener's z-index and call \p on_z_index_changed callback.
     * @param value A new z-index value.
     */
    void setZIndex(int value);

private:
    /// For overlapped MouseEventListeners, only the highest z-indexed listener's event executed.
    int z_index;
};

#endif //SFML_MOUSEEVENTLISTENER_MOUSEEVENTLISTENER_HPP
