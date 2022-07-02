#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "../include/parser.h"

#define RED "\033[31m" /* Red */

using namespace std;

Parser::Parser(string filename)
{
    this->column = 0;
    this->line = 0;
    this->lexeme = "";
    this->state = Deffault;

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

void readLine()
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

void readCharacter()
{
    if (this->currentChar == '\n' || lineBuffer.empty())
    {
        readLine();
    }

    this->currentChar = this->lineBuffer[this->column++];
}

void unreadCharacter()
{
    this->column--;
    this->currentChar = lineBuffer[this->column];
}

void addToLexeme()
{
    this->lexeme += this->currentChar;
}

void clearLexeme()
{
    this->lexeme = "";
}

bool eofReached()
{
    return this->currentChar == -1;
}

void analyze()
{
    readCharacter();
    while (!this->infile.eof())
    {
        switch (this->state)
        {
        case Deffault:
            analyzeStartState();
            break;

        case KeywordState:
            analyzeStringState();
            break;

        case Digit:
            analyzeDigitState();
            break;
        }
    }
}

void analyzeStartState()
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
        this->state = KeywordState;
        return;
    }
    else if (isdigit(this->currentChar))
    {
        this->state = Digit;
        return;
    }
    else if (this->currentChar == '=')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"Igual", EQOp});
            return;
        }
        unreadCharacter();
        setToken({"Igual", Assign});
        return;
    }
    else if (this->currentChar == '+')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '+')
        {
            addToLexeme();
            setToken({"Incremento", Increment});
            return;
        }
        else if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"PlusAssign", AddAssign});
            return;
        }
        unreadCharacter();
        setToken({"Soma", Plus});
        return;
    }
    else if (this->currentChar == '-')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '-')
        {
            addToLexeme();
            setToken({"Decremento", Decrement});
            return;
        }
        else if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"MinusAssign", LessAssign});
            return;
        }
        else if (this->currentChar == '>')
        {
            addToLexeme();
            setToken({"Accessor", Accessor});
            return;
        }
        unreadCharacter();
        setToken({"Substração", Minus});
        return;
    }
    else if (this->currentChar == '*')
    {
        cout << "Pointer" << endl;
        addToLexeme();
        setToken({"Multiplicação", Product});
        return;
    }
    else if (this->currentChar == '/')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"DivisionAssign", DivAssign});
            return;
        }
        unreadCharacter();
        setToken({"Division", Division});
        return;
    }
    else if (this->currentChar == '%')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"ModuleAssign", ModAssign});
            return;
        }
        unreadCharacter();
        addToLexeme();
        setToken({"Modulo", Module});
        return;
    }
    else if (this->currentChar == '[')
    {
        addToLexeme();
        setToken({"Operador", BracketOpen});
        return;
    }
    else if (this->currentChar == ']')
    {
        addToLexeme();
        setToken({"Operador", BracketClose});
        return;
    }
    else if (this->currentChar == '(')
    {
        addToLexeme();
        setToken({"Operador", ParenthesisOpen});
        return;
    }
    else if (this->currentChar == ')')
    {
        addToLexeme();
        setToken({"Operador", ParenthesisClose});
        return;
    }
    else if (this->currentChar == '{')
    {
        addToLexeme();
        setToken({"Operador", BraceOpen});
        return;
    }
    else if (this->currentChar == '}')
    {
        addToLexeme();
        setToken({"Operador", BraceClose});
        return;
    }
    else if (this->currentChar == ',')
    {
        addToLexeme();
        setToken({"Operador", Comma});
        return;
    }
    else if (this->currentChar == ';')
    {
        addToLexeme();
        setToken({"Operador", SemiCollon});
        return;
    }
    else if (this->currentChar == ':')
    {
        addToLexeme();
        setToken({"Operador", Collon});
        return;
    }
    else if (this->currentChar == '~')
    {
        addToLexeme();
        setToken({"Negação", Negate});
        return;
    }
    else if (this->currentChar == '^')
    {
        addToLexeme();
        setToken({"Potência", Power});
        return;
    }
    else if (this->currentChar == '.')
    {
        addToLexeme();
        setToken({"Acessor", Accessor});
        return;
    }
    else if (this->currentChar == '!')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"Diferente", NEOp});
            return;
        }
        unreadCharacter();
        setToken({"Not Lógido", LogicalNot});
        return;
    }
    else if (this->currentChar == '&')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '&')
        {
            addToLexeme();
            setToken({"LogicalAnd", LogicalAnd});
            return;
        }
        unreadCharacter();
        setToken({"And", AndOp});
        return;
    }
    else if (this->currentChar == '|')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '|')
        {
            addToLexeme();
            setToken({"LogicalOr", LogicalOr});
            return;
        }
        unreadCharacter();
        setToken({"Or", OrOp});
        return;
    }

    else if (this->currentChar == '>')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"Maior Igual", GEOp});
            return;
        }
        unreadCharacter();
        setToken({"Maior", Greater});
        return;
    }
    else if (this->currentChar == '<')
    {
        addToLexeme();
        readCharacter();
        if (this->currentChar == '=')
        {
            addToLexeme();
            setToken({"Menor Igual", LEOp});
            return;
        }
        unreadCharacter();
        setToken({"Menor", Less});
        return;
    }
}

void analyzeStringState()
{

    if (isalpha(this->currentChar) || isdigit(this->currentChar) || currentChar == '_')
    {
        addToLexeme();
        readCharacter();
        return;
    }

    unreadCharacter();
    currentToken = getKeyword();
    setToken(currentToken);
    state = Deffault;
    return;
}

void analyzeDigitState()
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
        Constant};
    setToken(currentToken);
    state = Deffault;
}

void analyzeFloatingPointState()
{

    if (isdigit(this->currentChar) > 0)
    {
        readCharacter();
        return;
    }

    else if (this->currentChar == '.')
    {
        state = Error;
        return;
    }

    unreadCharacter();
    currentToken = {
        "FloatingPointConstant",
        Constant};
    setToken(this->currentToken);
    this->state = Deffault;
}

void setToken(Token token, string value = "")
{
    cout << "Token encontrado: " << this->lexeme << endl;
    cout << "Token tipo: " << token.types << endl;
    cout << "Token na linha " << this->line << " coluna " << this->column << endl
         << endl;

    this->results.push_back({this->lexeme,
                       token.types});

    clearLexeme();
    readCharacter();
}

void handleError()
{
    cout << "Erro léxico na linha " << this->line << " coluna " << this->column << endl;
    return;
}

Token getKeyword()
{

    Token foundKeyword = {
        "Identifier",
        Identifier};

    for (const Token &keyword : keywords)
    {
        if (keyword.value == this->lexeme)
        {
            foundKeyword = keyword;
        }
    }

    return foundKeyword;
}