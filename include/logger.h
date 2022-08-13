//
// Created by marcello on 8/12/22.
//

#ifndef SYNTACTICPARSER_LOGGER_H
#define SYNTACTICPARSER_LOGGER_H

#include <string>

class Logger
{
public:
    Logger();

    void log(std::string message);
    void error(std::string message);
};

#endif //SYNTACTICPARSER_LOGGER_H
