#pragma once
#include "MathUtil.h"

namespace Fire
{
  struct Vector4
  {
    Vector4();
    //Vector4(const Vector4& rhs);
    Vector4(float x, float y, float z, float w);
    Vector4(float v[4]);
    //~Vector4();

    Vector4& operator=(const Vector4& rhs);

    float& operator[](const int& ind);
    const float& operator[](const int& ind) const;
    Vector4 operator-(const Vector4& rhs) const;
    Vector4 operator-() const;
    Vector4& operator-=(const Vector4& rhs);
    Vector4 operator+(const Vector4& rhs) const;
    Vector4& operator+=(const Vector4& rhs);
    Vector4 operator*(float scalar) const;
    Vector4& operator*=(float scalar);
    Vector4 operator/(float scalar) const;
    Vector4& operator/=(float scalar);
    bool operator==(const Vector4& rhs) const;
    bool operator!=(const Vector4& rhs) const;

    void Zero();
    void Set(float x, float y, float z, float w);

    static bool ApproxEqual(const Vector4& one, const Vector4& two, float epsilon = Math::Epsilon);
    static float Dot(const Vector4& one, const Vector4& two);
    // 3d cross product
    static Vector4 Cross(const Vector4& one, const Vector4& two);
    static float AngleBetween(const Vector4& one, const Vector4& two);
    static float RotateAround(const Vector4& rotator, const Vector4& axis, float amount);

    union 
    {
      struct
      {
        float r;
        float g;
        float b;
        float a;
      };
      struct
      {
        float x;
        float y;
        float z;
        float w;
      };
      float v[4];
    };
  };
}