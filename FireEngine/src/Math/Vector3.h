#pragma once
#include "MathUtil.h"

namespace Fire
{
  struct Vector3
  {
    Vector3();
    //Vector3(const Vector3& rhs);
    Vector3(float x, float y, float z);
    Vector3(float v[3]);
    //~Vector3();

    Vector3& operator=(const Vector3& rhs);
    float& operator[](const int& ind);
    float const& operator[](const int& ind) const;
    Vector3 operator-(const Vector3& rhs) const;
    Vector3& operator-=(const Vector3& rhs);
    Vector3 operator+(const Vector3& rhs) const;
    Vector3& operator+=(const Vector3& rhs);
    Vector3 operator*(float scalar) const;
    Vector3& operator*=(float scalar);
    Vector3 operator/(float scalar) const;
    Vector3& operator/=(float scalar);
    bool operator==(const Vector3& rhs) const;
    bool operator!=(const Vector3& rhs) const;

    void Zero();


    static bool ApproxEqual(const Vector3& one, const Vector3& two, float epsilon = Math::Epsilon);
    static float Dot(const Vector3& one, const Vector3& two);
    // 3d cross product
    static Vector3 Cross(const Vector3& one, const Vector3& two);
    static float AngleBetween(const Vector3& one, const Vector3& two);
    static float RotateAround(const Vector3& rotator, const Vector3& axis, float amount);

    union 
    {
      struct
      {
        float r;
        float g;
        float b;
      };
      struct
      {
        float x;
        float y;
        float z;
      };
      float v[3];
    };
  };
}