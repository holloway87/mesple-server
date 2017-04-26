/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.04.26
 */

#ifndef MESPLE_SERVER_BASECOMMAND_HPP
#define MESPLE_SERVER_BASECOMMAND_HPP


class BaseCommand {
protected:
    enum states {READING, SENDING, FINISHED};
    int state;
public:
    BaseCommand();
    bool isFinished();
    void execute() {}
};


#endif //MESPLE_SERVER_BASECOMMAND_HPP
