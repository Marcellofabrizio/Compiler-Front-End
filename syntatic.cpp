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
            return 1;
        }
        if (postFixExpression() == 1)
        {
            getToken();
            if (tk == BracketOpen)
            {
                getToken();
                if (expression() == 1)
                {
                    getToken();
                    if (tk == BracketClose)
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
            if (tk == ParenthesisOpen)
            {
                getToken();
                if (tk == ParenthesisClose)
                {
                    return 1;
                }
                if (argumentExpressionList() == 1)
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
            if (tk == Dot)
            {
                getToken();
                if (tk == Identifier)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (tk == Accessor)
            {
                getToken();
                if (tk == Identifier)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (tk == IncOp)
            {
                return 1;
            }
            if (tk == DecOp)
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

    // argumentExpressionList
    int argumentExpressionList()
    {
        if (assignmentExpression() == 1)
        {
            return 1;
        }
        if (argumentExpressionList() == 1)
        {
            getToken();
            if (tk == Comma)
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
            return 1;
        }
        if (multiplicativeExpression() == 1)
        {
            getToken();
            if (tk == Product)
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
            if (tk == Division)
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
            if (tk == Module)
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

    // additiveExpression
    int additiveExpression()
    {
        if (multiplicativeExpression() == 1)
        {
            return 1;
        }
        if (additiveExpression() == 1)
        {
            getToken();
            if (tk == Plus)
            {
                getToken();
                if (multiplicativeExpression() == 1)
                {
                    return 1;
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

    // shiftExpression
    int shiftExpression()
    {
        if (additiveExpression() == 1)
        {
            return 1;
        }
        if (shiftExpression() == 1)
        {
            getToken();
            if (tk == LeftOp)
            {
                getToken();
                if (additiveExpression() == 1)
                {
                    return 1;
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

    // relationalExpression
    int relationalExpression()
    {
        if (shiftExpression() == 1)
        {
            return 1;
        }
        if (relationalExpression() == 1)
        {
            getToken();
            if (tk == Less)
            {
                getToken();
                if (shiftExpression() == 1)
                {
                    return 1;
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
                    return 1;
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
                    return 1;
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

    // equalityExpression
    int equalityExpression()
    {
        if (relationalExpression() == 1)
        {
            return 1;
        }
        if (equalityExpression() == 1)
        {
            getToken();
            if (tk == EQOp)
            {
                getToken();
                if (relationalExpression() == 1)
                {
                    return 1;
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

    // andExpression
    int andExpression()
    {
        if (equalityExpression() == 1)
        {
            return 1;
        }
        if (andExpression() == 1)
        {
            getToken();
            if (tk == AndOp)
            {
                getToken();
                if (equalityExpression() == 1)
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

    // exclusiveOrExpression
    int exclusiveOrExpression()
    {
        if (andExpression() == 1)
        {
            return 1;
        }
        if (exclusiveOrExpression() == 1)
        {
            getToken();
            if (tk == Power)
            {
                getToken();
                if (andExpression() == 1)
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

    // inclusiveOrExpression
    int inclusiveOrExpression()
    {
        if (exclusiveOrExpression() == 1)
        {
            return 1;
        }
        if (inclusiveOrExpression() == 1)
        {
            getToken();
            if (tk == OrOp)
            {
                getToken();
                if (exclusiveOrExpression() == 1)
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

    // logicalAndExpression
    int logicalAndExpression()
    {
        if (inclusiveOrExpression() == 1)
        {
            return 1;
        }
        if (logicalAndExpression() == 1)
        {
            getToken();
            if (tk == AndOp)
            {
                getToken();
                if (inclusiveOrExpression() == 1)
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

    // logicalOrExpression
    int logicalOrExpression()
    {
        if (logicalAndExpression() == 1)
        {
            return 1;
        }
        if (logicalOrExpression() == 1)
        {
            getToken();
            if (tk == OrOp)
            {
                getToken();
                if (logicalAndExpression() == 1)
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
            return 1;
        }
        if (expression() == 1)
        {
            getToken();
            if (tk == Comma)
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
            return 1;
        }
        if (initDeclaratorList() == 1)
        {
            getToken();
            if (tk == Comma)
            {
                getToken();
                if (initDeclarator() == 1)
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
        
        cout << "Func: " << "typeSpecifier" << endl;
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
            return 1;
        }
        if (structDeclarationList() == 1)
        {
            getToken();
            if (tk == Comma)
            {
                getToken();
                if (structDeclarator() == 1)
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
            return 1;
        }
        if (tk == ParenthesisOpen)
        {
            getToken();
            if (declarator() == 1)
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
        if (directDeclarator() == 1)
        {
            getToken();
            if (tk == BracketOpen)
            {
                getToken();
                if (constantExrpression() == 1)
                {
                    getToken();
                    if (tk == BracketClose)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                if (tk == BracketClose)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            if (tk == ParenthesisOpen)
            {
                getToken();
                if (parameterTypeList() == 1)
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
            return 1;
        }
        if(parameterList()==1){
            getToken();
            if(tk==Comma){
                getToken();
                if(paramaeterDeclaration()==1){
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
        return 1;
       }
       if(identifierList()==1){
            getToken();
            if(tk==Comma){
                getToken();
                if(tk==Identifier){
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
                return 1;
            }
            if(parameterTypeList()==1){
                getToken();
                if(tk==ParenthesisClose){
                    return 1;
                }
                else{
                    return 0;
                }
            }
            if(abstractDeclarator()==1){
                getToken();
                if(tk==ParenthesisClose){
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
        if(tk==BracketClose){
            getToken();
            if(tk==BracketClose){
                return 1;
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
        if(directAbstractDeclarator()==1){
            getToken();
            if(tk==BracketOpen){
                getToken();
                if(tk==BracketClose){
                    return 1;
                }
                if(conditionExpression()==1){
                    getToken();
                    if(tk==BracketClose){
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
            if(tk==ParenthesisOpen){
                getToken();
                if(tk==ParenthesisClose){
                    return 1;
                }
                if(parameterTypeList()==1){
                    getToken();
                    if(tk==ParenthesisClose){
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
            return 1;
        }
        if(initializerList()==1){
            getToken();
            if(tk==Comma){
                getToken();
                if(initializer()==1){
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
            return 1;
        }
        if(declarationList()==1){
            getToken();
            if(declaration()==1){
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

    // statementList
    int statementList()
    {
        if(statement()==1){
            return 1;
        }
        if(statementList()==1){
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