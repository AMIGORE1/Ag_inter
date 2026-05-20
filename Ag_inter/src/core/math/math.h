#pragma once
#include <iostream>
#include <string>

struct Vector2 {
    float x, y;

    Vector2(float x = 0, float y = 0);

    float magnitude() const;
    Vector2 normalize() const;

    static float Distance(const Vector2& v1, const Vector2& v2);

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
    std::string to_string();
};

struct Vector3 {
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0);

    float& operator[](int index);
    const float& operator[](int index) const;

    bool operator!=(const Vector3& rhs) const;
    bool operator==(const Vector3& rhs) const;

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;

    static float distance(const Vector3& v1, const Vector3& v2);
    static Vector3 cross(const Vector3& v1, const Vector3& v2);

    operator Vector2() const;
    void normalize();
    float length() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
    std::string to_string();
};

struct Vector4 {
    float x, y, z, w;

    Vector4();
    Vector4(float x, float y, float z, float w);

    operator Vector3() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector4& v);
};

struct Matrix4x4 {
    float m00, m10, m20, m30;
    float m01, m11, m21, m31;
    float m02, m12, m22, m32;
    float m03, m13, m23, m33;

    Vector4 operator*(const Vector4& vector) const;
};

struct QAngle_t {
    float pitch, yaw, roll;

    QAngle_t();
    QAngle_t(float _pitch, float _yaw, float _roll);
};