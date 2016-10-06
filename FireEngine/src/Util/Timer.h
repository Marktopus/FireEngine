#pragma once
#include <chrono>

namespace Fire
{
  class Timer
  {
    public:
      typedef std::chrono::high_resolution_clock clock;
      Timer();
      ~Timer();
      void Reset();
      void Start();
      double GetDuration();

    private:
      clock clock_;
      clock::time_point start_time_;
  };
}