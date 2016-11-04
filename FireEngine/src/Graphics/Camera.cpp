#include "Precompiled.h"
#include "Camera.h"
namespace Fire
{
  Camera::Camera() 
  : forward_(0.0, 0.0, 1.0),
    up_(0.0, 1.0, 0.0),
    right_(1.0, 0.0, 0.0),
    far_plane_(10000.0f),
    near_plane_(0.001f),
    field_of_view_(Math::Pi/2.0f)
  {
    perspective_.Zero();
    position_.Zero();
    position_.z = 50;
    view_.Identity();
  }

  Camera::~Camera()
  {

  }

  void Camera::UpdatePerspective()
  {
    perspective_.PerspectiveTransform(field_of_view_, near_plane_, far_plane_);
  }

  void Camera::UpdateView()
  {
    view_.ViewTransform(right_, up_, forward_, position_);
  }

  void Camera::Roll(float amt) 
  {
    //TODO: this
  }

  void Camera::Pitch(float amt) 
  {
    //TODO: this
  }

  void Camera::Yaw(float amt) 
  {
    //TODO: this
  }

  void Camera::LookAt(const Vector3& target)
  {
    forward_ = target - position_;
    forward_.Normalize();
    Vector3 up(0.0, 1.0, 0.0);
    if(forward_ == up)
    { 
      up.x = 1.0;
    }
    right_ = Vector3::Cross(up, forward_);
    up_ = Vector3::Cross(forward_, right_);
  }

  Matrix4 Camera::GetView()
  {
    return view_;
  }

  Matrix4 Camera::GetPerspective()
  {
    return perspective_;
  }
}
