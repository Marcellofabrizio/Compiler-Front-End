//
// Created by marcello on 9/3/22.
//

#include "../include/syntactic2.h"
using namespace std;

Syntactic::Syntactic(vector<Token> results)
{
    this->tokenList = results;
    this->currentTokenIndex = -1;
}

int Syntactic::savePosition()
{
    return this->currentTokenIndex;
}

void Syntactic::restorePosition(int pos)
{
    this->currentTokenIndex = pos - 1;
    getToken();
}

void Syntactic::getToken()
{
    // funcao para pegar o token
    int size = this->tokenList.size();
    if (this->currentTokenIndex < size)
    {
        this->tk = this->tokenList[++this->currentTokenIndex].types;
        this->lexeme = this->tokenList[++this->currentTokenIndex].value;
    }

    else
    {
        this->tk = EndOfFile;
    }
}

bool Syntactic::assignmentExpression(string asgmtExp_c) {

    if(this->tk == Identifier)
    {
        string id = this->lexeme;
        if()
    }

}