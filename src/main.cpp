#include <iostream>

#include "../include/Vector.h"
#include "../include/Point.h"

int main() {
    math::Vec2f v1{1.0, 1.0};
    std::cout << v1.toString();

    math::Vec2f v2{-1.2, -1.3};
    std::cout << v2.toString();

    math::Vec2f v1_negate = -v1;
    std::cout << v1_negate.toString();

    math::Vec2f v3 = v1 + v2;
    std::cout << v3.toString();



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
