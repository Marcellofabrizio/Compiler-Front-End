#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./token.hpp"

using namespace std;

int tk;

class Syntatic
{

public:
    int currentTokenIndex = 0;
    vector<Token> tokenList;

    Syntatic(vector<Token> results)
    {
        tokenList = results;
        getToken();
    }

    void getToken()
    {
        // funcao para pegar o token

        tk = tokenList[currentTokenIndex].types;
        currentTokenIndex++;
    }

    // externalDeclaration
    int externalDeclaration()
    {
        if (functionDeclaration() == 1)
        {
            return 1;
        }
        if (declaration() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // functionDeclaration
    int functionDeclaration()
    {
        if (declarationSpecifiers() == 1)
        {
            getToken();
            if (declarator() == 1)
            {
                getToken();
                if (declarationList() == 1)
                {
                    getToken();
                    if (compoundStatement() == 1)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                if (compoundStatement() == 1)
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
        if (declarator() == 1)
        {
            getToken();
            if (declarationList() == 1)
            {
                getToken();
                if (compoundStatement() == 1)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (compoundStatement() == 1)
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

    // primaryExpression
    int primaryExpression()
    {
        if (tk == Identifier)
        { // id
            return 1;
        }
        if (tk == Constant)
        {
            return 1;
        }
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (expression() == 1)
            {
                getToken();
                if (tk == ParenthesisClose)
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

    // postFixExpression
    int postFixExpression()
    {
        if (primaryExpression() == 1)
        {
            getToken();
            if(postFixExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int postFixExpressionR(){
        if(tk==BracketOpen){
            getToken();
            if(expression()==1){
                getToken();
                if(tk==BracketClose){
                    getToken();
                    if(postFixExpressionR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==ParenthesisOpen){
            getToken();
            if(tk==ParenthesisClose){
                getToken();
                if(postFixExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(argumentExpressionList()==1){
                getToken();
                if(tk==ParenthesisClose){
                    getToken();
                    if(postFixExpressionR()==1){
                        return 1;
                    }
                    else{
                      return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Dot){
            getToken();
            if(Identifier()==1){
                getToken();
                if(postFixExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Accessor){
            getToken();
            if(Identifier()==1){
                getToken();
                if(postFixExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==IncOp){
            getToken();
            if(postFixExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        if(tk==DecOp){
            getToken();
            if(postFixExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // argumentExpressionList
    int argumentExpressionList()
    {
        if (assignmentExpression() == 1)
        {
            getToken();
            if(argumentExpressionListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int argumentExpressionListR(){
        if(tk==Comma){
            getToken();
            if(assignmentExpression()==1){
                getToken();
                if(argumentExpressionListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // unaryExpression
    int unaryExpression()
    {
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
            else
            {
                return 0;
            }
        }
        if (tk == DecOp)
        {
            getToken();
            if (unaryExpression() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (unaryExpression() == 1)
        {
            getToken();
            if (castExpression() == 1)
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

    // unaryOperator
    int unaryOperator()
    {
        if (tk == AndOp)
        {
            return 1;
        }
        if (tk == Product)
        {
            return 1;
        }
        if (tk == Plus)
        {
            return 1;
        }
        if (tk == Minus)
        {
            return 1;
        }
        if (tk == Negate)
        {
            return 1;
        }
        if (tk == LogicalNot)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // castExpression
    int castExpression()
    {
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
    int multiplicativeExpression()
    {
        if (unaryExpression() == 1)
        {
            getToken();
            if(multiplicativeExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int multiplicativeExpressionR(){
        if(tk==Product){
            getToken();
            if(unaryExpression()==1){
                getToken();
                if(multiplicativeExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Division){
            getToken();
            if(unaryExpression()==1){
                getToken();
                if(multiplicativeExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Module){
            getToken();
            if(unaryExpression()==1){
                getToken();
                if(multiplicativeExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // additiveExpression
    int additiveExpression()
    {
        if (multiplicativeExpression() == 1)
        {
            getToken();
            if(additiveExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int additiveExpressionR(){
        if(tk==Plus){
            getToken();
            if(multiplicativeExpression()==1){
                getToken();
                if(additiveExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Minus){
            getToken();
            if(multiplicativeExpression()==1){
                getToken();
                if(additiveExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // shiftExpression
    int shiftExpression()
    {
        if (additiveExpression() == 1)
        {
            getToken();
            if(shiftExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int shiftExpressionR(){
        if(tk==LeftOp){
            getToken();
            if(additiveExpression()==1){
                getToken();
                if(shiftExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }  
            else{
                return 0;
            }
        }
        if(tk==RightOp){
            getToken();
            if(additiveExpression()==1){
                getToken();
                if(shiftExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }  
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // relationalExpression
    int relationalExpression()
    {
        if (shiftExpression() == 1)
        {
            getToken();
            if(relationalExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int relationalExpressionR(){
        if(tk==Less){
            getToken();
            if(shiftExpression()==1){
                getToken();
                if(relationalExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Greater){
            getToken();
            if(shiftExpression()==1){
                getToken();
                if(relationalExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==LEOp){
            getToken();
            if(shiftExpression()==1){
                getToken();
                if(relationalExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==GEOp){
            getToken();
            if(shiftExpression()==1){
                getToken();
                if(relationalExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }
    // equalityExpression
    int equalityExpression()
    {
        if (relationalExpression() == 1)
        {
            getToken();
            if(equalityExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int equalityExpressionR(){
        if(tk==EQOp){
            getToken();
            if(relationalExpression()==1){
                getToken();
                if(equalityExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }   
        if(tk==NEOp){
            getToken();
            if(relationalExpression()==1){
                getToken();
                if(equalityExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        } 
    }

    // andExpression
    int andExpression()
    {
        if (equalityExpression() == 1)
        {
            getToken();
            if(andExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int andExpressionR(){
        if(tk==AndOp){
            getToken();
            if(equalityExpression()==1){
                getToken();
                if(andExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // exclusiveOrExpression
    int exclusiveOrExpression()
    {
        if (andExpression() == 1)
        {
            getToken();
            if(exclusiveOrExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int exclusiveOrExpressionR(){
        if(tk==Power){
            getToken();
            if(andExpression()==1){
                getToken();
                if(exclusiveOrExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // inclusiveOrExpression
    int inclusiveOrExpression()
    {
        if (exclusiveOrExpression() == 1)
        {
            getToken();
            if(inclusiveOrExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int inclusiveOrExpressionR(){
        if(tk==OrOp){
            getToken();
            if(exclusiveOrExpression()==1){
                getToken();
                if(inclusiveOrExpressionR()==1){
                    return 1;
                }
                else{
                    return 0
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // logicalAndExpression
    int logicalAndExpression()
    {
        if (inclusiveOrExpression() == 1)
        {
            getToken();
            if(inclusiveAndExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int inclusiveAndExpressionR(){
        if(tk==AndOp){
            getToken();
            if(inclusiveOrExpression()==1){
                getToken();
                if(inclusiveAndExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }
    // logicalOrExpression
    int logicalOrExpression()
    {
        if (logicalAndExpression() == 1)
        {
            getToken();
            if(logicalOrExpressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int logicalOrExpressionR(){
        if(tk==OrOp){
            getToken();
            if(logicalAndExpression()==1){
                getToken();
                if(logicalOrExpressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // conditionExpression
    int conditionExpression()
    {
        if (logicalOrExpression() == 1)
        {
            getToken();
            if (tk == QuestionMark)
            {
                getToken();
                if (expression() == 1)
                {
                    getToken();
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
    int assignmentExpression()
    {
        if (conditionExpression() == 1)
        {
            return 1;
        }
        if (unaryExpression() == 1)
        {
            getToken();
            if (assignmentOperator() == 1)
            {
                getToken();
                if (assignmentExpression() == 1)
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

    // assignmentOperator
    int assignmentOperator()
    {
        if (tk == Assign)
        {
            return 1;
        }
        if (tk == MulAssign)
        {
            return 1;
        }
        if (tk == DivAssign)
        {
            return 1;
        }
        if (tk == ModAssign)
        {
            return 1;
        }
        if (tk == AddAssign)
        {
            return 1;
        }
        if (tk == LessAssign)
        {
            return 1;
        }
        if (tk == LeftAssign)
        {
            return 1;
        }
        if (tk == RightAssign)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // expression
    int expression()
    {
        if (assignmentExpression() == 1)
        {
            getToken();
            if(expressionR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int expressionR(){
        if(tk==Comma){
            getToken();
            if(assignmentExpression()==1){
                getToken();
                if(expressionR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // constantExrpression
    int constantExrpression()
    {
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
    int declaration()
    {
        if (declarationSpecifiers() == 1)
        {
            getToken();
            if (tk == SemiCollon)
            {
                return 1;
            }
            if (initDeclaratorList() == 1)
            {
                getToken();
                if (tk == SemiCollon)
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

    // declarationSpecifiers
    int declarationSpecifiers()
    {
        if (typeSpecifier() == 1)
        {
            getToken();
            if (declarationSpecifiers() == 1)
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

    // initDeclaratorList
    int initDeclaratorList()
    {
        if (initDeclarator() == 1)
        {
            getToken();
            if(initDeclaratorListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int initDeclaratorListR(){
        if(tk==Comma){
            getToken();
            if(initDeclarator()==1){
                getToken();
                if(initDeclaratorListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }
    // initDeclarator
    int initDeclarator()
    {
        if (declarator() == 1)
        {
            getToken();
            if (tk == Assign)
            {
                getToken();
                if (initializer() == 1)
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
        else
        {
            return 0;
        }
    }

    // typeSpecifier
    int typeSpecifier()
    {
        
        cout << "FunÃ§Ã£o: " << "typeSpecifier" << endl;
        cout << "Token: " << tk << endl;
        cout << "Index: " << currentTokenIndex << endl;

        if (tk == Void)
        {
            return 1;
        }
        if (tk == Char)
        {
            return 1;
        }
        if (tk == Short)
        {
            return 1;
        }
        if (tk == Int)
        {
            return 1;
        }
        if (tk == Long)
        {
            return 1;
        }
        if (tk == Float)
        {
            return 1;
        }
        if (tk == Double)
        {
            return 1;
        }
        if (tk == Signed)
        {
            return 1;
        }
        if (tk == Unsigned)
        {
            return 1;
        }
        if (structSprecifier() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // structSprecifier
    int structSprecifier()
    {
        if (structGrammar() == 1)
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
                        getToken();
                        if (tk == BraceClose)
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
            if (tk == BraceOpen)
            {
                getToken();
                if (structDeclarationList() == 1)
                {
                    getToken();
                    if (tk == BraceClose)
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
            return 0;
        }
    }

    // struct -> tive que mudar o nome devido ao VScode ser mala e reclamar
    int structGrammar()
    {
        if (tk == Struct)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // structDeclarationList
    int structDeclarationList()
    {
        if (structDeclarator() == 1)
        {
            getToken();
            if(structDeclarationListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    int structDeclarationListR(){
        if(tk==Comma){
            getToken();
            if(structDeclarator()==1){
                getToken();
                if(structDeclarationListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // structDeclarator
    int structDeclarator()
    {
        if (declarator() == 1)
        {
            getToken();
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
            else
            {
                return 1;
            }
        }
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
        else
        {
            return 0;
        }
    }

    // declarator
    int declarator()
    {
        if (pointer() == 1)
        {
            getToken();
            if (directDeclarator() == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (directDeclarator() == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // directDeclarator
    int directDeclarator()
    {
        if (tk == Identifier)
        {
            getToken();
            if(directDeclaratorR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (declarator() == 1)
            {
                getToken();
                if (tk == ParenthesisClose)
                {
                    getToken();
                    if(directDeclaratorR()==1){
                        return 1;
                    }
                    else{
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
            return 0;
        }
    }
    int directDeclaratorR(){
        if(tk==ParenthesisOpen){
            getToken();
            if(tk==ParenthesisClose){
                getToken();
                if(directDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(parameterTypeList()==1){
                getToken();
                if(tk==ParenthesisClose){
                    getToken();
                    if(directDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==BracketOpen){
            getToken();
            if(tk==BracketClose){
                getToken();
                if(directDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(constantExrpression()==1){
                getToken();
                if(tk==BracketClose){
                    getToken();
                    if(directDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // pointer
    int pointer()
    {
        if (tk == Product)
        {
            getToken();
            if (pointer() == 1)
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

    // parameterTypeList
    int parameterTypeList()
    {
        if (parameterList() == 1)
        {
            getToken();
            if (tk == Comma)
            {
                getToken();
                if (tk == Ellipsis)
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
        else
        {
            return 0;
        }
    }

    // parameterList
    int parameterList()
    {
        if(paramaeterDeclaration()==1){
            getToken();
            if(parameterListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;            
        }

    }
    int parameterListR(){
        if(tk==Comma){
            getToken();
            if(paramaeterDeclaration()==1){
                getToken();
                if(parameterListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // paramaeterDeclaration
    int paramaeterDeclaration()
    {
        if(declarationSpecifiers()==1){
            getToken();
            if(declarator()==1){
                return 1;
            }
            if(abstractDeclarator()==1){
                return 1;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }

    // identifierList
    int identifierList()
    {
        if(tk==Identifier){
            getToken();
            if(identifierListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    int identifierListR(){
        if(tk==Comma){
            getToken();
            if(Identifier()==1){
                getToken();
                if(identifierListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }  
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // typeName    SPECIFIERLIST NÃƒO DECLARADO NA GRAMATICA
    int typeName()
    {
        if(specifierList()==1){
            getToken();
            if(abstractDeclarator()==1){
                return 1;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }

    // abstractDeclarator
    int abstractDeclarator()
    {
        if(pointer()==1){
            getToken();
            if(directAbstractDeclarator()==1){
                return 1;
            }
            else{
                return 1;
            }
        }
        if(directAbstractDeclarator()==1){
            return 1;
        }
        else{
            return 0;
        }
    }

    // directAbstractDeclarator
    int directAbstractDeclarator()
    {
        if(tk==ParenthesisOpen){
            getToken();
            if(tk==ParenthesisClose){
                getToken();
                if(directAbstractDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(parameterTypeList()==1){
                getToken();
                if(tk==ParenthesisClose){
                    getToken();
                    if(directAbstractDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            if(abstractDeclarator()==1){
                getToken();
                if(tk==ParenthesisClose){
                    getToken();
                    if(directAbstractDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==BracketClose){
            getToken();
            if(tk==BracketClose){
                getToken();
                if(directAbstractDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==BracketOpen){
            getToken();
            if(constantExrpression()==1){
                getToken();
                if(tk==BracketOpen){
                    getToken();
                    if(directAbstractDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    int directAbstractDeclaratorR(){
        if(tk==BracketOpen){
            getToken();
            if(tk==BracketClose){
                getToken();
                if(directAbstractDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(conditionExpression()==1){
                getToken();
                if(tk==BracketClose){
                    getToken();
                    if(directAbstractDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==ParenthesisOpen){
            getToken();
            if(tk==ParenthesisClose){
                getToken();
                if(directAbstractDeclaratorR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(parameterTypeList()==1){
                getToken();
                if(tk==ParenthesisClose){
                    getToken();
                    if(directAbstractDeclaratorR()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 1;
        }
    }

    // initializer
    int initializer()
    {
        if(assignmentExpression()==1){
            return 1;
        }
        if(tk==BraceOpen){
            getToken();
            if(initializerList()==1){
                getToken();
                if(tk==BraceClose){
                    return 1;
                }
                if(tk==Comma){
                    getToken();
                    if(tk==BraceClose){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // initializerList
    int initializerList()
    {
        if(initializer()==1){
            getToken();
            if(initializerListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    int initializerListR(){
        if(tk==Comma){
            getToken();
            if(initializer()==1){
                getToken();
                if(initializerListR()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }   
        else{
            return 1;
        }
    }

    // statement
    int statement()
    {
        if(labeledStatement()==1){
            return 1;
        }
        if(compoundStatement()==1){
            return 1;
        }
        if(expressionStatement()==1){
            return 1;
        }
        if(selectionsStatement()==1){
            return 1;
        }
        if(iterationStatement()==1){
            return 1;
        }
        if(jumpStatement()==1){
            return 1;
        }
        else{
            return 0;
        }
    }

    // labeledStatement
    int labeledStatement()
    {
        if(tk==Identifier){
            getToken();
            if(tk==Collon){
                getToken();
                if(statement()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Case){
            getToken();
            if(constantExrpression()==1){
                getToken();
                if(tk==Collon){
                    getToken();
                    if(statement()==1){
                        return 1;
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Default){
            getToken();
            if(tk==Collon){
                getToken();
                if(statement()==1){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // compoundStatement          //REVISAR GRAMATICA LINHA 288
    int compoundStatement()
    {
        if(tk==BraceOpen){
            getToken();
            if(tk==BraceClose){
                return 1;
            }
            if(statementList()==1){
                getToken();
                if(tk==BraceClose){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(declarationList()==1){
                getToken();
                if(tk==BraceClose){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // declarationList
    int declarationList()
    {
        if(declaration()==1){
            getToken();
            if(declarationListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    int declarationListR(){
        if(declaration()==1){
            getToken();
            if(declarationListR()==1){
                return 1;
            }
            else{
                return 0
            }
        }
        else{
            return 1;
        }
    }

    // statementList
    int statementList()
    {
        if(statement()==1){
            getToken();
            if(statementListR()==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    int statementListR(){
        if(statement()==1){
            getToken();
            if(statementListR()==1){
                return 1;
            }
            else{
                return 0
            }
        }
        else{
            return 1;
        }
    }

    // expressionStatement
    int expressionStatement()
    {
        if(tk==SemiCollon){
            return 1;
        }
        if(expression()==1){
            getToken();
            if(tk==SemiCollon){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // selectionsStatement
    int selectionsStatement()
    {
        if(tk==If){
            getToken();
            if(tk==ParenthesisOpen){
                getToken();
                if(expression()==1){
                    getToken();
                    if(tk==ParenthesisClose){
                        getToken();
                        if(statement()==1){
                            getToken();
                            if(tk==Else){
                                getToken();
                                if(statement()==1){
                                    return 1;
                                }
                                else{
                                    return 0;
                                }
                            }
                            else{
                                return 1;
                            }
                        }
                        else{
                            return 0;
                        }
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Switch){
            getToken();
            if(tk==ParenthesisOpen){
                getToken();
                if(expression()==1){
                    getToken();
                    if(tk==ParenthesisClose){
                        getToken();
                        if(statement()==1){
                            return 1;
                        }
                        else{
                            return 0;
                        }
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // iterationStatement
    int iterationStatement()
    {
        if(tk==While){
            getToken();
            if(tk==ParenthesisOpen){
                getToken();
                if(expression()==1){
                    getToken();
                    if(tk==ParenthesisClose){
                        getToken();
                        if(statement()==1){
                            return 1;
                        }
                        else{
                            return 0;
                        }
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==Do){
            getToken();
            if(statement()==1){
                getToken();
                if(tk==While){
                    getToken();
                    if(tk==ParenthesisOpen){
                        getToken();
                        if(expression()==1){
                            getToken();
                            if(tk==ParenthesisClose){
                                getToken();
                                if(tk==SemiCollon){
                                    return 1;
                                }
                                else{
                                    return 0;
                                }
                            }
                            else{
                                return 0;
                            }
                        }
                        else{
                            return 0;
                        }
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        if(tk==For){
            getToken();
            if(tk==ParenthesisOpen){
                getToken();
                if(expressionStatement()==1){
                    getToken();
                    if(expressionStatement()==1){
                        getToken(); 
                        if(tk==ParenthesisClose){
                            getToken();
                            if(statement()==1){
                                return 1;
                            }
                            else{
                                return 0;
                            }
                        }
                        if(expression()==1){
                            getToken();
                            if(tk==ParenthesisClose){
                                getToken();
                                if(statement()==1){
                                    return 1;
                                }
                                else{
                                    return 0;
                                }
                            }
                            else{
                                return 0;
                            }
                        }
                        else{
                            return 0;
                        }
                    }
                    else{
                        return 0;
                    }
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    // jumpStatement
    int jumpStatement()
    {
        if(tk==Continue){
            getToken();
            if(tk==SemiCollon){
                return 1;
            }
            else{
                return 0;
            }
        }
        if(tk==Break){
            getToken();
            if(tk==SemiCollon){
                return 1;
            }
            else{
                return 0;
            }
        }
        if(tk==Return){
            getToken();
            if(tk==SemiCollon){
                return 1;
            }
            if(expression()==1){
                getToken();
                if(tk==SemiCollon){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
};

// parabÃ©ns por chegar ao final do cÃ³digo