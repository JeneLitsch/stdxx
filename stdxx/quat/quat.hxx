#pragma once
#include <cmath>
#include <ostream>

namespace stx {
template<typename T>
    struct quat {
        template<typename Vector, typename Radians>
        static quat<T> from_axis_angle(Vector axis, Radians angle_radians) {
            return quat<T> {
                .x = axis.x * std::sin(angle_radians/2), 
                .y = axis.y * std::sin(angle_radians/2), 
                .z = axis.z * std::sin(angle_radians/2),
                .w = std::cos(angle_radians/2),
            };
        }
        T x, y, z, w;
    };

    using quatf = quat<float>;
    using quatd = quat<double>;

    template<typename T>
    quat<T> operator*(const quat<T> & q, const quat<T> & p) {
        return quat<T> {
            .x = (q.w * p.x) + (q.x * p.w) + (q.y * p.z) - (q.z * p.y),
            .y = (q.w * p.y) - (q.x * p.z) + (q.y * p.w) + (q.z * p.x),
            .z = (q.w * p.z) + (q.x * p.y) - (q.y * p.x) + (q.z * p.w),
            .w = (q.w * p.w) - (q.x * p.x) - (q.y * p.y) - (q.z * p.z),
        };
    }

    template<typename T>
    quat<T> operator*(const quat<T> & q, const T f) {
        return quat<T> {
            .x = q.x * f, 
            .y = q.y * f, 
            .z = q.z * f, 
            .w = q.w * f, 
        };
    }

    template<typename T>
    quat<T> operator*(const T f, const quat<T> & q) {
        return q * f;
    }

    template<typename T>
    quat<T> operator/(const quat<T> & q, const T f) {
        return q * (1 / f);
    }

    template<typename T>
    quat<T> operator/(const T f, const quat<T> & q) {
        return q * (1 / f);
    }

    template<typename T>
    T length (const quat<T> & q) {
        return std::sqrt((q.x*q.x) + (q.y*q.y) + (q.x*q.z) + (q.w*q.w));
    }

    template<typename T>
    T normalied (const quat<T> & q) {
        return q / length(q);
    }

    template<typename T>
	std::ostream & operator<<(std::ostream & out, const quat<T> & q) {
		return out  << "{" << q.x << "i," << q.y << "j," << q.z << "k," << q.w << "}";
	}
}