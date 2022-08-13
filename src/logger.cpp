//
// Created by marcello on 8/13/22.
//

#include <iostream>
#import "../include/logger.h"

using namespace std;

Logger::Logger() {

}

void Logger::log(std::string message) {
    cout << "\033[1;32m" << message << "\033[0m"<< endl;
}

void Logger::error(std::string message) {
    cout << "\033[1;31m" << message << "\033[0m"<< endl;
}