#include "math.h"
#include <cmath>
#include <stdexcept>


Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const {
    float mag = magnitude();
    return Vector2(x / mag, y / mag);
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return std::sqrt(dx * dx + dy * dy);
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::string Vector2::to_string() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}




Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float& Vector3::operator[](int index) {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range in Vector3");
    }
}

const float& Vector3::operator[](int index) const {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Index out of range in Vector3");
    }
}

bool Vector3::operator!=(const Vector3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

bool Vector3::operator==(const Vector3& rhs) const {
    return !(*this != rhs);
}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

float Vector3::distance(const Vector3& v1, const Vector3& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

Vector3::operator Vector2() const {
    return Vector2(x, y);
}

void Vector3::normalize() {
    float n = std::sqrt(x * x + y * y + z * z);
    x /= n;
    y /= n;
    z /= n;
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::string Vector3::to_string() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}



Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::operator Vector3() const {
    return Vector3(x, y, z);
}

std::ostream& operator<<(std::ostream& os, const Vector4& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}



Vector4 Matrix4x4::operator*(const Vector4& vector) const {
    Vector4 result;
    result.x = m00 * vector.x + m01 * vector.y + m02 * vector.z + m03 * vector.w;
    result.y = m10 * vector.x + m11 * vector.y + m12 * vector.z + m13 * vector.w;
    result.z = m20 * vector.x + m21 * vector.y + m22 * vector.z + m23 * vector.w;
    result.w = m30 * vector.x + m31 * vector.y + m32 * vector.z + m33 * vector.w;
    return result;
}



QAngle_t::QAngle_t() : pitch(0.0f), yaw(0.0f), roll(0.0f) {}

QAngle_t::QAngle_t(float _pitch, float _yaw, float _roll)
    : pitch(_pitch), yaw(_yaw), roll(_roll) {
}