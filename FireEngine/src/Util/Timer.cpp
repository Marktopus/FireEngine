#include "Precompiled.h"

#include "Timer.h"

namespace Fire
{
  Timer::Timer()
  {
  
  }

  Timer::~Timer()
  {

  }
  
  void Timer::Start()
  {
    start_time_ = clock_.now();
  }

  void Timer::Reset()
  {
    Start();
  }

  double Timer::GetDuration()
  {
    clock::time_point curTime = clock_.now();
    std::chrono::duration<double> time_span = 
      std::chrono::duration_cast<std::chrono::duration<double>>(curTime - start_time_);
    return time_span.count();
  }
}