//
// Created by marcello on 8/12/22.
//

#ifndef SYNTACTICPARSER_SEMANTICV1_H
#define SYNTACTICPARSER_SEMANTICV1_H

#include <list>
#include <string>
#include "./token.hpp"
#include "./logger.h"

using namespace std;

class TableEntry
{
public:
    TokenOccurence tokenOccurence;
    string type;
};

class Semantic
{

public:
    list<TableEntry> symbolsTable;
    Logger logger;
    Semantic(Logger &logger);

    void clearTable();
    void insertToken(TableEntry tableEntry);
    bool identifierInTable(TableEntry tableEntry);

};

#endif //SYNTACTICPARSER_SEMANTICV1_H