#include "TcpSocket.hpp"
#include <errno.h>
#include <iostream>

using namespace Net;

TcpSocket::TcpSocket(int fd /* = -1 */) :
_fd(fd),
_rBuf(1024, 12048),
_wBuf(1024, 12048)
{

}

TcpSocket::~TcpSocket()
{
  close (_fd);
}

int TcpSocket::fd() const
{
  return _fd;
}

bool TcpSocket::write(const char *source, int len)
{
  if (!_wBuf.write(source, len))
    return false;
  return true;
}

int TcpSocket::flush()
{
  char                  buffer[512];
  int			r;

  r = _wBuf.rAvailable();
  r = r > 512 ? 512 : r;
  if (r)
    {
      _wBuf.read(&buffer[0], r);
      if (::write(_fd, (char *) buffer, r) == -1)
        {
          if (errno != EWOULDBLOCK &&
              errno != EAGAIN)
            return (-1);
          _wBuf.readRollback();
        }
    }
  return (0);
}

int            TcpSocket::read(char* target, int len)
{
  return _rBuf.read(target, len);
}

TcpSocket       &TcpSocket::operator>>(int &i)
{
  _rBuf.read(reinterpret_cast<char *>(&i), 4);
  return *this;
}
