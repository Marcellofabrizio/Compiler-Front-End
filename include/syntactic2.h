//
// Created by marcello on 9/3/22.
//

#ifndef SYNTACTICPARSER_SYNTACTIC2_H
#define SYNTACTICPARSER_SYNTACTIC2_H

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
    int currentTokenIndex = 0;
    int tk;
    string lexeme;
    std::vector<Token> tokenList;
    std::stack<int> tokenStack;

    Syntactic(std::vector<Token> results);

    int savePosition();
    void restorePosition(int pos);
    void getToken();

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
    bool expression(string e_c);
    bool expressionR();
    bool expressionR(string er_h, string er_s);
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
    bool expressionStatement(string exp_c);
    bool selectionStatement();
    bool iterationStatement();
    bool jumpStatement();
    bool structDeclaratorList();
    bool structDeclaratorListR();

    bool postFixExpressionR(string p_c);

    bool assignmentExpression(string ass_c);
};


#endif //SYNTACTICPARSER_SYNTACTIC2_H
