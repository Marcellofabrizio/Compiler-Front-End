#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
    Start = 0,
    Digit,
    String,
    FloatingPoint,
    Error,
} State;

class Parser
{

public:
    int column = 0;
    int line = 0;
    int state = Start;
    char currentChar;
    string lineBuffer;
    string buffer = "";
    ifstream infile;
    Token currentToken;
    Token result;

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

    void readCharacter()
    {

        if (lineBuffer.empty() || column >= lineBuffer.size())
        {
            readLine();
        }

        currentChar = lineBuffer[column];
        buffer += currentChar;
        column++;
    }

    void unreadCharacter()
    {
        column--;
        currentChar = lineBuffer[column];
        buffer.pop_back();
    }

    void readLine()
    {
        if (!getline(infile, lineBuffer))
        {
            column = -1;
            return;
        }
        else if (lineBuffer.length() == 0)
        {
            readLine();
        }
        else
        {
            column = 0;
            line++;
            return;
        }
    }

    bool eofReached()
    {
        return column == -1;
    }

    void analyze()
    {
        readCharacter();
        while (!infile.eof())
        {
            switch (state)
            {
            case Start:
                analyzeStartState();
                readCharacter();
                break;

            case String:
                analyzeStringState();
                readCharacter();
                break;

            case Digit:
                analyzeDigitState();
                readCharacter();
                break;

            case Error:
                handleError();
                return;
            }
        }
    }

    void analyzeStartState()
    {
        char nextChar = peakNextChar();
        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
        {
            cleanBuffer();
            readCharacter();
            return;
        }

        if (isalpha(currentChar) || currentChar == '_')
        {
            readCharacter();
            state = String;
            cout << "State change to string" << endl;
            return;
        }
        else if (isdigit(currentChar))
        {
            state = Digit;
            cout << "State change to digit" << endl;
            cout << currentChar << endl;
            return;
        }
        else if (currentChar == '=')
        {
            readCharacter();
            if (currentChar == '=')
            {
                setToken({"Igual", Equals});
                return;
            }
            unreadCharacter();
            setToken({"Igual", Assign});
            return;
        }
        else if (currentChar == '+')
        {
            readCharacter();
            if (currentChar == '+')
            {
                setToken({"Incremento", Increment});
                return;
            }
            else if (currentChar == '=')
            {
                setToken({"PlusAssign", PlusAssign});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"Soma", Plus});
                return;
            }
        }
        else if (currentChar == '-')
        {
            readCharacter();
            if (currentChar == '-')
            {
                setToken({"Decremento", Decrement});
                return;
            }
            else if (currentChar == '=')
            {
                setToken({"MinusAssign", MinusAssign});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"Substração", Minus});
                return;
            }
        }
        else if (currentChar == '*')
        {
            if (isalpha(peakNextChar()))
            {
                setToken({"Pointer", Pointer});
                return;
            }

            else
            {
                setToken({"Multiplicação", Product});
                return;
            }
        }
        else if (currentChar == '/')
        {
            readCharacter();
            if (currentChar == '=')
            {
                setToken({"DivisionAssign", DivisionAssign});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"Division", Division});
                return;
            }
        }
        else if (currentChar == '%')
        {
            readCharacter();
            if (currentChar == '=')
            {
                setToken({"ModuleAssign", ModuleAssign});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"Modulo", Module});
                return;
            }
        }
        else if (currentChar == '[')
        {
            setToken({"Operador", BracketOpen});
            return;
        }
        else if (currentChar == ']')
        {
            setToken({"Operador", BracketClose});
            return;
        }
        else if (currentChar == '(')
        {
            setToken({"Operador", ParenthesisOpen});
            return;
        }
        else if (currentChar == ')')
        {
            setToken({"Operador", ParenthesisClose});
            return;
        }
        else if (currentChar == '{')
        {
            setToken({"Operador", ParenthesisOpen});
            return;
        }
        else if (currentChar == '}')
        {
            setToken({"Operador", ParenthesisClose});
            return;
        }
        else if (currentChar == ',')
        {
            setToken({"Operador", Comma});
            return;
        }
        // else if (currentChar == '.')
        // {
        //     setToken({"Operador", Dot});
        //     return;
        // }
        else if (currentChar == ':')
        {
            setToken({"Operador", Collon});
            return;
        }
        else if (currentChar == '&')
        {
            readCharacter();
            if (currentChar == '&')
            {
                setToken({"LogicalAnd", LogicalAnd});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"And", And});
            }
        }
        else if (currentChar == '|')
        {
            readCharacter();
            if (currentChar == '|')
            {
                setToken({"LogicalOr", LogicalOr});
                return;
            }
            else
            {
                unreadCharacter();
                setToken({"Or", Or});
            }
        }
    }

    void analyzeStringState()
    {
        if (isalpha(currentChar) || currentChar == '_' || isdigit(currentChar))
        {
            return;
        }

        unreadCharacter();
        currentToken = getKeyword();
        setToken(currentToken);
        state = Start;
        cout << "State change to start" << endl;
        cout << buffer << endl;
        cout << currentChar << endl;
        return;
    }

    void analyzeDigitState()
    {

        if (isdigit(currentChar))
        {
            readCharacter();
            return;
        }

        else if (currentChar == '.')
        {
            readCharacter();
            state = FloatingPoint;
            cout << "State change to floating point" << endl;
            return;
        }

        else if (isalpha(peakNextChar()))
        {
            state = Error;
            return;
        }

        unreadCharacter();
        currentToken = {
            "IntegerConstant",
            IntegerConstant};
        setToken(currentToken);
        state = Start;
        cout << "State change to start" << endl;
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
            FloatingPointConstant};
        setToken(currentToken);
        state = Start;
        cout << "State change to start" << endl;
    }

    void setToken(Token token, string value = "")
    {
        result = {
            buffer,
            token.types};
        registerToken();
        cleanBuffer();
    }

    void registerToken()
    {
        cout << "Token encontraddo: " << buffer << endl;
        cout << "Token tipo: " << result.types << endl;
        cout << "Token na linha " << line << " coluna " << column << endl;
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
            if (keyword.value == buffer)
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

    void cleanBuffer()
    {
        cout << "Buffer antes de limpar : " << buffer << endl;
        buffer = "";
        cout << "Buffer depois de limpar : " << buffer << endl;
    }
};