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

    Parser(ifstream infile)
    {
        if (infile.bad())
        {
            throw invalid_argument("Error opening file stream");
        }
    }

    void readLine();
    void analyze();
};