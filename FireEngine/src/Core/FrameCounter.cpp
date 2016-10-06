#include "Precompiled.h"
#include "Util/Timer.h"
#include "FrameCounter.h"
namespace Fire
{
  FrameCounter::FrameCounter() 
  : accumulator_(0.0),
    dt_(0.0),
    timer_(new Timer())
  {
    timer_->Start();
  }

  FrameCounter::~FrameCounter()
  {

  }

  void FrameCounter::Update()
  { 
    if(accumulator_ == 0.0)
    { 
      last_time_ = timer_->GetDuration();
    }
    double curTime = timer_->GetDuration();
    dt_ = curTime - last_time_;
    accumulator_ += dt_;
    last_time_ = curTime;
  }
}

