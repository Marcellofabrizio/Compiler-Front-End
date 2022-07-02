#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "../token.hpp"

#define RED "\033[31m" /* Red */

using namespace std;

typedef enum
{
    Deffault = 0,
    Digit,
    KeywordState,
    FloatingPoint,
    Error,
} State;

class Parser
{

public:
    int column;
    int line;
    int state;
    char currentChar;
    string lineBuffer;
    string lexeme;
    ifstream infile;
    Token currentToken;
    Token result;

    std::vector<Token> results;

    Token keywords[100] = {
        {"NULL", Null},
        {"printf", Identifier},
        {"scanf", Identifier},
        {"ident", Identifier},
        {"if", If},
        {"else if", ElseIf},
        {"else", Else},
        {"while", While},
        {"for", For},
        {"break", Break},
        {"continue", Continue},
        {"return", Return},
        {"try", Try},
        {"except", Except},
        {"int", Int},
        {"float", Float},
        {"short", Short},
        {"long", Long},
        {"signed", Signed},
        {"unsigned", Unsigned},
        {"void", Void},
        {"char", Char},
        {"const", Const},
        {"Struct", Struct},
        {"Double", Double},
        {"switch", Switch},
        {"case", Case},
        {"default", Default}};

    Parser(string filename);

    void readLine();
    void readCharacter();
    void unreadCharacter();
    void addToLexeme();
    void clearLexeme();
    void eofReached();
    void analyze();
    void analyzeStartState();
    void analyzeStringState();
    void analyzeDigitState();
    void analyzeFloatingPointState();
    void setToken(Token token, string value);
    void handleError();
    Token getKeyword();
};

#endif