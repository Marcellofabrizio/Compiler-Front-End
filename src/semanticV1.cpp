//
// Created by marcello on 8/12/22.
//

#include <string>
#include "../include/semanticV1.h"

Semantic::Semantic(Logger &logger) {
    this->logger = logger;
}

void Semantic::clearTable()
{
    this->symbolsTable.clear();
}

void Semantic::insertToken(TableEntry tableEntry)
{
    if(!identifierInTable(tableEntry)) {
        this->symbolsTable.push_back(tableEntry);
    }
}

bool Semantic::identifierInTable(TableEntry tableEntry)
{
    for(TableEntry existingEntry : this->symbolsTable)
    {
        if(tableEntry.tokenOccurence.token.value.compare(existingEntry.tokenOccurence.token.value) == 0)
        {
            if(tableEntry.type.compare(existingEntry.type) == 0) {
                string var = existingEntry.tokenOccurence.token.value;
                int line = existingEntry.tokenOccurence.declarationLine;
                this->logger.error("Variável " + var + " já declarada na linha " + to_string(line));
                return true;
            }
        }
    }

    return false;
}