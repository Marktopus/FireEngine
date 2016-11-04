#pragma once

#include "Vector4.h"

namespace Fire
{
  struct Vector3;
  struct Matrix4
  {
    Matrix4();
    Matrix4(Vector4 inv[4]);
    Matrix4(
      const Vector4& inv0, 
      const Vector4& inv1, 
      const Vector4& inv2, 
      const Vector4& inv3);
    Matrix4(
      float m0, float m1, float m2, float m3,
      float m4, float m5, float m6, float m7,
      float m8, float m9, float m10, float m11,
      float m12, float m13, float m14, float m15);
    Matrix4(float inm[16]);
    //~Matrix4();

    Matrix4 operator=(const Matrix4& rhs);
    Matrix4 operator*(const Matrix4& rhs) const;
    Matrix4& operator*=(const Matrix4& rhs);

    Matrix4& Identity();
    Matrix4& Zero();
    Matrix4& Transpose();
    Matrix4 GetTranspose() const;

    //Graphics inverse
    Matrix4& GInverse();
    Matrix4 GetGInverse() const;

    Matrix4& Scale(const Vector3& rhs);
    Matrix4 GetScaled(const Vector3& rhs) const;
    Matrix4& Scale(float x, float y, float z);
    Matrix4 GetScaled(float x, float y, float z) const;
    Matrix4& Scale(float scalar);
    Matrix4 GetScaled(float scalar) const;

    Matrix4& RotateX(float rot);
    Matrix4 GetRotatedX(float rot) const;
    Matrix4& RotateY(float rot);
    Matrix4 GetRotatedY(float ros) const;
    Matrix4& RotateZ(float ros);
    Matrix4 GetRotatedZ(float ros) const;
    Matrix4& Rotate(const Vector3& rhs);
    Matrix4 GetRotated(const Vector3& rhs) const;
    Matrix4& Rotate(float x, float y, float z);
    Matrix4 GetRotated(float x, float y, float z) const;

    Matrix4& Translate(const Vector3& rhs);
    Matrix4 GetTranslated(const Vector3& rhs);
    Matrix4 Translate(float x, float y, float z) const;
    Matrix4 GetTranslated(float x, float y, float z) const;

    // assumes dir vectors are normalized
    Matrix4& ViewTransform(const Vector3& right, const Vector3& up, const Vector3& forward, const Vector3& pos);
    Matrix4& PerspectiveTransform(float fov = Math::Pi/2.0f, float nearPlane = 0.001f, float farPlane = 10000.0f, float aspect = 800/600);
    Matrix4& OrthographicTransform(float left, float right, float top, float bottom);

    
    Vector4 Transform(const Vector4& vec);
    union 
    {
      float m[16];
      struct 
      {
        float 
          m0,  m1,  m2,  m3,
          m4,  m5,  m6,  m7,
          m8,  m9,  m10, m11,
          m12, m13, m14, m15;
      };
      struct 
      {
        Vector4 v[4];
      };
    };
  };
}

