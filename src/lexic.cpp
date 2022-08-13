#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../include/lexic.h"

Lexic::Lexic(string filename)
{

    this->column = 0;
    this->line = 0;
    this->state = State::DEF;
    this->lexeme = "";
    this->infile = ifstream(filename);

    if (infile.bad())
    {
        throw invalid_argument("Error opening file stream");
    }
    else
    {
        cout << "Só sucesso" << endl;
    }
}

void Lexic::readLine()
{
    if (!getline(this->infile, this->lineBuffer))
    {
        this->currentChar = -1;
        return;
    }

    this->lineBuffer += '\n';
    this->column = 0;
    this->line++;
    return;
}

void Lexic::readCharacter()
{
    if (this->currentChar == '\n' || this->lineBuffer.empty())
    {
        readLine();
        if (this->currentChar == -1)
        {
            this->results.push_back({ "EoF", EndOfFile });
            return;
        }
    }

    this->currentChar = this->lineBuffer[this->column++];
}

void Lexic::unreadCharacter()
{
    this->column--;
    this->currentChar = this->lineBuffer[this->column];
}

void Lexic::addToLexeme()
{
    this->lexeme += this->currentChar;
}

void Lexic::clearLexeme()
{
    this->lexeme = "";
}

void Lexic::analyze()
{
    readCharacter();
    while (!this->infile.eof())
    {
        switch (this->state)
        {
            case State::DEF:
                analyzeDefaultState();
                break;

            case State::KeywordState:
                analyzeStringState();
                break;

            case State::Digit:
                analyzeDigitState();
                break;
        }
    }
}

void Lexic::analyzeDefaultState()
{
    if (this->currentChar == ' ' || this->currentChar == '\t' || this->currentChar == '\n' || this->currentChar == '\r')
    {
        clearLexeme();
        readCharacter();
        return;
    }

    else if (isalpha(this->currentChar) || this->currentChar == '_')
    {
        addToLexeme();
        readCharacter();
        this->state = State::KeywordState;
        return;
    }
    else if (this->currentChar == '\'' )
    {
        readCharacter();
        this->state = State::KeywordState;
        return;
    }
    else if (isdigit(this->currentChar))
    {
        this->state = State::Digit;
        return;
    }
    else if (this->currentChar == '=')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "Igual", EQOp });
            return;
        }
        unreadCharacter();
        setToken({ "Igual", Assign });
        return;
    }
    else if (this->currentChar == '+')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '+')
        {
            addToLexeme();
            setToken({ "Incremento", IncOp});
            return;
        }
        else if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "PlusAssign", AddAssign });
            return;
        }
        unreadCharacter();
        setToken({ "Soma", Plus });
        return;
    }
    else if (this->currentChar == '-')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '-')
        {
            addToLexeme();
            setToken({ "Decremento", DecOp });
            return;
        }
        else if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "MinusAssign", LessAssign });
            return;
        }
        else if (this->currentChar == '>')
        {
            addToLexeme();
            setToken({ "Accessor", Accessor });
            return;
        }
        unreadCharacter();
        setToken({ "Substração", Minus });
        return;
    }
    else if (this->currentChar == '*')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "MulAssign", MulAssign });
            return;
        }
        setToken({ "Multiplicação", Product });
        return;
    }
    else if (this->currentChar == '/')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "DivisionAssign", DivAssign });
            return;
        }
        unreadCharacter();
        setToken({ "Division", Division });
        return;
    }
    else if (this->currentChar == '%')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "ModuleAssign", ModAssign });
            return;
        }
        unreadCharacter();
        addToLexeme();
        setToken({ "Modulo", Module });
        return;
    }
    else if (this->currentChar == '[')
    {
        addToLexeme();
        setToken({ "Operador", BracketOpen });
        return;
    }
    else if (this->currentChar == ']')
    {
        addToLexeme();
        setToken({ "Operador", BracketClose });
        return;
    }
    else if (this->currentChar == '(')
    {
        addToLexeme();
        setToken({ "Operador", ParenthesisOpen });
        return;
    }
    else if (this->currentChar == ')')
    {
        addToLexeme();
        setToken({ "Operador", ParenthesisClose });
        return;
    }
    else if (this->currentChar == '{')
    {
        addToLexeme();
        setToken({ "Operador", BraceOpen });
        return;
    }
    else if (this->currentChar == '}')
    {
        addToLexeme();
        setToken({ "Operador", BraceClose });
        return;
    }
    else if (this->currentChar == ',')
    {
        addToLexeme();
        setToken({ "Operador", Comma });
        return;
    }
    else if (this->currentChar == ';')
    {
        addToLexeme();
        setToken({ "Operador", SemiCollon });
        return;
    }
    else if (this->currentChar == ':')
    {
        addToLexeme();
        setToken({ "Operador", Collon });
        return;
    }
    else if (this->currentChar == '~')
    {
        addToLexeme();
        setToken({ "Negação", Negate });
        return;
    }
    else if (this->currentChar == '^')
    {
        addToLexeme();
        setToken({ "Potência", Power });
        return;
    }
    else if (this->currentChar == '.')
    {
        addToLexeme();
        setToken({ "Acessor", Accessor });
        return;
    }
    else if (this->currentChar == '!')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "Diferente", NEOp });
            return;
        }
        unreadCharacter();
        setToken({ "Not Lógido", LogicalNot });
        return;
    }
    else if (this->currentChar == '&')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '&')
        {
            addToLexeme();
            setToken({ "LogicalAnd", LogicalAnd });
            return;
        }
        unreadCharacter();
        setToken({ "And", AndOp });
        return;
    }
    else if (this->currentChar == '|')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '|')
        {
            addToLexeme();
            setToken({ "LogicalOr", LogicalOr });
            return;
        }
        unreadCharacter();
        setToken({ "Or", OrOp });
        return;
    }

    else if (this->currentChar == '>')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "Maior Igual", GEOp });
            return;
        }
        else if (this->currentChar == '>')
        {
            addToLexeme();
            setToken({ "RightOp", RightOp });
            return;
        }
        unreadCharacter();
        setToken({ "Maior", Greater });
        return;
    }
    else if (this->currentChar == '<')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({ "Menor Igual", LEOp });
            return;
        }
        else if (this->currentChar == '<')
        {
            addToLexeme();
            setToken({ "LeftOp", LeftOp });
            return;
        }
        unreadCharacter();
        setToken({ "Menor", Less });
        return;
    }
}

void Lexic::analyzeStringState()
{

    if (isalpha(this->currentChar) || isdigit(this->currentChar) || this->currentChar == '_')
    {
        addToLexeme();
        readCharacter();
        return;
    }

    if (this->currentChar == '\'')
    {
        this->currentToken = {
                this->lexeme,
                CharConstant
        };
        setToken(this->currentToken);
        this->state = State::DEF;
    }

    else
    {
        unreadCharacter();
        this->currentToken = getKeyword();
        setToken(this->currentToken);
        this->state = State::DEF;
    }
    return;
}

void Lexic::analyzeDigitState()
{
    if (isdigit(this->currentChar) || (this->currentChar == '.'))
    {
        addToLexeme();
        readCharacter();
        return;
    }

    unreadCharacter();

    this->currentToken = {
            "Constant",
            Constant };
    setToken(this->currentToken);
    state = State::DEF;
}

void Lexic::analyzeFloatingPointState()
{

    if (isdigit(this->currentChar) > 0)
    {
        readCharacter();
        return;
    }

    else if (this->currentChar == '.')
    {
        this->state = State::Error;
        return;
    }

    unreadCharacter();
    this->currentToken = {
            "FloatingPointConstant",
            Constant };
    setToken(this->currentToken);
    this->state = State::DEF;
}

void Lexic::setToken(Token token)
{
    cout << "Token encontrado: " << this->lexeme << endl;
    cout << "Token tipo: " << token.types << endl;
    cout << "Token na linha " << this->line << " coluna " << this->column << endl
         << endl;

    TokenOccurence occurence;
    occurence.token =
            {this->lexeme,
             token.types
    };

    occurence.declarationLine = NULL;

    if(token.types == Identifier) {
        occurence.declarationLine = line;
    }

    this->results.push_back(occurence);

    clearLexeme();
    readCharacter();
}

void Lexic::handleError()
{
    cout << "Erro léxico na linha " << this->line << " coluna " << this->column << endl;
    return;
}

Token Lexic::getKeyword()
{

    Token foundKeyword = {
            lexeme,
            Identifier };

    for (const Token& keyword : keywords)
    {
        if (keyword.value == this->lexeme)
        {
            foundKeyword = keyword;
        }
    }

    return foundKeyword;
}