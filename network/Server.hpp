/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_SERVER_HPP
#define MESPLE_SERVER_SERVER_HPP


#include <netdb.h>
#include <string>

#include "ConnectionManager.hpp"

using namespace std;

class Server {
private:
    ConnectionManager *connectionManager;
    struct addrinfo *serverInfo;
    string serverPort;
    int serverSocket;
    static bool running;

    void bindSocket();
    void setServerInfo();
    void startListen();

public:
    Server(const string port);
    void init();
    void loop();
    void static signalHandler(int signal);
    void shutdownServer();
};


#endif //MESPLE_SERVER_SERVER_HPP
