#include "../include/syntactic.h"
#include "string.h"
using namespace std;

Syntactic::Syntactic(vector<Token> results)
{
    this->tokenList = results;
    this->currentTokenIndex = -1;
}

int Syntactic::savePosition()
{
    return this->currentTokenIndex;
}

void Syntactic::restorePosition(int pos)
{
    this->currentTokenIndex = pos - 1;
    getToken();
}

void Syntactic::getToken()
{
    // funcao para pegar o token
    int size = this->tokenList.size();
    if (this->currentTokenIndex < size)
    {
        ++this->currentTokenIndex;
        this->tk = this->tokenList[this->currentTokenIndex].types;
        this->lexeme = this->tokenList[this->currentTokenIndex].value;
    }

    else
    {
        this->tk = EndOfFile;
    }
}

bool Syntactic::translationUnit()
{
    getToken();
    while (this->tk != EndOfFile)
    {
        if (!externalDeclaration())
        {
            return false;
        }
    }

    return true;
}

bool Syntactic::externalDeclaration()
{
    int position = savePosition();
    if (functionDeclaration())
    {
        return true;
    }
    else {
        restorePosition(position);
        if (declaration())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::functionDeclaration()
{
    if (declarationSpecifiers())
    {
        if (declarator())
        {
            if (declarationList())
            {
                if (compoundStatement())
                {
                    return true;
                }
            }

            if (compoundStatement())
            {
                return true;
            }
        }
    }

    if (declarator())
    {
        if (declarationList())
        {
            if (compoundStatement())
            {
                return true;
            }
        }

        if (compoundStatement())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::primaryExpression()
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

    else if (this->tk == CharConstant)
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

bool Syntactic::primaryExpression(string &primeExpCode)
{
    if (this->tk == Identifier)
    {
        primeExpCode = this->lexeme;
        getToken();
        return true;
    }

    else if (this->tk == Constant)
    {
        primeExpCode = this->lexeme;
        getToken();
        return true;
    }

    else if (this->tk == CharConstant)
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

bool Syntactic::postFixExpression()
{
    string primaryExpCode, postfixExpRCode;
    if (primaryExpression(primaryExpCode))
    {
        if (postFixExpressionR(postfixExpRCode))
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::postFixExpression(string &postFixExpCode)
{
    string primeExpCode, primeExpRCode;
    if (primaryExpression(primeExpCode))
    {
        postFixExpCode.append(primeExpCode);
        if (postFixExpressionR(primeExpRCode))
        {
            postFixExpCode.append(primeExpRCode);
            return true;
        }
    }

    return false;
}

bool Syntactic::postFixExpressionR()
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

        return false;
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

        return false;
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

        return false;
    }

    if (this->tk == IncOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }

        return false;
    }

    if (this->tk == DecOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }

        return false;
    }

    if (this->tk == BracketOpen)
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

        return false;
    }

    return true;
}

bool Syntactic::postFixExpressionR(string &postFixRCode)
{
    if (this->tk == IncOp)
    {
        postFixRCode = "++";
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }

        return false;
    }

    if (this->tk == DecOp)
    {
        getToken();
        if (postFixExpressionR())
        {
            return true;
        }

        return false;
    }

    if (this->tk == BracketOpen)
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

        return false;
    }

    return true;
}

bool Syntactic::argumentExpressionList()
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

bool Syntactic::argumentExpressionListR()
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

bool Syntactic::unaryExpression()
{
    string postFixExpCode;
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
        if (unaryExpression())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::unaryExpression(string &unaryCode)
{
    string postFixExpCode, unaryCode2;
    if (postFixExpression(postFixExpCode))
    {
        unaryCode.append(postFixExpCode);
        return true;
    }

    if (this->tk == IncOp)
    {
        unaryCode.append("++");
        getToken();
        if (unaryExpression(unaryCode2))
        {
            return true;
        }
    }

    if (this->tk == DecOp)
    {
        unaryCode.append("--");
        getToken();
        if (unaryExpression(unaryCode2))
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::unaryOperator()
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

bool Syntactic::castExpression()
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

bool Syntactic::multiplicativeExpression()
{
    string unaryExpCode;
    if (unaryExpression())
    {
        if (multiplicativeExpressionR())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::multiplicativeExpression(string &code)
{
    string unaryExpCode, multiplicativeExpCode;
    if (unaryExpression(unaryExpCode))
    {
        code.append(unaryExpCode);
        if (multiplicativeExpressionR(multiplicativeExpCode))
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::multiplicativeExpressionR()
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

bool Syntactic::multiplicativeExpressionR(string &code)
{

    string unaryCode, multExpCode;
    if (this->tk == Product)
    {
        getToken();
        if (unaryExpression(unaryCode))
        {
            if (multiplicativeExpressionR(multExpCode))
            {
                return true;
            }
        }
    }

    else if (this->tk == Division)
    {
        getToken();
        if (unaryExpression(unaryCode))
        {
            if (multiplicativeExpressionR(multExpCode))
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

bool Syntactic::additiveExpression()
{
    string multExpCode;
    if (multiplicativeExpression())
    {
        if (additiveExpressionR())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::additiveExpression(string &code)
{
    string multExpCode, additiveExpCode;
    if (multiplicativeExpression(multExpCode))
    {
        code.append(multExpCode);
        if (additiveExpressionR(additiveExpCode))
        {
            code.append(additiveExpCode);
            return true;
        }
    }

    return false;
}


bool Syntactic::additiveExpressionR()
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

bool Syntactic::additiveExpressionR(string &code)
{
    string addOpCode, multOpCode;
    if (this->tk == Plus)
    {
        addOpCode = ("\n\t+");
        getToken();
        if (multiplicativeExpression(multOpCode))
        {
            code.append("\n\tpush " + multOpCode + addOpCode);
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

bool Syntactic::shiftExpression()
{
    string additiveExp;
    if (additiveExpression())
    {
        if (shiftExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::shiftExpression(string &code)
{
    string additiveExp;
    if (additiveExpression(additiveExp))
    {
        code.append(additiveExp);
        if (shiftExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::shiftExpressionR()
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

bool Syntactic::relationalExpression()
{
    string shiftExpCode;
    if (shiftExpression())
    {
        if (relationalExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::relationalExpression(string &code)
{
    string shiftExpCode, relationExpCode;
    if (shiftExpression(shiftExpCode))
    {
        relationExpCode = shiftExpCode;
        if (relationalExpressionR(relationExpCode))
        {
            code.append(relationExpCode);
            return true;
        }
    }
    return false;
}

bool Syntactic::relationalExpressionR()
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

bool Syntactic::relationalExpressionR(string &code)
{
    string relationCode, expCode;
    if (this->tk == Less)
    {
        relationCode = "<";
        getToken();
        if (shiftExpression(expCode))
        {
            code.append("\n\tvalor-r " + code + "\n\tpush " + expCode + "\n\t" + relationCode);
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == Greater)
    {
        relationCode = ">";
        getToken();
        if (shiftExpression(expCode))
        {
            code.append("\tvalor-r " + code + "\n\tpush " + expCode + "\n\t" + relationCode);
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == LEOp)
    {
        relationCode = "<=";
        getToken();
        if (shiftExpression())
        {
            code.append("\tvalor-r " + code + "\n\tpush " + expCode + "\n\t" + relationCode);
            if (relationalExpressionR())
            {
                return true;
            }
        }
    }
    if (this->tk == GEOp)
    {
        relationCode = ">=";
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

bool Syntactic::equalityExpression()
{
    string relationalExp;
    if (relationalExpression())
    {
        if (equalityExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::equalityExpression(string &code)
{
    string relationalExp;
    if (relationalExpression(relationalExp))
    {
        code.append(relationalExp);
        if (equalityExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::equalityExpressionR()
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

bool Syntactic::andExpression()
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

bool Syntactic::andExpression(string &andExpCode)
{
    string equalityExpCode;
    if (equalityExpression(equalityExpCode))
    {
        andExpCode.append(equalityExpCode);
        if (andExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::andExpressionR()
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

bool Syntactic::exclusiveOrExpression()
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

bool Syntactic::exclusiveOrExpression(string &excOrCode)
{
    string andExpCode, excOrCodeR;
    if (andExpression(andExpCode))
    {
        excOrCode.append(andExpCode);
        if (exclusiveOrExpressionR(excOrCodeR))
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::exclusiveOrExpressionR()
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

bool Syntactic::exclusiveOrExpressionR(string &excOrCodeR)
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

bool Syntactic::inclusiveOrExpression()
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

bool Syntactic::inclusiveOrExpression(string &incOrExpCode)
{
    string excOrCode, inclOrCode;
    if (exclusiveOrExpression(excOrCode))
    {
        incOrExpCode.append(excOrCode);
        if (inclusiveOrExpressionR(inclOrCode))
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::inclusiveOrExpressionR()
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

bool Syntactic::inclusiveOrExpressionR(string incOrExpRCode)
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

bool Syntactic::logicalAndExpression(string &logicalCode)
{
    string incOrExpCode;
    if (inclusiveOrExpression(incOrExpCode))
    {
        logicalCode.append(incOrExpCode);
        if (logicalAndExpressionR())
        {
            return true;
        }
    }
    return false;
}

bool Syntactic::logicalAndExpression()
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

bool Syntactic::logicalAndExpressionR()
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

bool Syntactic::logicalOrExpression()
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

bool Syntactic::logicalOrExpression(string &logicalCode)
{
    string logicalCode2, logicalOrCode;
    if (logicalAndExpression(logicalCode2))
    {
        logicalCode.append(logicalCode2);
        if (logicalOrExpressionR(logicalOrCode))
        {
            logicalCode.append(logicalOrCode);
            return true;
        }
    }
    return false;
}

bool Syntactic::logicalOrExpressionR()
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

bool Syntactic::logicalOrExpressionR(string &logicalCodeR)
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

bool Syntactic::conditionExpression()
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

bool Syntactic::assignmentExpression()
{

    int position = savePosition();

    if (unaryExpression())
    {
        if (assignmentOperator())
        {

            int assPosition = savePosition();

            if (assignmentExpression())
            {
                return true;
            }

            else {
                restorePosition(assPosition);

                if (logicalOrExpression()) {
                    return true;
                }
            }
        }
    }

    restorePosition(position);
    if (logicalOrExpression()) {
        return true;
    }

    return false;
}

bool Syntactic::assignmentExpression(string &asgmtExpCode)
{

    int position = savePosition();
    string unaryCode, asgmtOppCode, asgmtExpCode2;
    string logicalCode;
    if (unaryExpression(unaryCode))
    {
        if (assignmentOperator(asgmtOppCode))
        {
            int assPosition = savePosition();

            if (assignmentExpression(asgmtExpCode2))
            {
                asgmtExpCode.append("\n\tvalor-l " + unaryCode + "\n\tpush " + asgmtExpCode2 + "\n\t" + asgmtOppCode);
                return true;
            }

            else {
                restorePosition(assPosition);

                if (logicalOrExpression(logicalCode)) {
                    return true;
                }
            }
        }
    }

    restorePosition(position);
    if (logicalOrExpression(logicalCode)) {
        asgmtExpCode.append(logicalCode);
        return true;
    }

    return false;
}

bool Syntactic::assignmentOperator()
{
    if (this->tk == Assign)
    {
        getToken();
        return true;
    }
    if (this->tk == MulAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == DivAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == ModAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == AddAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == LessAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == LeftAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == RightAssign)
    {
        getToken();
        return true;
    }
    return false;
}

bool Syntactic::assignmentOperator(string &asgmtCode)
{
    if (this->tk == Assign)
    {
        asgmtCode = "=";
        getToken();
        return true;
    }
    if (this->tk == MulAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == DivAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == ModAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == AddAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == LessAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == LeftAssign)
    {
        getToken();
        return true;
    }
    if (this->tk == RightAssign)
    {
        getToken();
        return true;
    }
    return false;
}


bool Syntactic::expression()
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

bool Syntactic::expression(string &expCode)
{
    string asgmtCode;
    if (assignmentExpression(asgmtCode))
    {
        if (expressionR(asgmtCode))
        {
            expCode.append(asgmtCode);
            return true;
        }
    }
    return false;
}


bool Syntactic::expressionR()
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

bool Syntactic::expressionR(string &expRCode)
{
    if (this->tk == Comma)
    {
        getToken();
        if (assignmentExpression(expRCode))
        {
            if (expressionR())
            {
                return true;
            }
        }
    }
    return true;
}

bool Syntactic::constantExrpression()
{
    if (logicalOrExpression())
    {
        return true;
    }

    return false;
}

bool Syntactic::declaration()
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

bool Syntactic::declarationSpecifiers()
{
    if (typeSpecifier())
    {
        if (declarationSpecifiers())
        {
            return true;
        }
        return true;
    }

    return false;
}

bool Syntactic::initDeclaratorList()
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

bool Syntactic::initDeclaratorListR()
{
    if (this->tk == Comma)
    {
        getToken();
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

bool Syntactic::initDeclarator()
{
    if (declarator())
    {
        if (this->tk == Assign)
        {
            getToken();
            if (initializer())
            {
                return true;
            }
        }

        return true;
    }

    return false;
}

bool Syntactic::typeSpecifier()
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
    if (this->tk == Long)
    {
        getToken();
        return true;
    }
    if (this->tk == Unsigned)
    {
        getToken();
        return true;
    }
    if (structSprecifier())
    {
        return true;
    }

    return false;
}

//bool Syntactic::longTypeSpecifier()
//{
//
//}
//
//bool Syntactic::unsignedTypeSpecifier()
//{
//
//}

bool Syntactic::specifierList()
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

bool Syntactic::structSprecifier()
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

bool Syntactic::structDeclarationList()
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

bool Syntactic::structDeclarationListR()
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

bool Syntactic::structDeclaration()
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

bool Syntactic::structDeclaratorList()
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

bool Syntactic::structDeclaratorListR()
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

bool Syntactic::structDeclarator()
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

bool Syntactic::declarator()
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

bool Syntactic::directDeclarator()
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

bool Syntactic::directDeclaratorR()
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

bool Syntactic::pointer()
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

bool Syntactic::parameterTypeList()
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

bool Syntactic::parameterList()
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

bool Syntactic::parameterListR()
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
            else
            {
                return false;
            }
        }

        else
        {
            return false;
        }
    }
    return true;
}

bool Syntactic::parameterDeclaration()
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

bool Syntactic::identifierList()
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

bool Syntactic::identifierListR()
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

bool Syntactic::typeName()
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

bool Syntactic::abstractDeclarator()
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

bool Syntactic::directAbstractDeclarator()
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

bool Syntactic::directAbstractDeclaratorR()
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

bool Syntactic::initializer()
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

bool Syntactic::initializerList()
{
    if (initializer())
    {
        if (initDeclaratorListR())
        {
            return true;
        }
    }

    return false;
}

bool Syntactic::initializerListR()
{
    if (this->tk == Comma)
    {
        getToken();
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

bool Syntactic::statement()
{

    int position = savePosition();
    if (labeledStatement())
    {
        return true;
    }
    restorePosition(position);
    if (compoundStatement())
    {
        return true;
    }
    restorePosition(position);
    if (expressionStatement())
    {
        return true;
    }
    restorePosition(position);
    if (selectionStatement())
    {
        return true;
    }
    restorePosition(position);
    if (iterationStatement())
    {
        return true;
    }
    restorePosition(position);
    if (jumpStatement())
    {
        return true;
    }

    return false;
}

bool Syntactic::statement(string &code)
{
    string stmtCode;
    int position = savePosition();
    if (compoundStatement(stmtCode))
    {
        code.append(stmtCode);
        return true;
    }
    restorePosition(position);
    if (expressionStatement(stmtCode))
    {
        code.append(stmtCode);
        return true;
    }
    return false;
}

bool Syntactic::labeledStatement()
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

bool Syntactic::compoundStatement()
{
    if (this->tk == BraceOpen)
    {
        getToken();

        if (this->tk == BraceClose)
        {
            getToken();
            return true;
        }

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

bool Syntactic::compoundStatementList()
{
    if (compoundStatementBody())
    {
        if (compoundStatementList())
        {
            return true;
        }

        return true;
    }

    return false;
}

bool Syntactic::compoundStatementBody()
{
    if (declarationList())
    {
        return true;
    }

    if (declarationList())
    {
        if (statementList()) {
            return true;
        }
    }

    else if (statementList())
    {
        return true;
    }

    return false;
}

bool Syntactic::compoundStatement(string &code)
{
    string compoundCode;
    if (this->tk == BraceOpen)
    {
        getToken();

        if (this->tk == BraceClose)
        {
            getToken();
            return true;
        }

        if (compoundStatementList(compoundCode))
        {
            code.append(compoundCode);
            if (this->tk == BraceClose)
            {

                getToken();
                return true;
            }
        }
    }
    return false;
}

bool Syntactic::compoundStatementList(string &code)
{
    string compoundCode, compundListCode;
    if (compoundStatementBody(compoundCode))
    {
        code.append(compoundCode);
        if (compoundStatementList(compundListCode))
        {
            code.append(compundListCode);
            return true;
        }

        return true;
    }

    return false;
}

bool Syntactic::compoundStatementBody(string &code)
{
    string stmtCode;
//    if (declarationList())
//    {
//        return true;
//    }
//
//    if (declarationList())
//    {
//        if (statementList()) {
//            return true;
//        }
//    }

    if (statementList(stmtCode))
    {
        code.append(stmtCode);
        return true;
    }

    return false;
}

bool Syntactic::declarationList()
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

bool Syntactic::statementList()
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

bool Syntactic::statementList(string &code)
{
    string stmtCode, stmtListCode;
    if (statement(stmtCode))
    {
        code.append(stmtCode);
        if (statementList(stmtListCode))
        {
            code.append(stmtListCode);
            return true;
        }
        code.append(stmtListCode);
        return true;
    }
    return false;
}

bool Syntactic::expressionStatement()
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

bool Syntactic::expressionStatement(string &expCode)
{
    string expCode2;
    if (this->tk == SemiCollon)
    {
        getToken();
        return true;
    }
    if (expression(expCode2))
    {
        expCode = expCode2;
        if (this->tk == SemiCollon)
        {
            getToken();
            return true;
        }
    }
    return false;
}

bool Syntactic::selectionStatement()
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

bool Syntactic::iterationStatement()
{
    string iterationCode, initCode, condCode, exprCode, stmtCode;
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
        if (this->tk == ParenthesisOpen)
        {
            getToken();
            if (expressionStatement(initCode))
            {
                iterationCode.append(initCode);
                iterationCode.append("\nINIT:\n");
                if (expressionStatement(condCode))
                {
                    iterationCode.append(condCode);
                    iterationCode.append("\n\tgofalse END\n");
                    if (this->tk == ParenthesisClose)
                    {
                        getToken();
                        if (statement(stmtCode))
                        {
                            // imprime código resultado
                            iterationCode.append(stmtCode);
                            cout << iterationCode << endl;
                            return true;
                        }
                    }
                    if (expression(exprCode))
                    {
                        iterationCode.append(exprCode);
                        if (this->tk == ParenthesisClose)
                        {
                            getToken();
                            if (statement(stmtCode))
                            {
                                // imprime código resultado
                                iterationCode.append("\n"+stmtCode);
                                iterationCode.append("\n\tgoto INIT");
                                iterationCode.append("\nEND:");
                                cout << iterationCode << endl;
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

bool Syntactic::jumpStatement()
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

// parabéns por chegar ao final do código
