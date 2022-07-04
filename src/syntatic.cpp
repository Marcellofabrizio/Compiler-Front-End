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
bool Syntatic::Syntatic::externalDeclaration()
{
    savePosition();
    if (functionDeclaration())
    {
        return true;
    }
    else
    {
        restorePosition();
        getToken();

        if (declaration())
        {
            return true;
        }
    }

    return false
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
    if (tk == Identifier)
    {
        getToken();
        return true;
    }

    else if (tk == Constant)
    {
        getToken();
        return true;
    }

    else if (tk == ParenthesisOpen)
    {
        getToken();
        if (expression())
        {
            if (tk == ParenthesisClose)
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

    if (tk == ParenthesisOpen)
    {
        getToken();
        if (tk == ParenthesisClose)
        {
            getToken();
            if (postFixExpressionR())
            {
                return true;
            }
        }

        else if (argumentExpressionList())
        {
            if (tk == ParenthesisClose)
            {
                getToken();
                if (postFixExpressionR())
                {
                    return true;
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
            if (postFixExpressionR())
            {
                return true;
            }
        }
    }

    if (tk == Accessor)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (postFixExpressionR())
            {
                return true;
            }
        }
    }

    if (tk == IncOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }
    }

    if (tk == DecOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }
    }

    if (tk == BraceOpen)
    {
        getToken();
        if (expression())
        {
            if (tk == BracketClose)
            {
                getToken();
                if (postFixExpressionR())
                {
                    return true;
                }
            }
        }
    }

    return true
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
    if (tk == Comma)
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

    if (tk == IncOp)
    {
        getToken();
        if (unaryExpression())
        {
            return true;
        }
    }

    if (tk == DecOp)
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
    if (tk == AndOp)
    {
        getToken();
        return true;
    }
    if (tk == Product)
    {
        getToken();
        return true;
    }
    if (tk == Plus)
    {
        getToken();
        return true;
    }
    if (tk == Minus)
    {
        getToken();
        return true;
    }
    if (tk == Negate)
    {
        getToken();
        return true;
    }
    if (tk == LogicalNot)
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

    else if (tk == ParenthesisOpen)
    {
        getToken();
        if (typeName())
        {
            if (tk == ParenthesisClose)
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

    if (tk == Product)
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

    else if (tk == Division)
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

    else if (tk == Module)
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
    if (tk == Plus)
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

    else if (tk == Minus)
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

// parabÃ©ns por chegar ao final do cÃ³digo