#pragma once
#include <chrono>
#include <iostream>

namespace Fire
{
  class Timer;
  class FrameCounter
  {
    public:
      FrameCounter();
      ~FrameCounter();
      void Update();
      
    private:
      double accumulator_;
      double dt_;
      double last_time_;
      Timer* timer_;

      

  };
}