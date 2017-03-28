/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_CONNECTIONMANAGER_HPP
#define MESPLE_SERVER_CONNECTIONMANAGER_HPP


#include <mutex>
#include <vector>
#include <sys/socket.h>

#include "../entity/Client.hpp"

using namespace std;

class ConnectionManager {
private:
    vector<Client> clients;
    mutex clientsMutex;
    int serverSocket;

public:
    static bool running;

    ConnectionManager(int socket);
    vector<Client> getNewClients();
    void loop();
};


#endif //MESPLE_SERVER_CONNECTIONMANAGER_HPP
