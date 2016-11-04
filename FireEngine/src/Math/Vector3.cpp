#include "Precompiled.h"
#include "Vector3.h"

namespace Fire
{
 Vector3::Vector3()
 {
   
 }

  Vector3::Vector3(
    float inx, 
    float iny, 
    float inz)
  : x(inx),
    y(iny),
    z(inz)
  {

  }

  Vector3::Vector3(float inv[3])
  : x(inv[0]),
    y(inv[1]),
    z(inv[2])
  {
  }

  //Vector3::~Vector3()
  //{
  //  
  //} 

  Vector3& Vector3::operator=(const Vector3& rhs)
  {
    if(&rhs != this)
    {
      memcpy(&x, &rhs.x, sizeof(rhs));
    }

    return *this;
  }

  float& Vector3::operator[](const int& ind)
  {
    return v[ind];
  }

  float const& Vector3::operator[](const int& ind) const
  {
    return v[ind];
  }

  Vector3 Vector3::operator-(const Vector3& rhs) const
  {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Vector3 Vector3::operator-() const
  {
    return Vector3(-x, -y, -z);
  }

  Vector3& Vector3::operator-=(const Vector3& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  Vector3 Vector3::operator+(const Vector3& rhs) const
  {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Vector3& Vector3::operator+=(const Vector3& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vector3 Vector3::operator*(float scalar) const
  {
    return Vector3(x * scalar, y * scalar, z * scalar);
  }

  Vector3& Vector3::operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  Vector3 Vector3::operator/(float scalar) const
  {
    return Vector3(x / scalar, y / scalar, z / scalar);
  }

  Vector3& Vector3::operator/=(float scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  bool Vector3::operator==(const Vector3& rhs) const
  {
    return 
      (x == rhs.x) &&
      (y == rhs.y) &&
      (z == rhs.z);
  }

  bool Vector3::operator!=(const Vector3& rhs) const
  {
    return !(*this == rhs);
  }

  void Vector3::Zero()
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  void Vector3::Normalize()
  {
    float len = sqrt((x * x) + (y * y) + (z * z));
    if (abs(len) > 0.0)
    {
      x /= len;
      y /= len;
      z /= len;
    }
  }

  Vector3 Vector3::GetNormalized()
  {
    Vector3 newVec(*this);
    newVec.Normalize();
    return newVec;
  }

  void Vector3::Set(float in_x, float in_y, float in_z)
  {
    x = in_x;
    y = in_y;
    z = in_z;
  }
  bool Vector3::ApproxEqual(const Vector3& one, const Vector3& two, float epsilon)
  {
    return 
      (one.x <= two.x + epsilon) && (one.x >= two.x - epsilon) &&
      (one.y <= two.y + epsilon) && (one.y >= two.y - epsilon) &&
      (one.z <= two.z + epsilon) && (one.z >= two.z - epsilon);
  }
  
  float Vector3::Dot(const Vector3& one, const Vector3& two)
  {
    return one.x * two.x + one.y * two.y + one.z * two.z;
  }


  Vector3 Vector3::Cross(const Vector3& one, const Vector3& two)
  {
    return Vector3(
      one.y * two.z - one.z * two.y,
      one.z * two.x - one.x * two.z,
      one.x * two.y - one.y * two.x
    );
  }


}