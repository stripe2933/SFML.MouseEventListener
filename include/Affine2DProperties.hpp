//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#ifndef SFML_MOUSEEVENTLISTENER_AFFINE2DPROPERTIES_HPP
#define SFML_MOUSEEVENTLISTENER_AFFINE2DPROPERTIES_HPP

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

class Affine2DProperties{
public:
    const sf::Angle rotation; // Rotation angle.
    const sf::Vector2f scale; // Scaling factor (x and y).
    const float shear_x;      // Shear factor of x.

    Affine2DProperties(const sf::Angle &rotation, const sf::Vector2f &scale, float shear_x);
    Affine2DProperties(const Affine2DProperties &source) = default;
    explicit Affine2DProperties(const sf::Transform &transform);

private:
    static Affine2DProperties getAffine2DPropertiesFromSFMLTransform(const sf::Transform &transform);
};

#endif //SFML_MOUSEEVENTLISTENER_AFFINE2DPROPERTIES_HPP
