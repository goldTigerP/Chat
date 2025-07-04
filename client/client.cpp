#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"
#include <iostream>
#include <string>
#include "common_define.h"

using namespace Poco::Net;
using namespace std;
using namespace Chat::Base;

int main()
{
    try
    {
        SocketAddress serverAddress(SERVER_IP, SERVER_PORT); // 连接到本地服务器
        StreamSocket socket(serverAddress);
        SocketStream socketStream(socket);

        string message;
        cout << "Enter a message: ";
        getline(cin, message);

        socketStream << message << endl; // 发送消息
        socketStream.flush();

        string response;
        getline(socketStream, response); // 接收回显
        cout << "Server response: " << response << endl;
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}