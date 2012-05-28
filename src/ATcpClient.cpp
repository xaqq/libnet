#include "ATcpClient.hpp"
#include "TcpSocket.hpp"
#include <iostream>

using namespace Net;

ATcpClient::~ATcpClient()
{
}

void ATcpClient::setSocket(TcpSocket* s)
{
  _socket = sockPtr(s);
}

const TcpSocket &ATcpClient::socket() const
{
  return *_socket;
}

TcpSocket &ATcpClient::socket()
{
  return *_socket;
}

bool    ATcpClient::write(const char *data, int len)
{
  return (_socket.get()->write(data, len));
}

bool    ATcpClient::writeInt(int v)
{
  return write(reinterpret_cast<char *> (&v), sizeof(int));
}

int     ATcpClient::dataAvailable() const
{
  return _socket.get()->_rBuf.rAvailable();
}