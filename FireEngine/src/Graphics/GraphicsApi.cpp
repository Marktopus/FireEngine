#include "Precompiled.h"
#include "GraphicsApi.h"

namespace Fire
{
  GraphicsApi::GraphicsApi(ApiType::Enum type) : api_type_(type)
  {

  }

  GraphicsApi::~GraphicsApi()
  {

  }

  ApiType::Enum GraphicsApi::GetType()
  {
    return api_type_;
  }
}