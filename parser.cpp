#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "./token.hpp"

#define RED "\033[31m"      /* Red */

using namespace std;

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
        lineBuffer.pop_back();
    }

    void readLine()
    {
        cout << "Lê linha" << endl;
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
            cout << lineBuffer.length() << endl;
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
        while (!eofReached())
        {
            switch (state)
            {
            case Start:
                analyzeStartState();
                break;

            case String:
                analyzeStringState();
                break;

            case Digit:
                analyzeDigitState();
                break;
            
            case Error:
                handleError();
                return;
            }
        }
    }

    void analyzeStartState()
    {

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
            readCharacter();
            state = Digit;
            cout << "State change to digit" << endl;
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
            readCharacter();
            if (isalpha(currentChar))
            {
                state = String;
                return;
            }

            else
            {
                unreadCharacter();
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
        else if (currentChar == '.')
        {
            setToken({"Operador", Dot});
            return;
        }
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
            readCharacter();
            return;
        }

        buffer.pop_back();

        cout << buffer << endl;

        if (buffer[0] == '*')
        {
            cout << "Pointer" << endl;
            currentToken = {
                "Pointer",
                Pointer};
            cout << buffer << endl;
        }
        else
        {
            currentToken = getKeyword();
        }

        setToken(currentToken);
        state = Start;
        cout << "State change to start" << endl;
    }

    void handleError() 
    {
        cout << "Erro léxico na linha " << line << " coluna " << column << endl;
        return; 
    }

    void analyzeDigitState()
    {

        if(isdigit(currentChar))
        {
            readCharacter();
            return;
        }

        else if(currentChar == '.')
        {
            readCharacter();
            state = FloatingPoint;
            return;
        }

        else if(isalpha(peakNextChar()))
        {
            state = Error;
            return;
        }

        state = Start;
        return;
    }

    void setToken(Token token)
    {
        result = {
            buffer,
            token.types};
        registerToken();
        cleanBuffer();
        readCharacter();
    }

    void registerToken()
    {
        cout << "Token encontraddo: " << buffer << endl;
        cout << "Token tipo: " << result.types << endl;
        cout << "Token na linha " << line << " coluna " << column << endl;
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
        buffer = "";
    }
};