#ifndef SYNTATIC_H
#define SYNTATIC_H

#include "../token.hpp"

class Syntatic
{

public:
    int currentTokenIndex = 0;
    std::vector<Token> tokenList;

    Syntatic(std::vector<Token> results);

    void getToken();

    int externalDeclaration();
    int functionDeclaration();
    int primaryExpression();
    int postFixExpression();
    int postFixExpressionR();
    int argumentExpressionList();
    int argumentExpressionListR();
    int unaryExpression();
    int unaryOperator();
    int castExpression();
    int multiplicativeExpression();
    int multiplicativeExpressionR();
    int additiveExpression();
    int additiveExpressionR();
    int shiftExpression();
    int shiftExpressionR();
    int relationalExpression();
    int relationalExpressionR();
    int equalityExpression();
    int equalityExpressionR();
    int andExpression();
    int andExpressionR();
    int exclusiveOrExpression();
    int exclusiveOrExpressionR();
    int inclusiveOrExpression();
    int inclusiveOrExpressionR();
    int logicalAndExpression();
    int inclusiveAndExpressionR();
    int logicalOrExpression();
    int logicalOrExpressionR();
    int logicalAndExpressionR();
    int conditionExpression();
    int assignmentExpression();
    int assignmentOperator();
    int expression();
    int expressionR();
    int constantExrpression();
    int declaration();
    int declarationSpecifiers();
    int initDeclaratorList();
    int initDeclaratorListR();
    int initDeclarator();
    int typeSpecifier();
    int specifierList();
    int structSprecifier();
    int structGrammar();
    int structDeclarationList();
    int structDeclarationListR();
    int structDeclarator();
    int declarator();
    int directDeclarator();
    int directDeclaratorR();
    int pointer();
    int parameterTypeList();
    int parameterList();
    int parameterListR();
    int paramaeterDeclaration();
    int identifierList();
    int identifierListR();
    int typeName(); 
    int abstractDeclarator();
    int directAbstractDeclarator();
    int directAbstractDeclaratorR();
    int initializer();
    int initializerList();
    int initializerListR();
    int statement();
    int labeledStatement();
    int compoundStatement();
    int declarationList();
    int declarationListR();
    int statementList();
    int statementListR();
    int expressionStatement();
    int selectionsStatement();
    int iterationStatement();
    int jumpStatement();
};

#endif