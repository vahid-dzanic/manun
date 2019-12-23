#pragma once

#include <manun/includes>

class SineProtocol
{
public:
  SineProtocol()
    : mDataFunc(stdex_create(&SineProtocol::data, this))
  {}
  virtual ~SineProtocol() = default;

  virtual void data(float value) = 0;

protected:
  stdex::function<void(float)> mDataFunc;
};
