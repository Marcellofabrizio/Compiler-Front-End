#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/syntatic.h"
using namespace std;

int tk;

Syntatic::Syntatic(vector<Token> results)
{
    this->tokenList = results;
    this->currentTokenIndex = 0;
    getToken();
}

void Syntatic::savePosition()
{
    this->tokenStack.push(this->currentTokenIndex);
}

void Syntatic::restorePosition()
{
    this->currentTokenIndex = this->tokenStack.top();
    this->tokenStack.pop();
}

void Syntatic::getToken()
{
    // funcao para pegar o token
    tk = this->tokenList[this->currentTokenIndex].types;
    this->currentTokenIndex++;
}

// externalDeclaration
int Syntatic::Syntatic::externalDeclaration()
{

    /*==================================== LEONARDO */
    // savePosition();
    if (functionDeclaration() == 1)
    {
        return 1;
    }
    // else
    // {

    //     getToken();
    //     if (declaration() == 1)
    //     {
    //         return 1;
    //     }
    // }

    return 0;
}

// functionDeclaration
int Syntatic::functionDeclaration()
{
    cout << "functionDeclaration: " << tk << endl;
    if (declarationSpecifiers() == 1)
    {
        if (declarator() == 1)
        {
            if (declarationList() == 1)
            {
                if (compoundStatement() == 1)
                {
                    return 1;
                }
            }
            if (compoundStatement() == 1)
            {
                return 1;
            }
        }
    }
    else if (declarator() == 1)
    {
        if (declarationList() == 1)
        {
            if (compoundStatement() == 1)
            {
                return 1;
            }
        }
        else if (compoundStatement() == 1)
        {
            return 1;
        }
    }

    return 0;
}

// primaryExpression
int Syntatic::primaryExpression()
{
    cout << "primaryExpression: " << tk << endl;
    if (tk == Identifier)
    { // id
        getToken();
        return 1;
    }
    if (tk == Constant)
    {
        getToken();
        return 1;
    }
    if (tk == ParenthesisOpen)
    {
        getToken();
        if (expression() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                return 1;
            }
        }
    }

    return 0;
}

// postFixExpression
int Syntatic::postFixExpression()
{
    cout << "postFixExpression: " << tk << endl;
    if (primaryExpression() == 1)
    {
        if (postFixExpressionR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::postFixExpressionR()
{
    cout << "postFixExpressionR: " << tk << endl;
    if (tk == ParenthesisOpen)
    {
        getToken();
        if (tk == ParenthesisClose)
        {
            getToken();
            if (postFixExpressionR() == 1)
            {
                return 1;
            }
        }
        if (argumentExpressionList() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (postFixExpressionR() == 1)
                {
                    return 1;
                }
            }
        }
    }
    if (tk == Dot)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (postFixExpressionR() == 1)
            {
                return 1;
            }
        }
    }
    if (tk == Accessor)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (postFixExpressionR() == 1)
            {
                return 1;
            }
        }
    }
    if (tk == IncOp)
    {
        getToken();
        if (postFixExpressionR() == 1)
        {
            return 1;
        }
    }
    if (tk == DecOp)
    {
        getToken();
        if (postFixExpressionR() == 1)
        {
            return 1;
        }
    }

    return 1;
}

// argumentExpressionList
int Syntatic::argumentExpressionList()
{
    cout << "argumentExpressionList: " << tk << endl;
    if (assignmentExpression() == 1)
    {
        if (argumentExpressionListR() == 1)
        {
            return 1;
        }
    }
    return 0;
}

int Syntatic::argumentExpressionListR()
{
    cout << "argumentExpressionListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (assignmentExpression() == 1)
        {
            if (argumentExpressionListR() == 1)
            {
                return 1;
            }
        }
    }

    return 1;
}

// unaryExpression
int Syntatic::unaryExpression()
{
    cout << "unaryExpression: " << tk << endl;
    if (postFixExpression() == 1)
    {
        return 1;
    }
    if (tk == IncOp)
    {
        getToken();
        if (unaryExpression() == 1)
        {
            return 1;
        }
    }
    if (tk == DecOp)
    {
        getToken();
        if (unaryExpression() == 1)
        {
            return 1;
        }
    }
    if (unaryOperator() == 1)
    {
        if (unaryOperator() == 1)
        {
            return 1;
        }
    }

    return 0;
}

// unaryOperator
int Syntatic::unaryOperator()
{
    cout << "unaryOperator: " << tk << endl;
    if (tk == AndOp)
    {
        getToken();
        return 1;
    }
    if (tk == Product)
    {
        getToken();
        return 1;
    }
    if (tk == Plus)
    {
        getToken();
        return 1;
    }
    if (tk == Minus)
    {
        getToken();
        return 1;
    }
    if (tk == Negate)
    {
        getToken();
        return 1;
    }
    if (tk == LogicalNot)
    {
        getToken();
        return 1;
    }

    return 0;
}

// castExpression
int Syntatic::castExpression()
{
    cout << "castExpression: " << tk << endl;
    if (unaryExpression() == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// multiplicativeExpression
int Syntatic::multiplicativeExpression()
{
    cout << "multiplicativeExpression: " << tk << endl;
    if (unaryExpression() == 1)
    {
        if (multiplicativeExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::multiplicativeExpressionR()
{
    cout << "multiplicativeExpressionR: " << tk << endl;
    if (tk == Product)
    {
        getToken();
        if (unaryExpression() == 1)
        {
            if (multiplicativeExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == Division)
    {
        getToken();
        if (unaryExpression() == 1)
        {
            if (multiplicativeExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == Module)
    {
        getToken();
        if (unaryExpression() == 1)
        {
            if (multiplicativeExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// additiveExpression
int Syntatic::additiveExpression()
{
    cout << "additiveExpression: " << tk << endl;
    if (multiplicativeExpression() == 1)
    {
        if (additiveExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::additiveExpressionR()
{
    cout << "additiveExpressionR: " << tk << endl;
    if (tk == Plus)
    {
        getToken();
        if (multiplicativeExpression() == 1)
        {
            if (additiveExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == Minus)
    {
        getToken();
        if (multiplicativeExpression() == 1)
        {
            if (additiveExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// shiftExpression
int Syntatic::shiftExpression()
{
    cout << "shiftExpression: " << tk << endl;
    if (additiveExpression() == 1)
    {
        if (shiftExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::shiftExpressionR()
{
    cout << "shiftExpressionR: " << tk << endl;
    if (tk == LeftOp)
    {
        getToken();
        if (additiveExpression() == 1)
        {
            if (shiftExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == RightOp)
    {
        getToken();
        if (additiveExpression() == 1)
        {
            if (shiftExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// relationalExpression
int Syntatic::relationalExpression()
{
    cout << "relationalExpression: " << tk << endl;
    if (shiftExpression() == 1)
    {
        if (relationalExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::relationalExpressionR()
{
    cout << "relationalExpressionR: " << tk << endl;
    if (tk == Less)
    {
        getToken();
        if (shiftExpression() == 1)
        {
            if (relationalExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == Greater)
    {
        getToken();
        if (shiftExpression() == 1)
        {
            if (relationalExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == LEOp)
    {
        getToken();
        if (shiftExpression() == 1)
        {
            if (relationalExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == GEOp)
    {
        getToken();
        if (shiftExpression() == 1)
        {
            if (relationalExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}
// equalityExpression
int Syntatic::equalityExpression()
{
    cout << "equalityExpression: " << tk << endl;
    if (relationalExpression() == 1)
    {
        if (equalityExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::equalityExpressionR()
{
    cout << "equalityExpressionR: " << tk << endl;
    if (tk == EQOp)
    {
        getToken();
        if (relationalExpression() == 1)
        {
            if (equalityExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (tk == NEOp)
    {
        getToken();
        if (relationalExpression() == 1)
        {
            if (equalityExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// andExpression
int Syntatic::andExpression()
{
    cout << "andExpression: " << tk << endl;
    if (equalityExpression() == 1)
    {
        if (andExpressionR() == 1)
        {
            return 1;
        }
    }
    return 0;
}

int Syntatic::andExpressionR()
{
    cout << "andExpressionR: " << tk << endl;
    if (tk == AndOp)
    {
        getToken();
        if (equalityExpression() == 1)
        {
            if (andExpressionR() == 1)
            {
                return 1;
            }
        }
    }
    return 1;
}

// exclusiveOrExpression
int Syntatic::exclusiveOrExpression()
{
    cout << "exclusiveOrExpression: " << tk << endl;
    if (andExpression() == 1)
    {
        if (exclusiveOrExpressionR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int Syntatic::exclusiveOrExpressionR()
{
    cout << "exclusiveOrExpressionR: " << tk << endl;
    if (tk == Power)
    {
        getToken();
        if (andExpression() == 1)
        {
            if (exclusiveOrExpressionR() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// inclusiveOrExpression
int Syntatic::inclusiveOrExpression()
{
    cout << "inclusiveOrExpression: " << tk << endl;
    if (exclusiveOrExpression() == 1)
    {
        if (inclusiveOrExpressionR() == 1)
        {
            return 1;
        }
    }
    return 0;
}

int Syntatic::inclusiveOrExpressionR()
{
    cout << "inclusiveOrExpressionR: " << tk << endl;
    if (tk == OrOp)
    {
        getToken();
        if (exclusiveOrExpression() == 1)
        {
            if (inclusiveOrExpressionR() == 1)
            {
                return 1;
            }
        }
    }

    return 1;
}

// logicalAndExpression
int Syntatic::logicalAndExpression()
{
    cout << "logicalAndExpression: " << tk << endl;
    if (inclusiveOrExpression() == 1)
    {
        if (inclusiveAndExpressionR() == 1)
        {
            return 1;
        }
    }
    return 0;
}

int Syntatic::inclusiveAndExpressionR()
{
    cout << "inclusiveAndExpressionR: " << tk << endl;
    if (tk == AndOp)
    {
        getToken();
        if (inclusiveOrExpression() == 1)
        {
            if (inclusiveAndExpressionR() == 1)
            {
                return 1;
            }
        }
    }
    return 1;
}
// logicalOrExpression
int Syntatic::logicalOrExpression()
{
    cout << "logicalOrExpression: " << tk << endl;
    if (logicalAndExpression() == 1)
    {
        if (logicalOrExpressionR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::logicalOrExpressionR()
{
    cout << "logicalOrExpressionR: " << tk << endl;
    if (tk == OrOp)
    {
        getToken();
        if (logicalAndExpression() == 1)
        {
            if (logicalOrExpressionR() == 1)
            {
                return 1;
            }
        }
    }
    return 1;
}

// conditionExpression
int Syntatic::conditionExpression()
{
    cout << "conditionExpression: " << tk << endl;
    if (logicalOrExpression() == 1)
    {
        if (tk == QuestionMark)
        {
            getToken();
            if (expression() == 1)
            {
                if (tk == Colon)
                {
                    getToken();
                    if (conditionExpression() == 1)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

// assignmentExpression
int Syntatic::assignmentExpression()
{
    cout << "assignmentExpression: " << tk << endl;
    // if (conditionExpression() == 1)
    // {
    //     return 1;
    // }
    /*==================================== LEONARDO */
    savePosition();
    if (unaryExpression() == 1)
    {
        if (assignmentOperator() == 1)
        {

            savePosition();
            if (assignmentExpression() == 1)
            {
                return 1;
            }
            else
            {
                /*==================================== LEONARDO */
                restorePosition();
                getToken();
                if (logicalOrExpression() == 1)
                {
                    return 1;
                }
            }
        }
    }

    /*==================================== LEONARDO */
    restorePosition();
    getToken();

    if (logicalOrExpression() == 1)
    {
        return 1;
    }

    return 0;
}

// assignmentOperator
int Syntatic::assignmentOperator()
{
    cout << "assignmentOperator: " << tk << endl;
    if (tk == Assign)
    {
        getToken();
        return 1;
    }
    if (tk == MulAssign)
    {
        getToken();
        return 1;
    }
    if (tk == DivAssign)
    {
        getToken();
        return 1;
    }
    if (tk == ModAssign)
    {
        getToken();
        return 1;
    }
    if (tk == AddAssign)
    {
        getToken();
        return 1;
    }
    if (tk == LessAssign)
    {
        getToken();
        return 1;
    }
    if (tk == LeftAssign)
    {
        getToken();
        return 1;
    }
    if (tk == RightAssign)
    {
        getToken();
        return 1;
    }
    else
    {
        return 0;
    }
}

// expression
int Syntatic::expression()
{
    cout << "expression: " << tk << endl;
    if (assignmentExpression() == 1)
    {
        if (expressionR() == 1)
        {
            return 1;
        }
    }
    
    return 0;
}

int Syntatic::expressionR()
{
    cout << "expressionR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (assignmentExpression() == 1)
        {
            if (expressionR() == 1)
            {
                return 1;
            }
        }
    }
    
    return 1;
}

// constantExrpression
int Syntatic::constantExrpression()
{
    cout << "constantExrpression: " << tk << endl;
    if (conditionExpression() == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// declaration
int Syntatic::declaration()
{
    cout << "declaration: " << tk << endl;
    if (declarationSpecifiers() == 1)
    {
        if (tk == SemiCollon)
        {
            getToken();
            return 1;
        }
        if (initDeclaratorList() == 1)
        {
            if (tk == SemiCollon)
            {
                getToken();
                return 1;
            }
        }
    }

    return 0;
}

// declarationSpecifiers
int Syntatic::declarationSpecifiers()
{
    cout << "declarationSpecifiers: " << tk << endl;
    if (typeSpecifier() == 1)
    {
        if (declarationSpecifiers() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

// initDeclaratorList
int Syntatic::initDeclaratorList()
{
    cout << "initDeclaratorList: " << tk << endl;
    if (initDeclarator() == 1)
    {
        if (initDeclaratorListR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::initDeclaratorListR()
{
    cout << "initDeclaratorListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (initDeclarator() == 1)
        {
            if (initDeclaratorListR() == 1)
            {
                return 1;
            }
        }
    }
    return 1;
}

// initDeclarator
int Syntatic::initDeclarator()
{
    cout << "initDeclarator: " << tk << endl;
    if (declarator() == 1)
    {
        if (tk == Assign)
        {
            getToken();
            if (initializer() == 1)
            {
                return 1;
            }
        }

        return 1;
    }

    return 0;
}

// typeSpecifier
int Syntatic::typeSpecifier()
{
    cout << "typeSpecifier: " << tk << endl;
    if (tk == Void)
    {
        getToken();
        return 1;
    }
    if (tk == Char)
    {
        getToken();
        return 1;
    }
    if (tk == Short)
    {
        getToken();
        return 1;
    }
    if (tk == Int)
    {
        getToken();
        return 1;
    }
    if (tk == Long)
    {
        getToken();
        return 1;
    }
    if (tk == Float)
    {
        getToken();
        return 1;
    }
    if (tk == Double)
    {
        getToken();
        return 1;
    }
    if (tk == Signed)
    {
        getToken();
        return 1;
    }
    if (tk == Unsigned)
    {
        getToken();
        return 1;
    }
    if (structSprecifier() == 1)
    {
        return 1;
    }

    return 0;
}

int Syntatic::specifierList()
{
    cout << "specifierList: " << tk << endl;
    if (typeSpecifier() == 1)
    {
        if (specifierList() == 1)
        {
            return 1;
        }

        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

// structSprecifier
int Syntatic::structSprecifier()
{
    cout << "structSprecifier: " << tk << endl;
    if (tk == Struct)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (tk == BraceOpen)
            {
                getToken();
                if (structDeclarationList() == 1)
                {
                    if (tk == BraceClose)
                    {
                        getToken();
                        return 1;
                    }
                }
            }
            else
            {
                return 1;
            }
        }
        if (tk == BraceOpen)
        {
            getToken();
            if (structDeclarationList() == 1)
            {
                if (tk == BraceClose)
                {
                    getToken();
                    return 1;
                }
            }
        }
    }

    return 0;
}

// struct -> tive que mudar o nome devido ao VScode ser mala e reclamar
int Syntatic::structGrammar()
{

    if (tk == Struct)
    {
        getToken();
        return 1;
    }

    return 0;
}

// structDeclarationList
int Syntatic::structDeclarationList()
{
    cout << "structDeclarationList: " << tk << endl;
    if (structDeclaration() == 1)
    {
        if (structDeclarationList() == 1)
        {
            return 1;
        }

        return 1;
    }
    return 0;
}

int Syntatic::structDeclaration()
{
    cout << "structDeclaration: " << tk << endl;
    if (specifierList() == 1)
    {
        if (structDeclarationList() == 1)
        {
            if (tk == SemiCollon)
            {
                getToken();
                return 1;
            }
        }
    }

    return 0;
}

int Syntatic::structDeclaratorList()
{
    cout << "structDeclaratorList: " << tk << endl;
    if (structDeclarator() == 1)
    {
        if (structDeclaratorListR() == 1)
        {
            return 1;
        }
    }

    return 1;
}

int Syntatic::structDeclaratorListR()
{
    cout << "structDeclaratorListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (structDeclarator() == 1)
        {
            if (structDeclaratorListR() == 1)
            {
                return 1;
            }
        }
    }

    return 1;
}

// structDeclarator
int Syntatic::structDeclarator()
{
    if (declarator() == 1)
    {
        if (tk == Collon)
        {
            getToken();
            if (constantExrpression() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        return 1;
    }
    if (tk == Collon)
    {
        getToken();
        if (constantExrpression() == 1)
        {
            return 1;
        }
    }

    return 0;
}

// declarator
int Syntatic::declarator()
{
    cout << "declarator: " << tk << endl;
    if (pointer() == 1)
    {
        if (directDeclarator() == 1)
        {
            return 1;
        }
    }
    if (directDeclarator() == 1)
    {
        return 1;
    }

    return 0;
}

// directDeclarator
int Syntatic::directDeclarator()
{
    cout << "directDeclarator: " << tk << endl;
    if (tk == Identifier)
    {
        getToken();
        if (directDeclaratorR() == 1)
        {
            return 1;
        }
    }

    if (tk == ParenthesisOpen)
    {
        getToken();
        if (declarator() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int Syntatic::directDeclaratorR()
{
    cout << "directDeclaratorR: " << tk << endl;
    if (tk == ParenthesisOpen)
    {
        getToken();
        if (tk == ParenthesisClose)
        {
            getToken();
            if (directDeclaratorR() == 1)
            {
                return 1;
            }
        }
        if (parameterTypeList() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
        if (identifierList() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }

    if (tk == BracketOpen)
    {
        getToken();
        if (tk == BracketClose)
        {
            getToken();
            if (directDeclaratorR() == 1)
            {
                return 1;
            }
        }

        if (logicalOrExpression() == 1)
        {
            if (tk == BracketClose)
            {
                getToken();
                if (directDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 1;
}

// pointer
int Syntatic::pointer()
{
    cout << "pointer: " << tk << endl;
    if (tk == Product)
    {
        getToken();
        if (pointer() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

// parameterTypeList
int Syntatic::parameterTypeList()
{
    cout << "parameterTypeList: " << tk << endl;
    if (parameterList() == 1)
    {
        if (tk == Comma)
        {
            getToken();
            if (tk == Ellipsis)
            {
                getToken();
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

// parameterList
int Syntatic::parameterList()
{
    cout << "parameterList: " << tk << endl;
    if (parameterDeclaration() == 1)
    {
        if (parameterListR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::parameterListR()
{
    cout << "parameterListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (parameterDeclaration() == 1)
        {
            if (parameterListR() == 1)
            {
                return 1;
            }
        }
    }

    return 1;
}

// parameterDeclaration
int Syntatic::parameterDeclaration()
{
    cout << "parameterDeclaration: " << tk << endl;
    if (declarationSpecifiers() == 1)
    {
        if (declarator() == 1)
        {
            return 1;
        }
        if (abstractDeclarator() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

// identifierList
int Syntatic::identifierList()
{
    cout << "identifierList: " << tk << endl;
    if (tk == Identifier)
    {
        getToken();
        if (identifierListR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::identifierListR()
{
    cout << "identifierListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (identifierListR() == 1)
            {
                return 1;
            }
        }
    }
    return 1;
}

// abstractDeclarator
int Syntatic::abstractDeclarator()
{
    cout << "abstractDeclarator: " << tk << endl;
    if (pointer() == 1)
    {
        if (directAbstractDeclarator() == 1)
        {
            return 1;
        }
        else
        {
            return 1;
        }
    }
    if (directAbstractDeclarator() == 1)
    {
        return 1;
    }

    return 0;
}

// directAbstractDeclarator
int Syntatic::directAbstractDeclarator()
{
    cout << "directAbstractDeclarator: " << tk << endl;
    if (tk == ParenthesisOpen)
    {
        getToken();
        if (tk == ParenthesisClose)
        {
            getToken();
            if (directAbstractDeclaratorR() == 1)
            {
                return 1;
            }
        }
        if (parameterTypeList() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
        if (abstractDeclarator() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }
    if (tk == BracketClose)
    {
        getToken();
        if (tk == BracketClose)
        {
            getToken();
            if (directAbstractDeclaratorR() == 1)
            {
                return 1;
            }
        }
    }
    if (tk == BracketOpen)
    {
        getToken();
        if (constantExrpression() == 1)
        {
            if (tk == BracketOpen)
            {
                getToken();
                if (directAbstractDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int Syntatic::directAbstractDeclaratorR()
{
    cout << "directAbstractDeclaratorR: " << tk << endl;
    if (tk == BracketOpen)
    {
        getToken();
        if (tk == BracketClose)
        {
            getToken();
            if (directAbstractDeclaratorR() == 1)
            {
                return 1;
            }
        }
        if (logicalOrExpression() == 1)
        {
            if (tk == BracketClose)
            {
                getToken();
                if (directAbstractDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }
    if (tk == ParenthesisOpen)
    {
        getToken();
        if (tk == ParenthesisClose)
        {
            getToken();
            if (directAbstractDeclaratorR() == 1)
            {
                return 1;
            }
        }
        if (parameterTypeList() == 1)
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclaratorR() == 1)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

// initializer
int Syntatic::initializer()
{
    cout << "initializer: " << tk << endl;
    if(assignmentExpression() == 1)
    {
        return 1;
    }
    if (tk == BraceOpen)
    {
        getToken();
        if (initializerList() == 1)
        {
            if (tk == BraceClose)
            {
                getToken();
                return 1;
            }
            else if (tk == Comma)
            {
                getToken();
                if (tk == BraceClose)
                {
                    getToken();
                    return 1;
                }
            }
        }
    }

    return 0;
}

// initializerList
int Syntatic::initializerList()
{
    cout << "initializerList: " << tk << endl;
    if (initializer() == 1)
    {
        if (initializerListR() == 1)
        {
            return 1;
        }
    }

    return 0;
}

int Syntatic::initializerListR()
{
    cout << "initializerListR: " << tk << endl;
    if (tk == Comma)
    {
        getToken();
        if (initializer() == 1)
        {
            if (initializerListR() == 1)
            {
                return 1;
            }
        }
    }

    return 1;
}

// statement
int Syntatic::statement()
{
    cout << "statement: " << tk << endl;
    if (labeledStatement() == 1)
    {
        return 1;
    }
    if (compoundStatement() == 1)
    {
        return 1;
    }
    if (expressionStatement() == 1)
    {
        return 1;
    }
    if (selectionsStatement() == 1)
    {
        return 1;
    }
    if (iterationStatement() == 1)
    {
        return 1;
    }
    if (jumpStatement() == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// labeledStatement
int Syntatic::labeledStatement()
{
    cout << "labeledStatement: " << tk << endl;
    if (tk == Identifier)
    {
        getToken();
        if (tk == Collon)
        {
            getToken();
            if (statement() == 1)
            {
                return 1;
            }
        }
    }
    else if (tk == Case)
    {
        getToken();
        if (logicalOrExpression() == 1)
        {
            if (tk == Collon)
            {
                getToken();
                if (statement() == 1)
                {
                    return 1;
                }
            }
        }
    }
    else if (tk == Default)
    {
        getToken();
        if (tk == Collon)
        {
            getToken();
            if (statement() == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// compoundStatement          //REVISAR GRAMATICA LINHA 288
int Syntatic::compoundStatement()
{
    cout << "compoundStatement: " << tk << endl;
    if (tk == BraceOpen)
    {
        getToken();
        if (compoundStatementBody() == 1)
        {
            if (tk == BraceClose)
            {
                return 1;
            }
        }
    }

    return 0;
}

/*==================================== LEONARDO */
int Syntatic::compoundStatementBody()
{
    cout << "compoundStatementBody: " << tk << endl;
    if (compoundStatementBodyR() == 1)
    {
        if (compoundStatementBody() == 1)
        {
            return 1;
        }

        return 0;
    }

    return 1;
}

/*==================================== LEONARDO */
int Syntatic::compoundStatementBodyR()
{
    cout << "compoundStatementBodyR: " << tk << endl;
    if (declarationList() == 1)
    {
        return 1;
    }

    if (statementList() == 1)
    {
        return 1;
    }

    return 0;
}

// declarationList
int Syntatic::declarationList()
{
    cout << "declarationList: " << tk << endl;
    if (declaration() == 1)
    {
        if (declarationList() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

int Syntatic::declarationListR()
{
    cout << "declarationListR: " << tk << endl;
    if (declaration() == 1)
    {
        if (declarationList() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

// statementList
int Syntatic::statementList()
{
    cout << "statementList: " << tk << endl;
    if (statement() == 1)
    {
        if (statementList() == 1)
        {
            return 1;
        }

        return 1;
    }

    return 0;
}

int Syntatic::statementListR()
{
    cout << "statementListR: " << tk << endl;
    if (statement() == 1)
    {
        if (statementListR() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

// expressionStatement
int Syntatic::expressionStatement()
{
    cout << "expressionStatement: " << tk << endl;
    if (tk == SemiCollon)
    {
        getToken();
        return 1;
    }
    if (expression() == 1)
    {
        if (tk == SemiCollon)
        {
            getToken();
            return 1;
        }
    }

    return 0;
}

// selectionsStatement
int Syntatic::selectionsStatement()
{
    cout << "selectionsStatement: " << tk << endl;
    if (tk == If)
    {
        getToken();
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (expression() == 1)
            {
                if (tk == ParenthesisClose)
                {
                    getToken();
                    if (statement() == 1)
                    {
                        if (tk == Else)
                        {
                            getToken();
                            if (statement() == 1)
                            {
                                return 1;
                            }
                        }

                        return 1;
                    }
                }
            }
        }
    }
    if (tk == Switch)
    {
        getToken();
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (expression() == 1)
            {
                if (tk == ParenthesisClose)
                {
                    getToken();
                    if (statement() == 1)
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

// iterationStatement
int Syntatic::iterationStatement()
{
    cout << "iterationStatement: " << tk << endl;
    if (tk == While)
    {
        getToken();
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (expression() == 1)
            {
                if (tk == ParenthesisClose)
                {
                    getToken();
                    if (statement() == 1)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    else if (tk == Do)
    {
        getToken();
        if (statement() == 1)
        {
            if (tk == While)
            {
                getToken();
                if (tk == ParenthesisOpen)
                {
                    getToken();
                    if (expression() == 1)
                    {
                        if (tk == ParenthesisClose)
                        {
                            getToken();
                            if (tk == SemiCollon)
                            {
                                getToken();
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (tk == For)
    {
        getToken();
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (expressionStatement() == 1)
            {
                if (expressionStatement() == 1)
                {
                    if (tk == ParenthesisClose)
                    {
                        getToken();
                        if (statement() == 1)
                        {
                            return 1;
                        }
                    }
                    if (expression() == 1)
                    {
                        if (tk == ParenthesisClose)
                        {
                            getToken();
                            if (statement() == 1)
                            {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

// jumpStatement
int Syntatic::jumpStatement()
{
    cout << "jumpStatement: " << tk << endl;
    if (tk == Continue)
    {
        getToken();
        if (tk == SemiCollon)
        {
            getToken();
            return 1;
        }
    }
    if (tk == Break)
    {
        getToken();
        if (tk == SemiCollon)
        {
            getToken();
            return 1;
        }
    }
    if (tk == Return)
    {
        getToken();
        if (tk == SemiCollon)
        {
            getToken();
            return 1;
        }
        if (expression() == 1)
        {
            if (tk == SemiCollon)
            {
                getToken();
                return 1;
            }
        }
    }

    return 0;
}

// parabÃ©ns por chegar ao final do cÃ³digo
