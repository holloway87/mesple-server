/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_CLIENT_HPP
#define MESPLE_SERVER_CLIENT_HPP


#include <sys/socket.h>

class Client {
private:
    struct sockaddr_storage address;
    int clientSocket;

public:
    Client(struct sockaddr_storage address, int clientSocket);
};


#endif //MESPLE_SERVER_CLIENT_HPP
