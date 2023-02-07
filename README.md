# SFML.MouseEventListener
Make SFML 3 shapes listen mouse event when cursor is in their boundary.

## A working example
[Sample: [ManyConvexes](https://github.com/stripe2933/SFML.MouseEventListener/tree/master/sample/ManyConvexes)]

https://user-images.githubusercontent.com/63503910/217190870-27e32287-4cc1-40ce-8534-7cea4fca8125.mov

## How to add this library to my project?

This library is based on CMake. You can use `FetchContent` CMake script to add the library.

```cmake
include(FetchContent)
FetchContent_Declare(SFML_MouseEventListener
        GIT_REPOSITORY https://github.com/stripe2933/SFML.MouseEventListener.git)
FetchContent_MakeAvailable(SFML_MouseEventListener)

target_link_libraries(${PROJECT_NAME} PUBLIC SFML_MouseEventListener)
```

Because the library has direct dependency from SFML, SFML would be automatically included to your project via find_package(SFML).
You can set `SFML_DIR` CMake variable manually if the CMake system cannot find SFML.

## How should I use it?

It supports `sf::CircleShape`, `sf::RectangleShape`, `sf::ConvexShape` and any custom combined boundary consists of circle, rectangle and convex polygon.
For example, if you want to print message when clikcing `sf::CircleShape`,

1. Make `sf::CircleShape` object.
```c++
sf::CircleShape circle { 24.f }; // Make a circle with radius=24.

// You can apply any affine transformation to the object.
circle.setPosition({ 200.f, 100.f });
circle.setScale({ 1.2f, 2.0f });
```

2. Create `MouseEventSystem` which accepts mouse event from window and execute registered `MouseEventListener`.
```c++
// MouseEventSystem accept integer-vector(sf::Vector2f) from sf::Event.
// Since your object is not only positioned by float-vector, but also may inside your own created sf::View,
// the accepted int vector and real position of object may different.
// Therefore, You should register MouseEventSystem with coordination converter, which converts mouse position
// to actual object-coordinate position.
MouseEventSystem system { [&](sf::Vector2i position) { return window.mapPixelToCoords(position); } };

// Now you can register listener from target object. Create an ObjectBoundary with factory method `createBoundaryFrom`,
// and unique_ptr of MouseEventListener.
// The constructor of MouseEventListener has optional argument, z_index, which indicates the hit-test priority (higher 
// z-index means the object is in front of other objects), sets by 0. You can manually set it as what you want.
auto listener = std::make_unique<MouseEventListener>(shape, ObjectBoundary::createBoundaryFrom(shape));

// And register callback for sf::MouseButtonPressed. It will be executed when press mouse button.
listener->on_mouse_button_pressed = [&](auto &sender, const auto &event){
    // sender: MouseEventListener whose callback is executed.
    // event: sf::Event::MouseButtonEvent, which has button and cursor position.
    
    std::cout << "Mouse pressed on " << static_cast<void*>(&sender) << " at (" << event.x << ", " << event.y << ")\n";
};
```

3. Make `MouseEventSystem` listens `sf::Event` polled by window. Since only callback for mouse pressing is registered,
it is only necessary for listen `sf::Event::MouseButtonPressed` event.

```c++
for (sf::Event event { }; window.pollEvent(event);) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
            system.executeMouseEvent<sf::Event::MouseButtonPressed>(event.mouseButton);
            break;
        
        // and any other event...
    }
}
```

4. Now draw your objects and test if they print messages when clicking them. If you want to render objects by its z-index (so
higher z-indexed object is in front of other), you can iterate system's listeners and render them. Listeners are always sorted
with ascending z-index.

```c++
for (auto &listener : system.getListeners()){
    window.draw(*dynamic_cast<const sf::Drawable*>(&listener->target));
}
```

You can find more sample from [ManyConvexes](https://github.com/stripe2933/SFML.MouseEventListener/tree/master/sample/ManyConvexes) 
(make objects pannable using `MouseEventListener`) and [Shapes](https://github.com/stripe2933/SFML.MouseEventListener/tree/master/sample/Shapes)
(create an `ObjectBoundary` by combining multiple `ObjectBoundary`s to make non-regular shaped target be able to listen.)
