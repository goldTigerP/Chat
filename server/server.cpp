#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include <iostream>
#include <string>

using namespace Poco::Net;
using namespace std;

int main()
{
    try
    {
        ServerSocket serverSocket(12345); // 监听端口 12345
        cout << "Server is running on port 12345..." << endl;

        while (true)
        {
            StreamSocket clientSocket = serverSocket.acceptConnection();
            cout << "Client connected!" << endl;

            SocketStream socketStream(clientSocket);
            string message;
            getline(socketStream, message); // 接收客户端消息
            cout << "Received: " << message << endl;

            socketStream << "Echo: " << message << endl; // 回显消息
        }
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}