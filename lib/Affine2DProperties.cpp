//
// Created by LEE KYOUNGHEON on 2023/02/01.
//

#include <Affine2DProperties.hpp>

Affine2DProperties::Affine2DProperties(const sf::Angle &rotation, const sf::Vector2f &scale, float shear_x) : rotation(rotation),
                                                                                                              scale(scale),
                                                                                                              shear_x(shear_x) { }

Affine2DProperties::Affine2DProperties(const sf::Transform &transform) : Affine2DProperties { getAffine2DPropertiesFromSFMLTransform(transform) } { }

Affine2DProperties Affine2DProperties::getAffine2DPropertiesFromSFMLTransform(const sf::Transform &transform) {
    /* For 2D Affine matrix [[a11, a12], [a21, a22]] without translation,
     * the rotated angle is:
     * theta = atan2(a21, a11).
     *
     * The x-scale factor sx is:
     * sx = sqrt(a11^2 + a21^2).
     *
     * The y-scale factor sy and x-share factor m could be obtained by system of equations.
     * m*sy = a12 * cos(theta) + a22 * sin(theta)
     * sy = ((m*sy) * cos(theta) - a12) / sin(theta) if sin(theta) != 0,
     *      (a22 - (m*sy) * sin(theta)) / cos(theta) otherwise.
     * m = (m*sy) / sy;
     *
     * By Stéphane Laurent from https://math.stackexchange.com/questions/612006/decomposing-an-affine-transformation
     * */

    // Note: SFML transform matrix is column-ordered.
    auto raw_matrix = transform.getMatrix();
    auto a11 = raw_matrix[0],
            a12 = raw_matrix[4],
            a21 = raw_matrix[1],
            a22 = raw_matrix[5];

    auto theta = std::atan2(a21, a11);
    auto sx = std::hypot(a11, a21);

    auto cos = std::cos(theta), sin = std::sin(theta);
    auto msy = a12 * cos + a22 * sin;
    auto sy = sin != 0 ? (msy * cos - a12) / sin : (a22 - msy * sin) / cos;
    auto m = msy / sy;

    return { sf::radians(theta), sf::Vector2f { sx, sy }, m };
}
