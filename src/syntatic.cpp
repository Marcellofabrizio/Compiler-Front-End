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
    if (tk == LeftOp)
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
    if (tk == RightOp)
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
    if (tk == Less)
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
    if (tk == Greater)
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
    if (tk == LEOp)
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
    if (tk == GEOp)
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
    if (tk == EQOp)
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
    if (tk == NEOp)
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
    if (tk == AndOp)
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
    if (tk == Power)
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
    if (tk == OrOp)
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
    if (tk == AndOp)
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
    if (tk == OrOp)
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
        if (tk == QuestionMark)
        {
            getToken();
            if (expression())
            {
                if (tk == Colon)
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
    if (tk == Assign)
    {
        return true;
    }
    if (tk == MulAssign)
    {
        return true;
    }
    if (tk == DivAssign)
    {
        return true;
    }
    if (tk == ModAssign)
    {
        return true;
    }
    if (tk == AddAssign)
    {
        return true;
    }
    if (tk == LessAssign)
    {
        return true;
    }
    if (tk == LeftAssign)
    {
        return true;
    }
    if (tk == RightAssign)
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
    if (tk == Comma)
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
        if (tk == SemiCollon)
        {
            getToken();
            return true;
        }

        else if (initDeclaratorList())
        {
            if (tk == SemiCollon)
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
    if (tk == Comma)
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
        if (tk == Assign)
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
    if (tk == Void)
    {
        getToken();
        return true;
    }
    if (tk == Char)
    {
        getToken();
        return true;
    }
    if (tk == Short)
    {
        getToken();
        return true;
    }
    if (tk == Int)
    {
        getToken();
        return true;
    }
    if (tk == Long)
    {
        getToken();
        return true;
    }
    if (tk == Float)
    {
        getToken();
        return true;
    }
    if (tk == Double)
    {
        getToken();
        return true;
    }
    if (tk == structSprecifier())
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
    if (tk == Struct)
    {
        getToken();
        if (tk == Identifier)
        {
            getToken();
            if (tk == BraceOpen)
            {
                getToken();
                if (structDeclarationList())
                {
                    if (tk == BracketClose)
                    {
                        getToken();
                        return true;
                    }
                }
            }

            return true;
        }

        else if (tk == BraceOpen)
        {
            getToken();

            if (structDeclarationList())
            {
                if (tk == BraceClose)
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
            if (tk == SemiCollon)
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
    if (tk == Comma)
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
        if (tk == Collon)
        {
            getToken();
            if (logicalOrExpression())
            {
                return true;
            }
        }

        return true;
    }

    else if (tk == Collon)
    {
        getToken();
        if (logicalOrExpression())
        {
            return true;
        }
    }

    return false;
}

bool Syntatic::declarator(){
    if(directDeclarator()){
        return true;
    }
    if(pointer()){
        if(directDeclarator()){
            return true;
        }
    }
    return false; 
}

bool Syntatic::directDeclarator(){
    if(tk==Identifier){
        getToken();
        if(directDeclaratorR()){
            return true;
        }
    }
    if(tk==ParenthesisOpen){
        getToken();
        if(declarator()){
            if(tk==ParenthesisClose){
                getToken();
                if(directDeclaratorR()){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Syntatic::directDeclaratorR(){
    if(tk==BracketOpen){
        getToken();
        if(tk==BracketClose){
            getToken();
            if(directDeclaratorR()){
                return true;
            }
        }
        if(logicalOrExpression()){
            if(tk==BracketClose){
                getToken();
                if(directDeclaratorR()){
                    return true;
                }
            }
        }
    }
    if(tk==ParenthesisOpen){
        getToken();
        if(tk==ParenthesisClose){
            getToken();
            if(directDeclaratorR()){
                return true;
            }
        }
        if(parameterTypeList()){
            if(tk==ParenthesisClose){
                getToken();
                if(directDeclaratorR()){
                    return true;
                }
            }
        }
    }
    return true;
    
}

bool Syntatic::pointer(){
    if(tk==Product){
        getToken();
        if(pointer()){
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::parameterTypeList(){
    if(parameterList()){
        if(tk==Comma){
            getToken();
            if(tk==Ellipsis){
                getToken();
                return true;
            }
        }
        return true;
    }
    return false;
}

bool Syntatic::parameterList(){
    if(parameterDeclaration()){
        if(parameterListR()){
            return true;
        }
    }
    return false;
}

bool Syntatic::parameterListR(){
    if(tk==Comma){
        getToken();
        if(parameterDeclaration()){
            if(parameterListR()){
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::parameterDeclaration(){
    if(declarationSpecifiers()){
        if(declarator()){
            return true;
        }
        if(abstractDeclarator()){
            return true;
        }
        return true;
    }
    return false;
}

bool Syntatic::identifierList(){
    if(tk==Identifier){
        getToken();
        if(identifierListR()){
            return true;
        }
    }
    return false;
}

bool Syntatic::identifierListR(){
    if(tk==Comma){
        getToken();
        if(tk==Identifier){
            getToken();
            if(identifierListR()){
                return true;
            }
        }
    }
    return true;
}

bool Syntatic::typeName(){
    if(specifierList()){
        if(abstractDeclarator()){
            return true;
        }
        return true;
    }
    return false;
}

// parabÃ©ns por chegar ao final do cÃ³digo