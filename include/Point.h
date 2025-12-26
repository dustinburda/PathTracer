#ifndef PATHTRACER_POINT_H
#define PATHTRACER_POINT_H

#include "Vector.h"

#include <array>
#include <cmath>
#include <concepts>
#include <cstring>
#include <format>
#include <initializer_list>
#include <stdexcept>
#include <sstream>
#include <type_traits>

namespace math {
    template<typename T, std::size_t N>
        requires (N > 0) && (std::integral<T> || std::floating_point<T>)
    class Point {
    public:

        Point() {
            std::memset(data_.data(), 0, sizeof (T) * N);
        }

        Point(std::initializer_list<T> elems) {
            if (elems.size() != N)
                throw std::logic_error(
                        std::format("Point of size {} cannot be initialized with {} elements", N, elems.size())
                );

            for (int index = 0; auto& elem : elems) {
                data_[index] = elem;
                index++;
            }
        }

        T operator[](std::size_t index) const {
            if (index < 0 || index >= N)
                throw std::logic_error(
                        std::format("Point of size {} cannot be accessed at index {}", N, index)
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

        Point<T, N> operator-() const {
            return *this * (-1.0f);
        }

        Vector<T, N> ToVector() const {
            return Vector<T, N>(data_);
        }



        std::string toString() const {
            std::string type = std::is_same_v<T, int>    ? "int" :
                               std::is_same_v<T, float>  ? "float" :
                               std::is_same_v<T, double> ? "double" :
                               "none";

            std::stringstream ss;

            ss << "Debugging Point:\n";
            ss << std::format("Dimension: {}\n", N);
            ss << std::format("Type: {}\n", type);
            ss << std::format("Data: {}\n", data_);
            ss << "\n";


            return ss.str();
        }

    private:
        std::array<T, N> data_;
    };
}

#endif //PATHTRACER_POINT_H
