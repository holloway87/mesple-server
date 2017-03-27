/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_SERVER_SERVEREXCEPTION_HPP
#define MESPLE_SERVER_SERVEREXCEPTION_HPP


#include <string>

using namespace std;

class ServerException {
public:
    const static short CODE_NO_ADDRESS_INFO = 10;

    short code;
    string message;

    ServerException(const string message, const short code);
};


#endif //MESPLE_SERVER_SERVEREXCEPTION_HPP
