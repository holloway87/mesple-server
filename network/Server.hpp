/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_SERVER_HPP
#define MESPLE_SERVER_SERVER_HPP


#include <netdb.h>
#include <string>

using namespace std;

class Server {
private:
    struct addrinfo *serverInfo;
    string serverPort;

    void setServerInfo();

public:
    Server(const string port);
    void init();
};


#endif //MESPLE_SERVER_SERVER_HPP
