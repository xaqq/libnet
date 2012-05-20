#include "ATcpClient.hpp"
#include "TcpSocket.hpp"

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
