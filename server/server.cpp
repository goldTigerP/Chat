#include "Poco/NObserver.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/StreamSocket.h"
#include "common_define.h"
#include <iostream>
#include <string>

using namespace Poco::Net;
using namespace Poco;
using namespace std;
using namespace Chat::Base;

class ClientConnection {
public:
  explicit ClientConnection(StreamSocket &socket, SocketReactor &reactor)
      : _socket(socket), _reactor(reactor) {
    // 注册事件处理器
    _reactor.addEventHandler(_socket,
                             NObserver<ClientConnection, ReadableNotification>(
                                 *this, &ClientConnection::onReadable));
    _reactor.addEventHandler(_socket,
                             NObserver<ClientConnection, ShutdownNotification>(
                                 *this, &ClientConnection::onShutdown));
    cout << "Client connected: " << _socket.peerAddress().toString() << endl;
  }

  ~ClientConnection() {
    // 移除事件处理器
    _reactor.removeEventHandler(
        _socket, NObserver<ClientConnection, ReadableNotification>(
                     *this, &ClientConnection::onReadable));
    _reactor.removeEventHandler(
        _socket, NObserver<ClientConnection, ShutdownNotification>(
                     *this, &ClientConnection::onShutdown));
    cout << "Client disconnected: " << _socket.peerAddress().toString() << endl;
  }

  void onReadable(const AutoPtr<ReadableNotification> &notification) {
    try {
      char buffer[1024] = {0};
      int n = _socket.receiveBytes(buffer, sizeof(buffer));
      if (n > 0) {
        cout << "Received: " << string(buffer, n) << endl;
        _socket.sendBytes(buffer, n);
      } else {
        delete this;
      }
    } catch (const exception &ex) {
      cerr << "Error in onReadable: " << ex.what() << endl;
      delete this;
    }
  }

  void onShutdown(const AutoPtr<ShutdownNotification> &notification) {
    delete this;
  }

private:
  StreamSocket _socket;
  SocketReactor &_reactor;
};

int main() {
  try {
    // 创建服务器套接字
    ServerSocket serverSocket(SERVER_PORT);
    SocketReactor reactor;

    // 创建连接接受器
    SocketAcceptor<ClientConnection> acceptor(serverSocket, reactor);

    // 启动反应器线程
    Thread reactorThread;
    reactorThread.start(reactor);

    cout << "Server is running on port " << SERVER_PORT << "..." << endl;

    // 等待用户输入以停止服务器
    getchar();

    // 停止反应器
    reactor.stop();
    reactorThread.join();
  } catch (const exception &ex) {
    cerr << "Error: " << ex.what() << endl;
  }

  return 0;
}