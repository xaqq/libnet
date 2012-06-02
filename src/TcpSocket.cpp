#include "TcpSocket.hpp"
#include <unistd.h>
#include <errno.h>
#include <iostream>

using namespace Net;

TcpSocket::TcpSocket(int fd /* = -1 */) :
_fd(fd),
_rBuf(1024 * 1024, 0),
_wBuf(1024 * 1024, 0)
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
  char                  buffer[1024 * 1024];
  int			r;
  int			ret;

  r = _wBuf.rAvailable();
  r = r > sizeof (buffer) ?  sizeof (buffer) : r;
  if (r)
    {
      _wBuf.read(&buffer[0], r);
      if ((ret = ::write(_fd, (char *) buffer, r)) == -1)
        {
          if (errno != EWOULDBLOCK &&
              errno != EAGAIN)
            {
              std::cerr << "Cannot write on socket" << std::endl;
              return (-1);
            }
          _wBuf.readRollback();
        }
      if (ret != r) /* we didnt write everything */
        _wBuf.readRollback(r - ret);
    }
  return (0);
}

int            TcpSocket::read(char* target, int len)
{
  return _rBuf.read(target, len);
}

TcpSocket       &TcpSocket::operator>>(int &i)
{
  _rBuf.read(reinterpret_cast<char *> (&i), 4);
  return *this;
}
