/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <iostream>

#include "network/Server.hpp"
#include "network/ServerException.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (2 > argc) {
        cerr << "error: no port provided via parameters" << endl;

        return 1;
    }

    Server server {argv[1]};

    try {
        server.init();
    } catch (ServerException e) {
        cerr << "error: " << e.message << endl;

        return e.code;
    }

    server.loop();
    server.shutdownServer();

    return 0;
}
