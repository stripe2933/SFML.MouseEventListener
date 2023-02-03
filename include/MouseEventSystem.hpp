//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_MOUSEEVENTSYSTEM_HPP
#define SFML_MOUSEEVENTLISTENER_MOUSEEVENTSYSTEM_HPP

#include <MouseEventListener.hpp>
#include <list>

class MouseEventSystem{
private:
    //////////////////////////////////////////////////
    /// Type definitions.
    //////////////////////////////////////////////////

    // Specify event parameter type and event callback for corresponding sf::Event::EventType.
    template <sf::Event::EventType T> struct event_arg { };
    template <> struct event_arg<sf::Event::MouseButtonPressed> {
        using arg_type = sf::Event::MouseButtonEvent;
        constexpr static auto has_callback = [](const MouseEventListener &listener) { return static_cast<bool>(listener.on_mouse_button_pressed); };
        constexpr static auto execute_callback = [](MouseEventListener &listener, const arg_type &event){ listener.on_mouse_button_pressed(listener, event); };
    };
    template <> struct event_arg<sf::Event::MouseButtonReleased> {
        using arg_type = sf::Event::MouseButtonEvent;
        constexpr static auto has_callback = [](const MouseEventListener &listener) { return static_cast<bool>(listener.on_mouse_button_released); };
        constexpr static auto execute_callback = [](MouseEventListener &listener, const arg_type &event){ listener.on_mouse_button_released(listener, event); };
    };
    template <> struct event_arg<sf::Event::MouseMoved> {
        using arg_type = sf::Event::MouseMoveEvent;
        constexpr static auto has_callback = [](const MouseEventListener &listener) { return static_cast<bool>(listener.on_mouse_moved); };
        constexpr static auto execute_callback = [](MouseEventListener &listener, const arg_type &event){ listener.on_mouse_moved(listener, event); };
    };
    template <> struct event_arg<sf::Event::MouseWheelScrolled> {
        using arg_type = sf::Event::MouseWheelScrollEvent;
        constexpr static auto has_callback = [](const MouseEventListener &listener) { return static_cast<bool>(listener.on_mouse_wheel_scrolled); };
        constexpr static auto execute_callback = [](MouseEventListener &listener, const arg_type &event){ listener.on_mouse_wheel_scrolled(listener, event); };
    };

public:
    //////////////////////////////////////////////////
    /// Constructors and destructor.
    //////////////////////////////////////////////////

    ~MouseEventSystem() noexcept = default;
    explicit MouseEventSystem(const std::function<sf::Vector2f(sf::Vector2i)> &coordination_converter);
    MouseEventSystem(const MouseEventSystem&) = delete;
    MouseEventSystem(MouseEventSystem&&) = default;

    //////////////////////////////////////////////////
    /// Member functions.
    //////////////////////////////////////////////////

    /**
     * Add listener to listeners.
     * @param listener An unique_ptr object of MouseEventListener.
     */
    void addListener(std::unique_ptr<MouseEventListener> listener);

    /**
     * Delete listener in the index.
     * @param index Listener index in listeners.
     * @note Index of listeners may changed due to it's z-index changing.
     */
    void deleteListener(std::size_t index);

    const std::list<std::unique_ptr<MouseEventListener>> &getListeners() const;

    /**
     * Execute callback of the MouseEventListener corresponding to the given input.
     * @tparam T SFML mouse event type (MouseButtonPressed/MouseButtonReleased/MouseMoved/MouseWheelScrolled).
     * @param event Event object corresponds to given SFML mouse event type (\p T).
     *
     * @example
     * @code
     * // `system` is MouseEventSystem and suppose listeners are already registered.
     *
     * // In sf::RenderWindow main loop:
     * for (sf::Event event { }; window.pollEvent(event);) {
     *     switch (event.type) {
     *         // Use executeMouseEvent for the necessary event input.
     *         // In here, we want to get mouse input for only mouse pressing and moving.
     *
     *         case sf::Event::MouseButtonPressed:
     *             system.executeMouseEvent<sf::Event::MouseButtonPressed>(event.mouseButton);
     *             break;
     *         case sf::Event::MouseMoved:
     *             system.executeMouseEvent<sf::Event::MouseMoved>(event.mouseMove);
     *             break;
     *
     *         // ... other cases for sf::Event::EventType.
     *     }
     * }
     *
     * // Now when clicking or moving cursor in the listener's boundary, their on_mouse_button_pressed/on_mouse_moved callback will be executed.
     * @endcode
     */
    template <sf::Event::EventType T>
    void executeMouseEvent(const typename event_arg<T>::arg_type &event) const{
        auto result = getFirstHitTestListener<T>({ event.x, event.y });
        if (result){
            auto listener = result.value();
            event_arg<T>::execute_callback(*listener, event);
        }
    }

private:
    //////////////////////////////////////////////////
    /// Private member fields.
    //////////////////////////////////////////////////

    std::function<sf::Vector2f(sf::Vector2i)> coordination_converter; /// A converter for converting given window-
                                                                      /// coordinate Vector2i to target-coordinate Vector2f.
    std::list<std::unique_ptr<MouseEventListener>> listeners; /// Registered listeners. Sorted in ascending order of z-index.

    //////////////////////////////////////////////////
    /// Private member functions.
    //////////////////////////////////////////////////

    /**
     * Calculate the object with the highest \p z_index that has a callback corresponding to a given \p MouseEventType
     * and has a successful hit test for a given \p mouse_position.
     * @tparam MouseEventType \p MouseButtonPressed / \p MouseButtonReleased / \p MouseMoved / \p MouseWheelScrolled.
     * @param mouse_position A window-coordinated mouse position.
     * @return Const pointer of \p MouseEventListener that satisfy given mouse position and event type,
     * \p std::nullopt otherwise.
     */
    template <sf::Event::EventType MouseEventType>
    std::optional<MouseEventListener*> getFirstHitTestListener(sf::Vector2i mouse_position) const{
        // Since listeners are sorted with ascending z-index, traverse listeners by reverse direction.
        auto it = std::find_if(listeners.crbegin(), listeners.crend(), [&](auto &listener){
            if (!event_arg<MouseEventType>::has_callback(*listener)){
                return false; // Early return for callback unregistered listener.
            }

            // Check if mouse_position is inside in listener's boundary.
            auto position = coordination_converter(mouse_position);
            auto position_in_target_coordinate = listener->target.getInverseTransform().transformPoint(position);

            return listener->target_boundary->contains(position_in_target_coordinate);
        });

        return it != listeners.crend() ? std::optional<MouseEventListener*> { it->get() }
                                       : std::nullopt;
    }
};

#endif //SFML_MOUSEEVENTLISTENER_MOUSEEVENTSYSTEM_HPP
