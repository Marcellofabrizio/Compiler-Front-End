#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../include/syntatic.h"
using namespace std;

Syntatic::Syntatic(vector<Token> results)
{
    this->tokenList = results;
    this->currentTokenIndex = -1;
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
    this->tk = this->tokenList[++this->currentTokenIndex].types;
}

// externalDeclaration
bool Syntatic::Syntatic::externalDeclaration()
{
    if (functionDeclaration())
    {
        return true;
    }
    else if (declaration())
    {
        return true;
    }

    return false;
}

bool Syntatic::functionDeclaration()
{
    savePosition();
    if (declarationSpecifiers())
    {
        if (declarator())
        {
            savePosition();
            if (declarationList())
            {
                if (compoundStatement())
                {
                    return true;
                }
            }

            restorePosition();
            getToken();
            if (compoundStatement())
            {
                return true;
            }
        }
    }

    restorePosition();
    getToken();
    if (declarator())
    {
        savePosition();
        if (declarationList())
        {
            if (compoundStatement())
            {
                return true;
            }
        }

        restorePosition();
        getToken();
        if (compoundStatement())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::primaryExpression()
{
    if (this->tk == Identifier)
    {
        getToken();
        return true;
    }

    else if (this->tk == Constant)
    {
        getToken();
        return true;
    }

    else if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (expression())
        {
            if (this->tk == ParenthesisClose)
            {
                return true;
            }
        }
    }

    return false;
}

bool Syntatic::postFixExpression()
{
    if (primaryExpression())
    {
        if (postFixExpressionR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::postFixExpressionR()
{

    if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (this->tk == ParenthesisClose)
        {
            getToken();
            if (postFixExpressionR())
            {
                return true;
            }
        }

        else if (argumentExpressionList())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (postFixExpressionR())
                {
                    return true;
                }
            }
        }
    }

    if (this->tk == Dot)
    {
        getToken();
        if (this->tk == Identifier)
        {
            getToken();
            if (postFixExpressionR())
            {
                return true;
            }
        }
    }

    if (this->tk == Accessor)
    {
        getToken();
        if (this->tk == Identifier)
        {
            getToken();
            if (postFixExpressionR())
            {
                return true;
            }
        }
    }

    if (this->tk == IncOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }
    }

    if (this->tk == DecOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }
    }

    if (this->tk == BraceOpen)
    {
        getToken();
        if (expression())
        {
            if (this->tk == BracketClose)
            {
                getToken();
                if (postFixExpressionR())
                {
                    return true;
                }
            }
        }
    }

    return true;
}

bool Syntatic::argumentExpressionList()
{
    if (assignmentExpression())
    {
        if (argumentExpressionListR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::argumentExpressionListR()
{
    if (this->tk == Comma)
    {
        getToken();
        if (assignmentExpression())
        {
            if (argumentExpressionListR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::unaryExpression()
{
    if (postFixExpression())
    {
        return true;
    }

    if (this->tk == IncOp)
    {
        getToken();
        if (unaryExpression())
        {
            return true;
        }
    }

    if (this->tk == DecOp)
    {
        getToken();
        if (unaryExpression())
        {
            return true;
        }
    }

    if (unaryOperator())
    {
        if (castExpression())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::unaryOperator()
{
    if (this->tk == AndOp)
    {
        getToken();
        return true;
    }
    if (this->tk == Product)
    {
        getToken();
        return true;
    }
    if (this->tk == Plus)
    {
        getToken();
        return true;
    }
    if (this->tk == Minus)
    {
        getToken();
        return true;
    }
    if (this->tk == Negate)
    {
        getToken();
        return true;
    }
    if (this->tk == LogicalNot)
    {
        getToken();
        return true;
    }

    return false;
}

bool Syntatic::castExpression()
{
    if (unaryExpression())
    {
        return true;
    }

    else if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (typeName())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (castExpression())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Syntatic::multiplicativeExpression()
{
    if (castExpression())
    {
        if (multiplicativeExpressionR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::multiplicativeExpressionR()
{

    if (this->tk == Product)
    {
        getToken();
        if (unaryExpression())
        {
            if (multiplicativeExpressionR())
            {
                return true;
            }
        }
    }

    else if (this->tk == Division)
    {
        getToken();
        if (unaryExpression())
        {
            if (multiplicativeExpressionR())
            {
                return true;
            }
        }
    }

    else if (this->tk == Module)
    {
        getToken();
        if (unaryExpression())
        {
            if (multiplicativeExpressionR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::additiveExpression()
{
    if (multiplicativeExpression())
    {
        if (additiveExpressionR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::additiveExpressionR()
{
    if (this->tk == Plus)
    {
        getToken();
        if (multiplicativeExpression())
        {
            if (additiveExpressionR())
            {
                return true;
            }
        }
    }

    else if (this->tk == Minus)
    {
        getToken();
        if (multiplicativeExpression())
        {
            if (additiveExpressionR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::shiftExpression()
{
    if (additiveExpression())
    {
        if (shiftExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::shiftExpressionR()
{
    if (this->tk == LeftOp)
    {
        getToken();
        if (additiveExpression())
        {
            if (shiftExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == RightOp)
    {
        getToken();
        if (additiveExpression())
        {
            if (shiftExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::relationalExpression()
{
    if (shiftExpression())
    {
        if (relationalExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::relationalExpressionR()
{
    if (this->tk == Less)
    {
        getToken();
        if (shiftExpression())
        {
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == Greater)
    {
        getToken();
        if (shiftExpression())
        {
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == LEOp)
    {
        getToken();
        if (shiftExpression())
        {
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == GEOp)
    {
        getToken();
        if (shiftExpression())
        {
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::equalityExpression()
{
    if (relationalExpression())
    {
        if (equalityExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::equalityExpressionR()
{
    if (this->tk == EQOp)
    {
        getToken();
        if (relationalExpression())
        {
            if (equalityExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == NEOp)
    {
        getToken();
        if (relationalExpression())
        {
            if (equalityExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::andExpression()
{
    if (equalityExpression())
    {
        if (andExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::andExpressionR()
{
    if (this->tk == AndOp)
    {
        getToken();
        if (equalityExpression())
        {
            if (andExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::exclusiveOrExpression()
{
    if (andExpression())
    {
        if (exclusiveOrExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::exclusiveOrExpressionR()
{
    if (this->tk == Power)
    {
        getToken();
        if (andExpression())
        {
            if (exclusiveOrExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::inclusiveOrExpression()
{
    if (exclusiveOrExpression())
    {
        if (inclusiveOrExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::inclusiveOrExpressionR()
{
    if (this->tk == OrOp)
    {
        getToken();
        if (exclusiveOrExpression())
        {
            if (inclusiveOrExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::logicalAndExpression()
{
    if (inclusiveOrExpression())
    {
        if (logicalAndExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::logicalAndExpressionR()
{
    if (this->tk == AndOp)
    {
        getToken();
        if (inclusiveOrExpression())
        {
            if (logicalAndExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::logicalOrExpression()
{
    if (logicalAndExpression())
    {
        if (logicalOrExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::logicalOrExpressionR()
{
    if (this->tk == OrOp)
    {
        getToken();
        if (logicalAndExpression())
        {
            if (logicalOrExpressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::conditionExpression()
{
    if (logicalOrExpression())
    {
        if (this->tk == QuestionMark)
        {
            getToken();
            if (expression())
            {
                if (this->tk == Colon)
                {
                    getToken();
                    if (conditionExpression())
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool Syntatic::assignmentExpression()
{
    if (conditionExpression())
    {
        return true;
    }
    if (unaryExpression())
    {
        if (assignmentOperator())
        {
            if (assignmentExpression())
            {
                return true;
            }
        }
    }
    return false;
}

bool Syntatic::assignmentOperator()
{
    if (this->tk == Assign)
    {
        return true;
    }
    if (this->tk == MulAssign)
    {
        return true;
    }
    if (this->tk == DivAssign)
    {
        return true;
    }
    if (this->tk == ModAssign)
    {
        return true;
    }
    if (this->tk == AddAssign)
    {
        return true;
    }
    if (this->tk == LessAssign)
    {
        return true;
    }
    if (this->tk == LeftAssign)
    {
        return true;
    }
    if (this->tk == RightAssign)
    {
        return true;
    }
    return false;
}

bool Syntatic::expression()
{
    if (assignmentExpression())
    {
        if (expressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::expressionR()
{
    if (this->tk == Comma)
    {
        getToken();
        if (assignmentExpression())
        {
            if (expressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::constantExrpression()
{
    if (logicalOrExpression())
    {
        return true;
    }

    return false;
}

bool Syntatic::declaration()
{

    if (declarationSpecifiers())
    {
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }

        else if (initDeclaratorList())
        {
            if (this->tk == SemiCollon)
            {
                getToken();
                return true;
            }
        }
    }

    return false;
}

bool Syntatic::declarationSpecifiers()
{
    if (typeSpecifier())
    {
        savePosition();
        if (declarationSpecifiers())
        {
            return true;
        }
        restorePosition();
        getToken();
        return true;
    }

    return false;
}

bool Syntatic::initDeclaratorList()
{
    if (initDeclarator())
    {
        if (initDeclaratorListR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::initDeclaratorListR()
{
    if (this->tk == Comma)
    {
        if (initDeclarator())
        {
            if (initDeclaratorListR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::initDeclarator()
{
    if (declarator())
    {
        if (this->tk == Assign)
        {
            if (initializer())
            {
                return true;
            }
        }

        return true;
    }

    return false;
}

bool Syntatic::typeSpecifier()
{
    if (this->tk == Void)
    {
        getToken();
        return true;
    }
    if (this->tk == Char)
    {
        getToken();
        return true;
    }
    if (this->tk == Short)
    {
        getToken();
        return true;
    }
    if (this->tk == Int)
    {
        getToken();
        return true;
    }
    if (this->tk == Long)
    {
        getToken();
        return true;
    }
    if (this->tk == Float)
    {
        getToken();
        return true;
    }
    if (this->tk == Double)
    {
        getToken();
        return true;
    }
    if (this->tk == structSprecifier())
    {
        return true;
    }

    return false;
}

bool Syntatic::specifierList()
{

    if (typeSpecifier())
    {
        if (specifierList())
        {
            return true;
        }

        return true;
    }

    return false;
}

bool Syntatic::structSprecifier()
{
    if (this->tk == Struct)
    {
        getToken();
        if (this->tk == Identifier)
        {
            getToken();
            if (this->tk == BraceOpen)
            {
                getToken();
                if (structDeclarationList())
                {
                    if (this->tk == BracketClose)
                    {
                        getToken();
                        return true;
                    }
                }
            }

            return true;
        }

        else if (this->tk == BraceOpen)
        {
            getToken();

            if (structDeclarationList())
            {
                if (this->tk == BraceClose)
                {
                    getToken();
                    return true;
                }
            }
        }
    }

    return false;
}

bool Syntatic::structDeclarationList()
{
    if (structDeclaration())
    {
        if (structDeclarationListR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::structDeclarationListR()
{
    if (structDeclaration())
    {
        if (structDeclarationListR())
        {
            return true;
        }
    }

    return true;
}

bool Syntatic::structDeclaration()
{
    if (specifierList())
    {
        if (structDeclarationList())
        {
            if (this->tk == SemiCollon)
            {
                getToken();
                return true;
            }
        }
    }

    return false;
}

bool Syntatic::structDeclaratorList()
{
    if (structDeclarator())
    {
        if (structDeclaratorListR())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::structDeclaratorListR()
{
    if (this->tk == Comma)
    {
        getToken();
        if (structDeclarator())
        {
            if (structDeclaratorListR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::structDeclarator()
{
    if (declarator())
    {
        if (this->tk == Collon)
        {
            getToken();
            if (logicalOrExpression())
            {
                return true;
            }
        }

        return true;
    }

    else if (this->tk == Collon)
    {
        getToken();
        if (logicalOrExpression())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::declarator()
{
    if (directDeclarator())
    {
        return true;
    }
    if (pointer())
    {
        if (directDeclarator())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::directDeclarator()
{
    if (this->tk == Identifier)
    {
        getToken();
        if (directDeclaratorR())
        {
            return true;
        }
    }
    if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (declarator())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (directDeclaratorR())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Syntatic::directDeclaratorR()
{
    if (this->tk == BracketOpen)
    {
        getToken();
        if (this->tk == BracketClose)
        {
            getToken();
            if (directDeclaratorR())
            {
                return true;
            }
        }
        if (logicalOrExpression())
        {
            if (this->tk == BracketClose)
            {
                getToken();
                if (directDeclaratorR())
                {
                    return true;
                }
            }
        }
    }
    if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (this->tk == ParenthesisClose)
        {
            getToken();
            if (directDeclaratorR())
            {
                return true;
            }
        }
        if (parameterTypeList())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (directDeclaratorR())
                {
                    return true;
                }
            }
        }
    }
    return true;
}

bool Syntatic::pointer()
{
    if (this->tk == Product)
    {
        getToken();
        if (pointer())
        {
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::parameterTypeList()
{
    if (parameterList())
    {
        if (this->tk == Comma)
        {
            getToken();
            if (this->tk == Ellipsis)
            {
                getToken();
                return true;
            }
        }
        return true;
    }
    return false;
}

bool Syntatic::parameterList()
{
    if (parameterDeclaration())
    {
        if (parameterListR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::parameterListR()
{
    if (this->tk == Comma)
    {
        getToken();
        if (parameterDeclaration())
        {
            if (parameterListR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::parameterDeclaration()
{
    if (declarationSpecifiers())
    {
        if (declarator())
        {
            return true;
        }
        if (abstractDeclarator())
        {
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::identifierList()
{
    if (this->tk == Identifier)
    {
        getToken();
        if (identifierListR())
        {
            return true;
        }
    }
    return false;
}

bool Syntatic::identifierListR()
{
    if (this->tk == Comma)
    {
        getToken();
        if (this->tk == Identifier)
        {
            getToken();
            if (identifierListR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::typeName()
{
    if (specifierList())
    {
        if (abstractDeclarator())
        {
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::abstractDeclarator()
{
    if (pointer())
    {
        if (directAbstractDeclarator())
        {
            return true;
        }

        return true;
    }

    if (directAbstractDeclarator())
    {
        return true;
    }

    return false;
}

bool Syntatic::directAbstractDeclarator()
{
    if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (parameterTypeList())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclarator())
                {
                    return true;
                }
            }
        }

        else if (abstractDeclarator())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclaratorR())
                {
                    return true;
                }
            }
        }

        else if (this->tk == ParenthesisClose)
        {
            getToken();
            if (directAbstractDeclaratorR())
            {
                return true;
            }
        }
    }

    else if (this->tk == BracketOpen)
    {
        getToken();
        if (logicalOrExpression())
        {
            if (this->tk == BracketClose)
            {
                getToken();
                if (directAbstractDeclaratorR())
                {
                    return true;
                }
            }
        }

        else if (this->tk == BracketClose)
        {
            getToken();
            if (directAbstractDeclaratorR())
            {
                return true;
            }
        }
    }

    return false;
}

bool Syntatic::directAbstractDeclaratorR()
{
    if (this->tk == BracketOpen)
    {
        getToken();

        if (logicalOrExpression())
        {
            if (this->tk == BracketClose)
            {
                getToken();
                if (directAbstractDeclaratorR())
                {
                    return true;
                }
            }
        }
    }

    else if (this->tk == ParenthesisOpen)
    {
        getToken();
        if (parameterTypeList())
        {
            if (this->tk == ParenthesisClose)
            {
                getToken();
                if (directAbstractDeclaratorR())
                {
                    return true;
                }
            }
        }

        else if (this->tk == ParenthesisClose)
        {
            getToken();
            if (directAbstractDeclaratorR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::initializer()
{
    if (assignmentExpression())
    {
        return true;
    }

    if (this->tk == BraceOpen)
    {
        getToken();
        if (initializerList())
        {
            if (this->tk == BraceClose)
            {
                getToken();
                return true;
            }

            else if (this->tk == Comma)
            {
                getToken();
                if (this->tk == BraceClose)
                {
                    getToken();
                    return true;
                }
            }
        }
    }

    return false;
}

bool Syntatic::initializerList()
{
    if (initializer())
    {
        if (initDeclaratorListR())
        {
            return true;
        }
    }

    return true;
}

bool Syntatic::initializerListR()
{
    if (this->tk == Comma)
    {
        if (initializer())
        {
            if (initializerListR())
            {
                return true;
            }
        }
    }

    return true;
}

bool Syntatic::statement()
{
    if (labeledStatement())
    {
        return true;
    }
    else if (compoundStatement())
    {
        return true;
    }
    else if (expressionStatement())
    {
        return true;
    }
    else if (selectionStatement())
    {
        return true;
    }
    else if (iterationStatement())
    {
        return true;
    }
    else if (jumpStatement())
    {
        return true;
    }

    return false;
}

bool Syntatic::labeledStatement()
{
    if (this->tk == Case)
    {
        getToken();
        if (logicalOrExpression())
        {
            if (this->tk == Collon)
            {
                getToken();
                if (statement())
                {
                    return true;
                }
            }
        }
    }

    else if (this->tk == Default)
    {
        getToken();

        if (this->tk == Collon)
        {
            getToken();
            if (statement())
            {
                return true;
            }
        }
    }

    return false;
}

bool Syntatic::compoundStatement()
{
    if (this->tk == BraceOpen)
    {
        getToken();
        if (compoundStatementList())
        {
            if (this->tk == BraceClose)
            {
                getToken();
                return true;
            }
        }
    }
    return false;
}

bool Syntatic::compoundStatementList()
{
    if (compoundStatementBody())
    {
        if (compoundStatementList())
        {
            return true;
        }

        return false;
    }

    return true;
}

bool Syntatic::compoundStatementBody()
{
    if (declarationList())
    {
        return true;
    }

    else if (statementList())
    {
        return true;
    }

    return false;
}

bool Syntatic::declarationList()
{
    if (declaration())
    {
        if (declarationList())
        {
            return true;
        }

        return true;
    }

    return false;
}

bool Syntatic::statementList()
{
    if (statement())
    {
        if (statementList())
        {
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::expressionStatement()
{
    if (this->tk == SemiCollon)
    {
        getToken();
        return true;
    }
    if (expression())
    {
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }
    }
    return false;
}

bool Syntatic::selectionStatement()
{
    if (this->tk == If)
    {
        getToken();
        if (this->tk == ParenthesisOpen)
        {
            getToken();
            if (expression())
            {
                if (this->tk == ParenthesisClose)
                {
                    getToken();
                    if (statement())
                    {
                        if (this->tk == Else)
                        {
                            getToken();
                            if (statement())
                            {
                                return true;
                            }
                        }
                        return true;
                    }
                }
            }
        }
    }
    if (this->tk == Switch)
    {
        getToken();
        if (this->tk == ParenthesisOpen)
        {
            getToken();
            if (expression())
            {
                if (this->tk == ParenthesisClose)
                {
                    getToken();
                    if (statement())
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Syntatic::iterationStatement()
{
    if (this->tk == While)
    {
        getToken();
        if (this->tk == ParenthesisOpen)
        {
            getToken();
            if (expression())
            {
                if (this->tk == ParenthesisClose)
                {
                    getToken();
                    if (statement())
                    {
                        return true;
                    }
                }
            }
        }
    }
    if (this->tk == Do)
    {
        getToken();
        if (statement())
        {
            if (this->tk == While)
            {
                getToken();
                if (this->tk == ParenthesisOpen)
                {
                    getToken();
                    if (expression())
                    {
                        if (this->tk == ParenthesisClose)
                        {
                            getToken();
                            if (this->tk == SemiCollon)
                            {
                                getToken();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    if (this->tk == For)
    {
        getToken();
        if (this->tk == ParenthesisClose)
        {
            getToken();
            if (expressionStatement())
            {
                if (expressionStatement())
                {
                    if (this->tk == ParenthesisClose)
                    {
                        getToken();
                        if (statement())
                        {
                            return true;
                        }
                    }
                    if (expression())
                    {
                        if (this->tk == ParenthesisClose)
                        {
                            getToken();
                            if (statement())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Syntatic::jumpStatement()
{
    if (this->tk == Continue)
    {
        getToken();
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }
    }
    if (this->tk == Break)
    {
        getToken();
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }
    }
    if (this->tk == Return)
    {
        getToken();
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }
        if (expression())
        {
            if (this->tk == SemiCollon)
            {
                getToken();
                return true;
            }
        }
    }
    return false;
}

// parabÃ©ns por chegar ao final do cÃ³digo