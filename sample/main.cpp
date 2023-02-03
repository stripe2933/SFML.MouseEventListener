#include <random>

#include <MouseEventSystem.hpp>
#include <DragObserver.hpp>

int main() {
    sf::RenderWindow window { sf::VideoMode {{ 480U, 480U }}, "MouseEventListener Example" };
    window.setVerticalSyncEnabled(true);

    // Initialize random engine.

    std::random_device rd;
    std::mt19937 gen { rd() };
    std::uniform_real_distribution<float> ratio_dis { 0.f, 1.f }, scale_dis { 0.5f, 2.f };
    std::uniform_int_distribution<unsigned char> color_dis { 0, 255 };

    // Create 50 rectangle objects with varying position, rotation and scale.

    constexpr std::size_t NUM_OBJECTS = 50;
    std::vector<sf::RectangleShape> rects;
    rects.reserve(NUM_OBJECTS);
    std::generate_n(std::back_inserter(rects), NUM_OBJECTS, [&]{
        sf::RectangleShape rect { { 50.f, 50.f } };
        rect.setPosition(sf::Vector2f { window.getSize() }.cwiseMul({ ratio_dis(gen), ratio_dis(gen) }));
        rect.setRotation(sf::degrees(360.f * ratio_dis(gen)));
        rect.setFillColor(sf::Color { color_dis(gen), color_dis(gen), color_dis(gen) });
        rect.setScale({ scale_dis(gen), scale_dis(gen) });

        return rect;
    });

    // Create MouseEventListener from each rectangle and set behavior for mouse event.
    // Select/deselect panning target for mouse pressing/releasing.
    // Scale listener's target if mouse scroll over it.

    MouseEventSystem system { [&](sf::Vector2i position) { return window.mapPixelToCoords(position); } };
    std::optional<sf::Transformable*> panning_target = std::nullopt;
    for (auto &rect : rects){
        auto listener = std::make_unique<MouseEventListener>(rect, ObjectBoundary::createBoundaryFrom(rect));
        listener->on_mouse_button_pressed = [&](auto &sender, const auto &event){
            if (event.button == sf::Mouse::Left){
                panning_target = &sender.target;
                sender.setZIndex(1);
            }
        };
        listener->on_mouse_button_released = [&](auto &sender, const auto &event){
            panning_target = std::nullopt;
            sender.setZIndex(0);
        };
        listener->on_mouse_wheel_scrolled = [&](auto &sender, const auto &event){
            auto factor = std::pow(1.01f, event.delta);
            sender.target.scale({ factor, factor });
        };

        system.addListener(std::move(listener));
    }

    // Attach drag observer to window's mouse event.
    // Move panning_target when dragging.

    DragObserver drag_observer;
    sf::Vector2f prev_position_in_target_coordinate;
    drag_observer.on_drag_start = [&](sf::Vector2i position){
        prev_position_in_target_coordinate = window.mapPixelToCoords(position);
    };
    drag_observer.on_dragging = [&](sf::Vector2i position) {
        if (panning_target){
            auto current_position_in_target_coordinate = window.mapPixelToCoords(position);
            panning_target.value()->move(current_position_in_target_coordinate - prev_position_in_target_coordinate);
            prev_position_in_target_coordinate = current_position_in_target_coordinate;
        }
    };

    // Main loop.

    while (window.isOpen()) {
        for (sf::Event event { }; window.pollEvent(event);) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    system.executeMouseEvent<sf::Event::MouseButtonPressed>(event.mouseButton);
                    drag_observer.processMouseButtonPressedEvent(event.mouseButton);
                    break;

                case sf::Event::MouseButtonReleased:
                    system.executeMouseEvent<sf::Event::MouseButtonReleased>(event.mouseButton);
                    drag_observer.processMouseButtonReleasedEvent(event.mouseButton);
                    break;

                case sf::Event::MouseMoved:
                    drag_observer.processMouseMovedEvent(event.mouseMove);
                    break;

                case sf::Event::MouseWheelScrolled:
                    system.executeMouseEvent<sf::Event::MouseWheelScrolled>(event.mouseWheelScroll);
                    break;

                default:
                    break;
            }
        }

        window.clear();
        for (auto &listener : system.getListeners()){
            window.draw(*dynamic_cast<const sf::Drawable*>(&listener->target));
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
