/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.04.26
 */

#include "BaseCommand.hpp"

/**
 * Return if command has finished.
 *
 * @return if command has finished
 */
bool BaseCommand::isFinished() {
    return FINISHED == state;
}

/**
 * Instantiates the command with the reading state.
 */
BaseCommand::BaseCommand() {
    state = READING;
}
