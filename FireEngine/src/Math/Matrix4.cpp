#include "Precompiled.h"
#include "Matrix4.h"
#include "Vector3.h"
namespace Fire
{
  Matrix4::Matrix4()
  {
    //empty
  }

  Matrix4::Matrix4(Vector4 inv[4])
  {

  }

  Matrix4::Matrix4(
    const Vector4& inv0, 
    const Vector4& inv1, 
    const Vector4& inv2, 
    const Vector4& inv3)
  : m0(inv0[0]),  m1(inv0[1]),  m2(inv0[2]),  m3(inv0[3]),
    m4(inv1[0]),  m5(inv1[1]),  m6(inv1[2]),  m7(inv1[3]),
    m8(inv2[0]),  m9(inv2[1]),  m10(inv2[2]), m11(inv2[3]),
    m12(inv3[0]), m13(inv3[1]), m14(inv3[2]), m15(inv3[3])
  {
    
  }
  
  Matrix4::Matrix4(
    float inm0,  float inm1,  float inm2,  float inm3,
    float inm4,  float inm5,  float inm6,  float inm7,
    float inm8,  float inm9,  float inm10, float inm11,
    float inm12, float inm13, float inm14, float inm15)
  : m0(inm0), m1(inm1), m2(inm2), m3(inm3),
    m4(inm4), m5(inm5), m6(inm6), m7(inm7),
    m8(inm8), m9(inm9), m10(inm10), m11(inm11),
    m12(inm12), m13(inm13), m14(inm14), m15(inm15)
  {
    
  }

  Matrix4::Matrix4(float inm[16])
  : m0(inm[0]), m1(inm[1]), m2(inm[2]), m3(inm[3]),
    m4(inm[4]), m5(inm[5]), m6(inm[6]), m7(inm[7]),
    m8(inm[8]), m9(inm[9]), m10(inm[10]), m11(inm[11]),
    m12(inm[12]), m13(inm[13]), m14(inm[14]), m15(inm[15])
  {

  }
  //Matrix4::~Matrix4()
  //{

  //}

  
  Matrix4 Matrix4::operator=(const Matrix4& rhs)
  {
    if(&rhs != this)
    {
      memcpy(m, rhs.m, sizeof(rhs));
    }
    return *this;
  }

  Matrix4 Matrix4::operator*(const Matrix4& rhs) const
  {
    // [0 1] [0 1]  0 * 0 + 1 * 2, 0 * 1 + 1 * 3
    // [2 3] [2 3]  2 * 0 + 3 * 2, 2 * 1 + 3 * 3
    //
    //
    return Matrix4(
      rhs.v[0][0] * v[0][0] + rhs.v[1][0] * v[0][1] + rhs.v[2][0] * v[0][2] + rhs.v[3][0] * v[0][3],
      rhs.v[0][1] * v[0][0] + rhs.v[1][1] * v[0][1] + rhs.v[2][1] * v[0][2] + rhs.v[3][1] * v[0][3],
      rhs.v[0][2] * v[0][0] + rhs.v[1][2] * v[0][1] + rhs.v[2][2] * v[0][2] + rhs.v[3][2] * v[0][3],
      rhs.v[0][3] * v[0][0] + rhs.v[1][3] * v[0][1] + rhs.v[2][3] * v[0][2] + rhs.v[3][3] * v[0][3],

      rhs.v[0][0] * v[1][0] + rhs.v[1][0] * v[1][1] + rhs.v[2][0] * v[1][2] + rhs.v[3][0] * v[1][3],
      rhs.v[0][1] * v[1][0] + rhs.v[1][1] * v[1][1] + rhs.v[2][1] * v[1][2] + rhs.v[3][1] * v[1][3],
      rhs.v[0][2] * v[1][0] + rhs.v[1][2] * v[1][1] + rhs.v[2][2] * v[1][2] + rhs.v[3][2] * v[1][3],
      rhs.v[0][3] * v[1][0] + rhs.v[1][3] * v[1][1] + rhs.v[2][3] * v[1][2] + rhs.v[3][3] * v[1][3],

      rhs.v[0][0] * v[2][0] + rhs.v[1][0] * v[2][1] + rhs.v[2][0] * v[2][2] + rhs.v[3][0] * v[2][3],
      rhs.v[0][1] * v[2][0] + rhs.v[1][1] * v[2][1] + rhs.v[2][1] * v[2][2] + rhs.v[3][1] * v[2][3],
      rhs.v[0][2] * v[2][0] + rhs.v[1][2] * v[2][1] + rhs.v[2][2] * v[2][2] + rhs.v[3][2] * v[2][3],
      rhs.v[0][3] * v[3][0] + rhs.v[1][3] * v[3][1] + rhs.v[2][3] * v[3][2] + rhs.v[3][3] * v[3][3],

      rhs.v[0][0] * v[3][0] + rhs.v[1][0] * v[3][1] + rhs.v[2][0] * v[3][2] + rhs.v[3][0] * v[3][3],
      rhs.v[0][1] * v[3][0] + rhs.v[1][1] * v[3][1] + rhs.v[2][1] * v[3][2] + rhs.v[3][1] * v[3][3],
      rhs.v[0][2] * v[3][0] + rhs.v[1][2] * v[3][1] + rhs.v[2][2] * v[3][2] + rhs.v[3][2] * v[3][3],
      rhs.v[0][3] * v[2][0] + rhs.v[1][3] * v[2][1] + rhs.v[2][3] * v[2][2] + rhs.v[3][3] * v[2][3]);
/*
    return Matrix4(
      v[0][0] * rhs.v[0][0] + v[1][0] * rhs.v[0][1] + v[2][0] * rhs.v[0][2] + v[3][0] * rhs.v[0][3],
      v[0][1] * rhs.v[0][0] + v[1][1] * rhs.v[0][1] + v[2][1] * rhs.v[0][2] + v[3][1] * rhs.v[0][3],
      v[0][2] * rhs.v[0][0] + v[1][2] * rhs.v[0][1] + v[2][2] * rhs.v[0][2] + v[3][2] * rhs.v[0][3],
      v[0][3] * rhs.v[0][0] + v[1][3] * rhs.v[0][1] + v[2][3] * rhs.v[0][2] + v[3][3] * rhs.v[0][3],

      v[0][0] * rhs.v[1][0] + v[1][0] * rhs.v[1][1] + v[2][0] * rhs.v[1][2] + v[3][0] * rhs.v[1][3],
      v[0][1] * rhs.v[1][0] + v[1][1] * rhs.v[1][1] + v[2][1] * rhs.v[1][2] + v[3][1] * rhs.v[1][3],
      v[0][2] * rhs.v[1][0] + v[1][2] * rhs.v[1][1] + v[2][2] * rhs.v[1][2] + v[3][2] * rhs.v[1][3],
      v[0][3] * rhs.v[1][0] + v[1][3] * rhs.v[1][1] + v[2][3] * rhs.v[1][2] + v[3][3] * rhs.v[1][3],

      v[0][0] * rhs.v[2][0] + v[1][0] * rhs.v[2][1] + v[2][0] * rhs.v[2][2] + v[3][0] * rhs.v[2][3],
      v[0][1] * rhs.v[2][0] + v[1][1] * rhs.v[2][1] + v[2][1] * rhs.v[2][2] + v[3][1] * rhs.v[2][3],
      v[0][2] * rhs.v[2][0] + v[1][2] * rhs.v[2][1] + v[2][2] * rhs.v[2][2] + v[3][2] * rhs.v[2][3],
      v[0][3] * rhs.v[3][0] + v[1][3] * rhs.v[3][1] + v[2][3] * rhs.v[3][2] + v[3][3] * rhs.v[3][3],

      v[0][0] * rhs.v[3][0] + v[1][0] * rhs.v[3][1] + v[2][0] * rhs.v[3][2] + v[3][0] * rhs.v[3][3],
      v[0][1] * rhs.v[3][0] + v[1][1] * rhs.v[3][1] + v[2][1] * rhs.v[3][2] + v[3][1] * rhs.v[3][3],
      v[0][2] * rhs.v[3][0] + v[1][2] * rhs.v[3][1] + v[2][2] * rhs.v[3][2] + v[3][2] * rhs.v[3][3],
      v[0][3] * rhs.v[2][0] + v[1][3] * rhs.v[2][1] + v[2][3] * rhs.v[2][2] + v[3][3] * rhs.v[2][3]);*/
  }

  Matrix4& Matrix4::operator*=(const Matrix4& rhs)
  { 
    *this = *this * rhs;
    return *this;
  }

  Matrix4& Matrix4::Identity()
  {
    Zero();
    v[0][0] = 1.0;    
    v[1][1] = 1.0;    
    v[2][2] = 1.0;    
    v[3][3] = 1.0;
    return *this;
  }

  Matrix4& Matrix4::Zero()
  {
    memset(m, 0, sizeof(m));
    return *this;
  }

  Matrix4& Matrix4::Transpose()
  {
    std::swap(v[0][1], v[1][0]);
    std::swap(v[0][2], v[2][0]);
    std::swap(v[0][3], v[3][0]);
    
    std::swap(v[1][2], v[2][1]);
    std::swap(v[1][3], v[3][1]);
    std::swap(v[2][3], v[3][2]);
    return *this;
  }

  Matrix4 Matrix4::GetTranspose() const
  {
    Matrix4 toRet(*this);
    return toRet.Transpose();
  }

  Matrix4& Matrix4::GInverse()
  {
    return *this;
  }

  Matrix4 Matrix4::GetGInverse() const
  {
    Matrix4 toRet(*this);
    return toRet.GInverse();
  }


  Matrix4& Matrix4::Scale(const Vector3& rhs)
  {
    return Scale(rhs[0], rhs[1], rhs[2]);
  }

  Matrix4 Matrix4::GetScaled(const Vector3& rhs) const
  {
    Matrix4 toRet(*this);
    return toRet.Scale(rhs);
  }

  Matrix4& Matrix4::Scale(float x, float y, float z)
  {
    v[0][0] *= x;
    v[1][1] *= y;
    v[2][2] *= z;
    return *this;
  }

  Matrix4 Matrix4::GetScaled(float x, float y, float z) const
  {
    Matrix4 toRet(*this);
    return toRet.Scale(x, y, z);
  }

  Matrix4& Matrix4::Scale(float scalar)
  {
    return Scale(scalar, scalar, scalar);
  }

  Matrix4 Matrix4::GetScaled(float scalar) const
  {
    Matrix4 toRet(*this);
    return toRet.Scale(scalar);
  }


  Matrix4& Matrix4::RotateX(float rot)
  {
    //1.0, 0.0, 0.0 .....
    //0.0, cos,-sin
    //0.0, sin, cos
    Matrix4 rotation;
    rotation.Identity();
    float cosine = cos(rot);
    float sine = sin(rot);
    rotation.v[1][1] = cosine;
    rotation.v[2][2] = cosine;

    rotation.v[1][2] = -sine;
    rotation.v[2][1] = sine;

    return *this * rotation;
  }

  Matrix4 Matrix4::GetRotatedX(float rot) const
  {
    Matrix4 toRet(*this);
    return toRet.RotateX(rot);
  }

  Matrix4& Matrix4::RotateY(float rot)
  {
    // cos, 0.0, sin .....
    // 0.0, 1.0, 0.0
    //-sin, 0.0, cos
    Matrix4 rotation;
    rotation.Identity();
    float cosine = cos(rot);
    float sine = sin(rot);
    rotation.v[0][0] = cosine;
    rotation.v[2][2] = cosine;

    rotation.v[0][2] = sine;
    rotation.v[2][0] = -sine;

    return *this * rotation;
  }

  Matrix4 Matrix4::GetRotatedY(float rot) const
  {
    Matrix4 toRet(*this);
    return toRet.RotateY(rot);
  }

  Matrix4& Matrix4::RotateZ(float rot)
  {
    //cos,-sin, 0.0
    //sin, cos, 0.0
    //0.0, 0.0, 1.0
    Matrix4 rotation;
    rotation.Identity();
    float cosine = cos(rot);
    float sine = sin(rot);
    rotation.v[0][0] = cosine;
    rotation.v[1][1] = cosine;

    rotation.v[0][1] = -sine;
    rotation.v[1][0] = sine;

    return *this * rotation;
  }

  Matrix4 Matrix4::GetRotatedZ(float rot) const
  {
    Matrix4 toRet(*this);
    return toRet.RotateZ(rot);
  }


  Matrix4& Matrix4::Rotate(const Vector3& rhs)
  {
    return Rotate(rhs[0], rhs[1], rhs[2]);
  }

  Matrix4 Matrix4::GetRotated(const Vector3& rhs) const
  {
    Matrix4 toReturn(*this);
    toReturn.Rotate(rhs);
    return toReturn;
  }

  Matrix4& Matrix4::Rotate(float x, float y, float z)
  {
    RotateX(x);
    RotateY(y);    
    RotateZ(z);
    return *this;
  }

  Matrix4 Matrix4::GetRotated(float x, float y, float z) const
  {
    Matrix4 toRet(*this);
    return toRet.Rotate(x, y, z);
  }

  Matrix4& Matrix4::Translate(const Vector3& rhs)
  {
    return Translate(rhs[0], rhs[1], rhs[2]);
  }

  Matrix4 Matrix4::GetTranslated(const Vector3& rhs)
  {
    Matrix4 toRet(*this);
    return toRet.Translate(rhs);
  }

  Matrix4& Matrix4::Translate(float x, float y, float z) const
  {
    // 1.0, 0.0, 0.0, x1    0.0
    // 0.0, 1.0, 0.0, y1    0.0
    // 0.0, 0.0, 1.0, z1    0.0
    // 0.0, 0.0, 0.0, 1.0   1.0

    Matrix4 translation;
    translation.Identity();

    translation.v[0][3] = x;
    translation.v[1][3] = y;
    translation.v[2][3] = z;

    return *this * translation;
  }

  Matrix4 Matrix4::GetTranslated(float x, float y, float z) const
  {
    Matrix4 toRet(*this);
    return toRet.Translate(x, y, z);
  }


  Vector4 Matrix4::Transform(const Vector4& vec)
  {
    return Vector4(
      v[0][0] * vec[0] + v[0][1] * vec[1] + v[0][2] * vec[2] + v[0][3] * vec[3],
      v[1][0] * vec[0] + v[1][1] * vec[1] + v[1][2] * vec[2] + v[1][3] * vec[3],
      v[2][0] * vec[0] + v[2][1] * vec[1] + v[2][2] * vec[2] + v[2][3] * vec[3],
      v[3][0] * vec[0] + v[3][1] * vec[1] + v[3][2] * vec[2] + v[3][3] * vec[3]
    );
  }
}

