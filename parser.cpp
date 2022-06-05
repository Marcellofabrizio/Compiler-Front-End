#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "./token.hpp"

using namespace std;

class Parser
{

public:
    int column = 0;
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

        currentChar = line[column];
        column++;
    }

    void readLine()
    {
        if (!getline(infile, line))
        {
            cout << "EOF" << endl;
            column = -1;
        }
    }

    void analyze();
};