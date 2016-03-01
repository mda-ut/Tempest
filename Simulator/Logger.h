#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>

class Logger
{
public:
    Logger();

    /*
     * Logs the message
     * TODO add priority, might copy jon's logger
     */
    static void Log(std::string);
};

#endif // LOGGER_H
