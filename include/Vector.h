#ifndef PATHTRACER_VECTOR_H
#define PATHTRACER_VECTOR_H


#include <array>
#include <initializer_list>
#include <format>

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
                data_[index] = elems;
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


    private:
        std::array<T, N> data_;
    };

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
