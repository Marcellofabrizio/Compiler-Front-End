#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "./token.hpp"

using namespace std;

typedef enum
{
    Start = 0,
    Digit,
    String
} State;

class Parser
{

public:
    int column = 0;
    int state = Start;
    char currentChar;
    string line;
    string buffer;
    ifstream infile;
    Token currentToken;

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

        if (line.empty() || column >= line.size())
        {
            readLine();
        }

        cout << "Lido char" << endl;

        currentChar = line[column];

        cout << currentChar << endl;

        column++;
    }

    void readLine()
    {
        if (!getline(infile, line))
        {
            column = -1;
            cout << column << endl;
        }
    }

    bool eofReached()
    {
        return column == -1;
    }

    void analyze()
    {
        readCharacter();
        cout << currentChar << endl;

        while (!eofReached())
        {
            buffer += currentChar;
            switch (state)
            {
            case Start:
                analyzeStartState();

            case String:

                analyzeStringState();

            case Digit:

                analyzeDigitState();
            }
        }
    }

    void analyzeStartState()
    {

        if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
        {
            buffer = "";
            cout << "Vazio" << endl;
            readCharacter();
        }

        if (isalpha(currentChar) || currentChar == '_')
        {
            readCharacter();
            state = String;
            cout << currentChar << endl;
            cout << "Token de string" << endl;
        }
        else if (isdigit(currentChar))
        {
            readCharacter();
            state = Digit;
            cout << "Token de digito" << endl;
        }
        else if (currentChar == '=')
        {
            readCharacter();
            if (currentChar == '=')
            {
                setToken({"Igual", Assign});
                cout << "Token de igual" << endl;
            }
        }
        else if (currentChar == '+')
        {
            readCharacter();
            if (currentChar == '+')
            {
                setToken({"Incremento", Increment});
                cout << "incremento" << endl;
            }
            else if (currentChar == '=')
            {
                setToken({"PlusAssign", PlusAssign});
                cout << "mais igual" << endl;
            }
            else
            {
                setToken({"Soma", Plus});
                cout << "soma" << endl;
            }
        }
        else if (currentChar == '*')
        {
            readCharacter();

            if (isalpha(currentChar))
            {
                state = String;
            }

            else
            {
                setToken({"Multiplicação", Product});
            }
        }
        else if (currentChar == '[')
        {
            readCharacter();
            setToken({"Abre colchetes", BracketOpen});
        }
        else if (currentChar == ']')
        {
            readCharacter();
            setToken({"Fecha colchetes", BracketClose});
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
        currentToken = getKeyword();
        state = Start;
    }

    void analyzeDigitState()
    {
        bool isFloat = false;

        while (isdigit(currentChar))
        {
            readCharacter();
            if (isFloat)
            {
                setToken({"Double point float", LexicalError});
            }
        }
    }

    void setToken(Token token)
    {
        currentToken = token;
        registerToken();
    }

    void registerToken()
    {
        cout << currentToken.value << endl;
    }

    Token getKeyword()
    {

        for (const Token &keyword : keywords)
        {
            if (keyword.value == buffer)
            {
                return keyword;
            }
        }
    }
};