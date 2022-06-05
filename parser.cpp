#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "./token.hpp"

using namespace std;

class Parser
{

public:
    string line;
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

    void readLine()
    {
        if (!getline(infile, line))
        {
            cout << "Error reading line" << endl;
        }
    }

    void analyze();
};