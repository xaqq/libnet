#include "RingBuffer.hpp"
#include <iostream>
#include <cstring>
#include <new>
#include <stdlib.h>

using namespace Net;

RingBuffer::RingBuffer(int size, int maxSize /* = 0 */) :
_data(0),
_size(size + 1),
_s(0),
_e(0)
{
  if (maxSize == 0)
    _maxSize = size;
  else
    _maxSize = maxSize;
  _data = stringPtr(new std::string);
  _data.get()->resize(_size, '\0');
}

RingBuffer::~RingBuffer()
{
}

bool RingBuffer::resize(int add)
{
  stringPtr     newBuffer;
  int		r;

  if (_size + add > _maxSize)
    return (false);
  newBuffer = stringPtr(new (std::nothrow) std::string);
  if (!newBuffer.get())
    return false;
  try
    {
      newBuffer->resize(_data.get()->size() + add);
    }
  catch (std::bad_alloc &e)
    {
      readRollback();
      return false;
    }
  if ((r = rAvailable()))
    if (read(*newBuffer, r) == 0)
      return false;
  _data = stringPtr(newBuffer);
  _s = 0;
  _lastStart = 0;
  _e = r;
  _size += add;
  return true;
}

int RingBuffer::rAvailable() const
{
  if (_s == _e)
    return (0);
  if (_s < _e)
    return (_e - _s);
  if (_s > _e)
    return (_e + _size - _s);
  return (0);
}

int RingBuffer::wAvailable() const
{
  return _size - rAvailable() - 1;
}

bool RingBuffer::write(const char* source, int len)
{
  int		direct;

  while (wAvailable() < len)
    if (!resize(1024))
      return (false);
  if (wAvailable() >= len)
    {
      direct = _size - _e;
      direct = direct > len ? len : direct;
      /*      _data.get()->replace(_e, direct, source, direct);*/
      memcpy(&((*_data)[_e]), source, direct);
      len -= direct;
      _e += direct;
      _e %= _size;
      if (len)
        write(source + direct, len);
    }
  return (true);
}

int RingBuffer::read(std::string &target, int len)
{
  int           readBytes = 0;

  try
    {
      if (target.size() < static_cast<unsigned int> (len))
        target.resize(len);
    }
  catch (std::bad_alloc &e)
    {
      return (0);
    }
  read_(&target[0], len, readBytes);
  return readBytes;
}

int RingBuffer::read(char *target, int len)
{
  int           readBytes = 0;

  read_(&target[0], len, readBytes);
  return readBytes;
}

bool RingBuffer::readRollback()
{
  if (_s == _lastStart)
    return false;
  _s = _lastStart;
  return true;
}

void RingBuffer::readRollback(int diff)
{
  int           tmp;

  tmp = _s;
  tmp -= diff;
  tmp %= _size;
  if (tmp < 0)
    _s = _size - abs(tmp);
  else
    _s = tmp;
}

void RingBuffer::read_(char *target, int len, int &readBytes)
{
  int		direct;

  if (len > rAvailable())
    len = rAvailable();
  direct = _size - _s;
  direct = direct > len ? len : direct;
  /*  _data.get()->copy(target, direct, _s);*/
  memcpy(target, &((*_data)[_s]), direct);
  readBytes += direct;
  len -= direct;
  _s += direct;
  _s %= _size;
  if (len)
    read_(target + direct, len, readBytes);
}
