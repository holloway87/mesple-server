/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_CONNECTIONMANAGER_HPP
#define MESPLE_SERVER_CONNECTIONMANAGER_HPP


#include <vector>
#include <sys/socket.h>

#include "../entity/Client.hpp"

using namespace std;

class ConnectionManager {
private:
    vector<Client> clients;
    int serverSocket;

public:
    static bool running;

    ConnectionManager(int socket);
    void loop();
};


#endif //MESPLE_SERVER_CONNECTIONMANAGER_HPP
