#ifndef SYNTACTIC_H
#define SYNTACTIC_H

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "./token.hpp"
using namespace std;

class Syntactic
{

public:
    int tk;
    int currentTokenIndex = 0;
    int globalLabelIndex = 1;
    int globalTempsIndex = 1;
    std::string lexeme;
    std::vector<Token> tokenList;
    std::stack<int> tokenStack;
    std::stack<std::string> tempStack;

    Syntactic(std::vector<Token> results);

    int savePosition();
    void restorePosition(int pos);
    void getToken();
    std::string getTemp();
    std::string newLabel(std::string label = NULL);

    bool translationUnit();
    bool externalDeclaration();
    bool functionDeclaration();
    bool primaryExpression();
    bool postFixExpression();
    bool postFixExpressionR();
    bool argumentExpressionList();
    bool argumentExpressionListR();
    bool argumentExpression();
    bool unaryExpression();
    bool unaryOperator();
    bool castExpression();
    bool typeName();
    bool multiplicativeExpression();
    bool multiplicativeExpressionR();
    bool additiveExpression();
    bool additiveExpressionR();
    bool shiftExpression();
    bool shiftExpressionR();
    bool relationalExpression();
    bool relationalExpressionR();
    bool equalityExpression();
    bool equalityExpressionR();
    bool andExpression();
    bool andExpressionR();
    bool exclusiveOrExpression();
    bool exclusiveOrExpressionR();
    bool inclusiveOrExpression();
    bool inclusiveOrExpressionR();
    bool logicalAndExpression();
    bool inclusiveAndExpressionR();
    bool logicalOrExpression();
    bool logicalOrExpressionR();
    bool logicalAndExpressionR();
    bool conditionExpression();
    bool assignmentExpression();
    bool assignmentOperator();
    bool expression();
    bool expressionR();
    bool constantExrpression();
    bool declaration();
    bool declarationSpecifiers();
    bool initDeclaratorList();
    bool initDeclaratorListR();
    bool initDeclarator();
    bool typeSpecifier();
    bool specifierList();
    bool structSprecifier();
    bool structGrammar();
    bool structDeclarationList();
    bool structDeclarationListR();
    bool structDeclaration();
    bool structDeclarator();
    bool declarator();
    bool directDeclarator();
    bool directDeclaratorR();
    bool pointer();
    bool parameterTypeList();
    bool parameterList();
    bool parameterListR();
    bool parameterDeclaration();
    bool identifierList();
    bool identifierListR();
    bool abstractDeclarator();
    bool directAbstractDeclarator();
    bool directAbstractDeclaratorR();
    bool initializer();
    bool initializerList();
    bool initializerListR();
    bool statement();
    bool labeledStatement();
    bool compoundStatement();
    bool compoundStatementList();
    bool compoundStatementBody();
    bool declarationList();
    bool declarationListR();
    bool statementList();
    bool statementListR();
    bool expressionStatement();
    bool selectionStatement();
    bool iterationStatement();
    bool jumpStatement();
    bool structDeclaratorList();
    bool structDeclaratorListR();

    bool expressionStatement(std::string &expCode);

    bool statement(std::string &stmtCode);

    bool expression(std::string &expCode);

    bool primaryExpression(std::string &primeExpCode,  bool isAssignment);

    bool postFixExpressionR(std::string &postFixRCode);

    bool postFixExpression(string &postFixExpCode, bool isAssignment);

    bool assignmentOperator(std::string &asgmtCode);

    bool assignmentExpression(std::string &asgmtExpCode);

    bool unaryExpression(std::string &unaryCode, bool isAssignment);

    bool expressionR(string &expRCode);

    bool logicalAndExpression(string &logicalCode);

    bool inclusiveOrExpression(string &incOrExpCode);

    bool inclusiveOrExpressionR(string incOrExpRCode);

    bool logicalOrExpression(string &logicalCode);

    bool logicalOrExpressionR(string &logicalCodeR);

    bool exclusiveOrExpression(string &excOrCode);

    bool exclusiveOrExpressionR(string &excOrCodeR);

    bool andExpression(string &andExpCode);

    bool equalityExpression(string &code);

    bool relationalExpression(string &code);

    bool shiftExpression(string &code);

    bool additiveExpression(string &code);

    bool multiplicativeExpression(string &code, bool isAssignment);

    bool multiplicativeExpressionR(string &code);

    bool relationalExpressionR(string &code);

    bool additiveExpressionR(string &code);

    bool compoundStatementBody(string &code);

    bool compoundStatementList(string &code);

    bool compoundStatement(string &code);

    bool statementList(string &code);

    bool switchStatement();

    bool caseStatementList(string &expressionCode, string &caseListCode, string &caseListTest);

    bool caseStatement(string &caseTest, string &caseCode);

};

#endif