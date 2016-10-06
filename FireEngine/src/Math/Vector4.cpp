#include "Precompiled.h"
#include "Vector4.h"

namespace Fire
{
  Vector4::Vector4()
  {
    
  }

  Vector4::Vector4(
    float inx, 
    float iny, 
    float inz, 
    float inw)
  : x(inx),
    y(iny),
    z(inz),
    w(inw)
  {

  }

  Vector4::Vector4(float inv[4])
  : x(inv[0]),
    y(inv[1]),
    z(inv[2]),
    w(inv[3])
  {
  }

  //Vector4::~Vector()
  //{

  //}

  Vector4& Vector4::operator=(const Vector4& rhs)
  {
    if(&rhs != this)
    {
      memcpy(&x, &rhs.x, sizeof(rhs));
    }

    return *this;
  }

  float& Vector4::operator[](const int& ind)
  {
    return v[ind];
  }

  const float& Vector4::operator[](const int& ind) const
  {
    return v[ind];
  }

  Vector4 Vector4::operator-(const Vector4& rhs) const
  {
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
  }

  Vector4& Vector4::operator-=(const Vector4& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  Vector4 Vector4::operator+(const Vector4& rhs) const
  {
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
  }

  Vector4& Vector4::operator+=(const Vector4& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  Vector4 Vector4::operator*(float scalar) const
  {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
  }

  Vector4& Vector4::operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  Vector4 Vector4::operator/(float scalar) const
  {
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
  }
  Vector4& Vector4::operator/=(float scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }

  bool Vector4::operator==(const Vector4& rhs) const
  {
    return 
      (x == rhs.x) &&
      (y == rhs.y) &&
      (z == rhs.z) &&
      (w == rhs.w);
  }

  bool Vector4::operator!=(const Vector4& rhs) const
  {
    return !(*this == rhs);
  }

  void Vector4::Zero()
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
  }

  bool Vector4::ApproxEqual(const Vector4& one, const Vector4& two, float epsilon)
  {
    return 
      (one.x <= two.x + epsilon) && (one.x >= two.x - epsilon) &&
      (one.y <= two.y + epsilon) && (one.y >= two.y - epsilon) &&
      (one.z <= two.z + epsilon) && (one.z >= two.z - epsilon) &&
      (one.w <= two.w + epsilon) && (one.w >= two.w - epsilon);
  }
  
  float Vector4::Dot(const Vector4& one, const Vector4& two)
  {
    return one.x * two.x + one.y * two.y + one.z * two.z + one.w * two.w;
  }


  Vector4 Vector4::Cross(const Vector4& one, const Vector4& two)
  {
    return Vector4(
      one.y * two.z - one.z * two.y,
      one.z * two.x - one.x * two.z,
      one.x * two.y - one.y * two.x,
      0.0f
    );
  }


}