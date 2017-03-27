/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include "ServerException.hpp"

/**
 * New instance with the given message and code.
 *
 * @param message
 * @param code
 */
ServerException::ServerException(const string message, const short code) {
    this->message = message;
    this->code = code;
}
