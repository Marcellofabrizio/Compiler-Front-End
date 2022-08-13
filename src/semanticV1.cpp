//
// Created by marcello on 8/12/22.
//

#include <string>
#include "../include/semanticV1.h"

Semantic::Semantic() {}

void Semantic::clearTable()
{
    this->symbolsTable.clear();
}

void Semantic::insertToken(TableEntry tableEntry)
{
    this->symbolsTable.push_back(tableEntry);
}

bool Semantic::checkIdentifierDeclaration(string identifier)
{
    for(TableEntry tableEntry : this->symbolsTable)
    {
        if(tableEntry.tokenOccurence.token.value.compare(identifier) == 0)
        {
            return true;
        }
    }

    return false;
}