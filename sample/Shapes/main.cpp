#include <iostream>

#include <MouseEventSystem.hpp>
#include <CircleBoundary.hpp>
#include <GroupBoundary.hpp>

static const std::filesystem::path ASSET_DIRNAME = "/Users/stripe2933/Desktop/SFML.MouseEventListener/sample/Shapes/assets";

int main() {
    sf::RenderWindow window { sf::VideoMode {{ 480U, 480U }}, "MouseEventListener Example - Shapes" };
    window.setVerticalSyncEnabled(true);

    MouseEventSystem system { [&](sf::Vector2i position) { return window.mapPixelToCoords(position); }};

    // Create circle and register its listener.
    // Print message when click circle.

    sf::CircleShape circle { 30.f };
    circle.setPosition({ 100.f, 100.f });
    circle.setScale({ 1.f, 2.f });
    circle.setFillColor(sf::Color::Red);

    auto circle_listener = std::make_unique<MouseEventListener>(circle, ObjectBoundary::createBoundaryFrom(circle));
    circle_listener->on_mouse_button_pressed = [](auto &, const auto &) {
        std::cout << "Mouse click on circle.\n";
    };
    system.addListener(std::move(circle_listener));

    // Create rectangle and register its listener.
    // Print message when click rectangle.

    sf::RectangleShape rect {{ 60.f, 80.f }};
    rect.setPosition({ 320.f, 260.f });
    rect.setRotation(sf::degrees(30));
    rect.setFillColor(sf::Color::Blue);

    auto rect_listener = std::make_unique<MouseEventListener>(rect, ObjectBoundary::createBoundaryFrom(rect));
    rect_listener->on_mouse_button_pressed = [](auto &, const auto &) {
        std::cout << "Mouse click on rect.\n";
    };
    system.addListener(std::move(rect_listener));

    // Create SFML sprite and register its listener.
    // Change wing texture when click sprite.
    // You can use GroupBoundary(which hit test for multiple boundaries) for non-regular shape object.

    sf::Texture bird_tex, up_wing_tex, down_wing_tex;
    if (!bird_tex.loadFromFile(ASSET_DIRNAME / "birdbody.png") ||
        !up_wing_tex.loadFromFile(ASSET_DIRNAME / "birdwingdown.png") ||
        !down_wing_tex.loadFromFile(ASSET_DIRNAME / "birdwingup.png")) {
        throw std::runtime_error { "Cannot load required texture." };
    }
    bird_tex.setSmooth(true);
    up_wing_tex.setSmooth(true);
    down_wing_tex.setSmooth(true);

    sf::Sprite bird_sprite { bird_tex },
            up_wing_sprite { up_wing_tex },
            down_wing_sprite { down_wing_tex };
    // Scale to 25%.
    bird_sprite.setScale({ 0.25f, 0.25f });
    up_wing_sprite.setScale({ 0.25f, 0.25f });
    down_wing_sprite.setScale({ 0.25f, 0.25f });

    bird_sprite.move({ 50.f, 0.f });
    up_wing_sprite.move({ 0.f, 50.f });
    down_wing_sprite.move({ 0.f, 50.f });

    sf::RenderTexture total_tex;
    bool is_wing_up = true;
    if (!total_tex.create({ 160U, 160U })) {
        throw std::runtime_error { "Cannot create SFML RenderTexture." };
    }
    total_tex.draw(bird_sprite);
    total_tex.draw(up_wing_sprite);
    total_tex.display();

    sf::Sprite total_sprite { total_tex.getTexture() };
    total_sprite.move({ 100.f, 300.f });

    // Boundary coordinate is based on total_sprite.
    auto bird_body_boundary = std::make_shared<CircleBoundary>(sf::Vector2f{ 106.f, 74.f }, 56.f);
    auto bird_wing_boundary = std::make_shared<CircleBoundary>(sf::Vector2f{ 24.f, 75.f }, 28.f);
    auto bird_boundary = std::make_shared<GroupBoundary>(
            std::initializer_list<std::shared_ptr<const ObjectBoundary>>{
                bird_body_boundary,
                bird_wing_boundary });

    auto bird_listener = std::make_unique<MouseEventListener>(total_sprite, bird_boundary);
    bird_listener->on_mouse_button_pressed = [&](auto&, const auto&){
        total_tex.clear();
        total_tex.draw(bird_sprite);
        if (is_wing_up){
            total_tex.draw(down_wing_sprite);
        }
        else{
            total_tex.draw(up_wing_sprite);
        }
        is_wing_up = !is_wing_up;
        total_tex.display();

        total_sprite.setTexture(total_tex.getTexture());
    };
    system.addListener(std::move(bird_listener));

    while (window.isOpen()) {
        for (sf::Event event { }; window.pollEvent(event);) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    system.executeMouseEvent<sf::Event::MouseButtonPressed>(event.mouseButton);
                    break;

                default:
                    break;
            }
        }

        window.clear();
        for (auto &listener: system.getListeners()) {
            window.draw(*dynamic_cast<const sf::Drawable*>(&listener->target));
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
