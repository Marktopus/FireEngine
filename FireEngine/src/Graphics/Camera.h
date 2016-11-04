#pragma once

#include "Math/Matrix4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"

namespace Fire
{
  class Camera
  {
    public:
      Camera();
      ~Camera();
      void UpdatePerspective();
      void UpdateView();

      //todo: camera controller with this shit in it
      void Roll(float amt);
      void Pitch(float amt);
      void Yaw(float amt);


      void LookAt(const Vector3& target);
      
      Matrix4 GetView();
      Matrix4 GetPerspective();

      Vector3 position_;      
      Vector3 forward_;      
      Vector3 up_;      
      Vector3 right_;      


      float near_plane_;
      float far_plane_;
      float field_of_view_;
      Matrix4 perspective_;
      Matrix4 view_;
  };
}