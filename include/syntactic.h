#ifndef SYNTACTIC_H
#define SYNTACTIC_H

#include <stack>
#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include "./token.hpp"
using namespace std;

class SwitchProd
{
public:
    string label;
    string code;
    string testCode;

    SwitchProd();
    SwitchProd(string label, string code, string testCode);
};

class Syntactic
{

public:
    int tk;
    int currentTokenIndex = 0;
    int globalLabelIndex = 1;
    int globalTempsIndex = 1;
    string lexeme;
    vector<Token> tokenList;
    vector<string> caseLabels;
    vector<SwitchProd> switchProds;
    stack<int> tokenStack;
    stack<string> tempStack;
    stack<string> switchLabelStack;
    string currCaseLabel;
    map<string, SwitchProd> switchMap;

    Syntactic(vector<Token> results);

    int savePosition();
    void restorePosition(int pos);
    void getToken();
    string printSwitchMap();
    string getTemp();
    string newLabel(string label = NULL);

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
//    bool selectionStatement();
    bool iterationStatement();
    bool jumpStatement();
    bool structDeclaratorList();
    bool structDeclaratorListR();

    bool expressionStatement(string &expCode);

    bool statement(string &code);

    bool statement(string &code, string &place);

    bool expression(string &expCode);

    bool primaryExpression(string &primeExpCode,  bool isAssignment);

    bool postFixExpressionR(string &postFixRCode);

    bool postFixExpression(string &postFixExpCode, bool isAssignment);

    bool assignmentOperator(string &asgmtCode);

    bool assignmentExpression(string &asgmtExpCode);

    bool unaryExpression(string &unaryCode, bool isAssignment);

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

    bool labeledStatement(string &code, string &place);

    bool expression(string &code, string &place);

    bool compoundStatement(string &code, string &place);

    bool compoundStatementBody(string &code, string &place);

    bool compoundStatementList(string &code, string &place);

    bool statementList(string &code, string &place);

    bool selectionStatement(string &code);
};

#endif