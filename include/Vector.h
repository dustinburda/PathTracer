#ifndef PATHTRACER_VECTOR_H
#define PATHTRACER_VECTOR_H

#if defined(__aarch64__)
    #include <arm_neon.h>
#elif defined(__x86_64__)
    #include <immintrin.h>
#endif

#include <array>

namespace math {

    class Vec4 {
    public:
        explicit Vec4(double d) : data_{d,d,d,d} {}
        explicit Vec4(double x, double y, double z, double h) : data_{x,y,z,h} {}

        Vec4 operator+(const Vec4& other) {

        }

        Vec4 operator-(const Vec4& other) {

        }

    private:
        std::array<double, 4> data_;
    };

    class Vec3 {
    public:
        explicit Vec3(double d);
        explicit Vec3();

    private:
        std::array<double, 3> data_;
    };

    class Vec2 {
    public:
        explicit Vec2(double d);
        explicit Vec2();

    private:
        std::array<double, 2> data_;
    };
}


#endif //PATHTRACER_VECTOR_H
