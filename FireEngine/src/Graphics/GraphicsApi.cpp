#include "Precompiled.h"
#include "GraphicsApi.h"

namespace Fire
{
  GraphicsApi::GraphicsApi(GraphicsApi::Type type) : api_type_(type)
  {

  }

  GraphicsApi::~GraphicsApi()
  {

  }

  GraphicsApi::Type GraphicsApi::GetType()
  {
    return api_type_;
  }
}