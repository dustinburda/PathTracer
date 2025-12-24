#ifndef PATHTRACER_VECTOR_H
#define PATHTRACER_VECTOR_H


#include <array>
#include <cmath>
#include <concepts>
#include <cstring>
#include <stdexcept>
#include <format>
#include <initializer_list>
#include <sstream>
#include <type_traits>



namespace math {

    template<typename T, std::size_t N>
    class Vector {
    public:
        Vector() {
            std::memset(data_.data(), 0, sizeof (T) * N);
        }

        Vector(std::initializer_list<T> elems) {
            if (elems.size() != N)
                throw std::logic_error(
                        std::format("Vector of size {} cannot be initialized with {} elements", N, elems.size())
                );

            for (int index = 0; auto& elem : elems) {
                data_[index] = elem;
                index++;
            }
        }

        T operator[](std::size_t index) const {
            if (index < 0 || index >= N)
                throw std::logic_error(
                    std::format("Vector of size {} cannot be accessed at index {}", N, index)
                );

            return data_[index];
        }

        T& operator[](std::size_t index) {
            if (index < 0 || index >= N)
                throw std::logic_error(
                        std::format("Vector of size {} cannot be accessed at index {}", N, index)
            );

            return data_[index];
        }

        Vector<T, N> operator-() const {
            return *this * (-1.0f);
        }

        Vector<T, N>& operator+=(Vector<T, N>& other) {
            for (std::size_t i = 0; i < N; i++) {
                data_[i] += other.data_[i];
            }

            return *this;
        }

        Vector<T, N>& operator-=(Vector<T, N>& other) {
            for (std::size_t i = 0; i < N; i++) {
                data_[i] -= other.data_[i];
            }

            return *this;
        }

        Vector<T, N>& operator*=(float t) {
            T t_cast = static_cast<T>(t);

            for (std::size_t i = 0; i < N; i++) {
                data_[i] *= t_cast;
            }

            return *this;
        }

        Vector<T, N>& operator/=(float t) {
            T t_cast = static_cast<T>(t);

            for (std::size_t i = 0; i < N; i++) {
                data_[i] /= t_cast;
            }

            return *this;
        }

        float LengthSquared() const {
            float norm = 0;

            for (auto& elem : data_) {
                norm += elem * elem;
            }

            return norm;
        }

        float Length() const {
            return std::sqrt(LengthSquared());
        }

        std::string toString() const {
            std::string type = std::is_same_v<T, int>    ? "int" :
                               std::is_same_v<T, float>  ? "float" :
                               std::is_same_v<T, double> ? "double" :
                                                           "none";

            std::stringstream ss;

            ss << "Debugging Vector:\n";
            ss << std::format("Dimension: {}\n", N);
            ss << std::format("Type: {}\n", type);
            ss << std::format("Data: {}\n", data_);
            ss << "\n";


            return ss.str();
        }


    private:
        std::array<T, N> data_;
    };

    template<typename T, std::size_t N>
    Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        Vector<T, N> sum;

        for (int i = 0; i < N; i++)
            sum[i] = v1[i] + v2[i];

        return sum;
    }

    template<typename T, std::size_t N>
    Vector<T, N> operator-(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        return v1 + (-v2);
    }

    template<typename T, std::size_t N>
    Vector<T, N> operator*(const Vector<T, N>& v, float t) {
        Vector<T, N> mult;

        for (int i = 0; i < N; i++)
            mult[i] = v[i] * t;

        return mult;
    }

    template<typename T, std::size_t N>
    Vector<T, N> operator*(float t, const Vector<T, N>& v) {
        return v * t;
    }

    template<typename T, std::size_t N>
    bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2)
        requires std::floating_point<T>
    {
        const T EPSILON = static_cast<T>(10e-4);

        for (std::size_t i = 0; i < N; i++) {
            if (std::abs(v1[i] - v2[i]) > EPSILON)
                return false;
        }

        return true;
    }

    template<typename T, std::size_t N>
    bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2)
        requires std::integral<T>
    {
        for (std::size_t i = 0; i < N; i++) {
            if (v1[i] != v2[i])
                return false;
        }

        return true;
    }


    using Vec2d = Vector<double, 2>;
    using Vec3d = Vector<double, 3>;
    using Vec4d = Vector<double, 4>;
    using Vec2f = Vector<float, 2>;
    using Vec3f = Vector<float, 3>;
    using Vec4f = Vector<float, 4>;
    using Vec2i = Vector<int, 2>;
    using Vec3i = Vector<int, 3>;
    using Vec4i = Vector<int, 4>;

}


#endif //PATHTRACER_VECTOR_H
