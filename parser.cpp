#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "./token.hpp"

#define RED "\033[31m" /* Red */

using namespace std;
/*
Todo:
    - Estado para floats
    - Estado de string vira estado identificador
    - Estado de string somente para strings
    - Estado de comentario (se tiver tempo)
*/
typedef enum
{
    Deffault = 0,
    Digit,
    KeywordState,
    FloatingPoint,
    Error,
} State;

class Parser
{

public:
    int column = 0;
    int line = 0;
    int state = Deffault;
    char currentChar;
    string lineBuffer;
    string lexeme = "";
    ifstream infile;
    Token currentToken;
    Token result;

    // lista de resultados, vai adicionando p depois passar p sintático
    list<Token> results;

    Parser(string filename)
    {
        infile = ifstream(filename);

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
        if (!getline(infile, lineBuffer))
        {
            currentChar = -1;
            return;
        }

        lineBuffer += '\n';
        column = 0;
        line++;
        return;
    }

    void readCharacter()
    {
        if (currentChar == '\n' || lineBuffer.empty())
        {
            readLine();
        }

        currentChar = lineBuffer[column++];
    }

    void unreadCharacter()
    {
        column--;
        currentChar = lineBuffer[column];
    }

    void addToLexeme()
    {
        lexeme += currentChar;
    }

    void clearLexeme()
    {
        lexeme = "";
    }

    bool eofReached()
    {
        return currentChar == -1;
    }

    void analyze()
    {
        readCharacter();
        while (!infile.eof())
        {
            switch (state)
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
        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r')
        {
            clearLexeme();
            readCharacter();
            return;
        }

        else if (isalpha(currentChar) || currentChar == '_')
        {
            addToLexeme();
            readCharacter();
            state = KeywordState;
            return;
        }
        else if (isdigit(currentChar))
        {
            state = Digit;
            return;
        }
        else if (currentChar == '=')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
            {
                addToLexeme();
                setToken({"Igual", EQOp});
                return;
            }
            unreadCharacter();
            setToken({"Igual", Assign});
            return;
        }
        else if (currentChar == '+')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '+')
            {
                addToLexeme();
                setToken({"Incremento", Increment});
                return;
            }
            else if (currentChar == '=')
            {
                addToLexeme();
                setToken({"PlusAssign", AddAssign});
                return;
            }
            unreadCharacter();
            setToken({"Soma", Plus});
            return;
        }
        else if (currentChar == '-')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '-')
            {
                addToLexeme();
                setToken({"Decremento", Decrement});
                return;
            }
            else if (currentChar == '=')
            {
                addToLexeme();
                setToken({"MinusAssign", LessAssign});
                return;
            }
            else if (currentChar == '>')
            {
                addToLexeme();
                setToken({"Accessor", Accessor});
                return;
            }
            unreadCharacter();
            setToken({"Substração", Minus});
            return;
        }
        else if (currentChar == '*')
        {
            cout << "Pointer" << endl;
            addToLexeme();
            setToken({"Multiplicação", Product});
            return;
        }
        else if (currentChar == '/')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
            {
                addToLexeme();
                setToken({"DivisionAssign", DivAssign});
                return;
            }
            unreadCharacter();
            setToken({"Division", Division});
            return;
        }
        else if (currentChar == '%')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
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
        else if (currentChar == '[')
        {
            addToLexeme();
            setToken({"Operador", BracketOpen});
            return;
        }
        else if (currentChar == ']')
        {
            addToLexeme();
            setToken({"Operador", BracketClose});
            return;
        }
        else if (currentChar == '(')
        {
            addToLexeme();
            setToken({"Operador", ParenthesisOpen});
            return;
        }
        else if (currentChar == ')')
        {
            addToLexeme();
            setToken({"Operador", ParenthesisClose});
            return;
        }
        else if (currentChar == '{')
        {
            addToLexeme();
            setToken({"Operador", BraceOpen});
            return;
        }
        else if (currentChar == '}')
        {
            addToLexeme();
            setToken({"Operador", BraceClose});
            return;
        }
        else if (currentChar == ',')
        {
            addToLexeme();
            setToken({"Operador", Comma});
            return;
        }
        else if (currentChar == ';')
        {
            addToLexeme();
            setToken({"Operador", SemiCollon});
            return;
        }
        else if (currentChar == ':')
        {
            addToLexeme();
            setToken({"Operador", Collon});
            return;
        }
        else if (currentChar == '~')
        {
            addToLexeme();
            setToken({"Negação", Negate});
            return;
        }
        else if (currentChar == '^')
        {
            addToLexeme();
            setToken({"Potência", Power});
            return;
        }
        else if (currentChar == '.')
        {
            addToLexeme();
            setToken({"Acessor", Accessor});
            return;
        }
        else if (currentChar == '!')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
            {
                addToLexeme();
                setToken({"Diferente", NEOp});
                return;
            }
            unreadCharacter();
            setToken({"Not Lógido", LogicalNot});
            return;
        }
        else if (currentChar == '&')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '&')
            {
                addToLexeme();
                setToken({"LogicalAnd", LogicalAnd});
                return;
            }
            unreadCharacter();
            setToken({"And", AndOp});
            return;
        }
        else if (currentChar == '|')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '|')
            {
                addToLexeme();
                setToken({"LogicalOr", LogicalOr});
                return;
            }
            unreadCharacter();
            setToken({"Or", OrOp});
            return;
        }

        else if (currentChar == '>')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
            {
                addToLexeme();
                setToken({"Maior Igual", GEOp});
                return;
            }
            unreadCharacter();
            setToken({"Maior", Greater});
            return;
        }
        else if (currentChar == '<')
        {
            addToLexeme();
            readCharacter();
            if (currentChar == '=')
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

        if (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_')
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
        if (isdigit(currentChar) || (currentChar == '.'))
        {
            addToLexeme();
            readCharacter();
            return;
        }

        unreadCharacter();

        currentToken = {
            "Constant",
            Constant};
        setToken(currentToken);
        state = Deffault;
    }

    void analyzeFloatingPointState()
    {

        if (isdigit(currentChar) > 0)
        {
            readCharacter();
            return;
        }

        else if (currentChar == '.')
        {
            state = Error;
            return;
        }

        unreadCharacter();
        currentToken = {
            "FloatingPointConstant",
            Constant};
        setToken(currentToken);
        state = Deffault;
    }

    void setToken(Token token, string value = "")
    {
        cout << "Token encontrado: " << lexeme << endl;
        cout << "Token tipo: " << token.types << endl;
        cout << "Token na linha " << line << " coluna " << column << endl
             << endl;

        clearLexeme();
        readCharacter();
    }

    void handleError()
    {
        cout << "Erro léxico na linha " << line << " coluna " << column << endl;
        return;
    }

    Token getKeyword()
    {

        Token foundKeyword = {
            "Identifier",
            Identifier};

        for (const Token &keyword : keywords)
        {
            if (keyword.value == lexeme)
            {
                foundKeyword = keyword;
            }
        }

        return foundKeyword;
    }

    char peakNextChar()
    {
        readCharacter();
        char nextChar = currentChar;
        unreadCharacter();
        return nextChar;
    }
};