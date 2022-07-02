#include <iostream>
#include <fstream>
#include "./lexic.cpp"
#include "./include/syntatic.h"

using namespace std;

int main(int argc, char const *argv[])
{

    Lexic *parser = new Lexic("./test.c");
    parser->analyze();

    Syntatic *syntatic = new Syntatic(parser->results);
    cout << syntatic->externalDeclaration() << endl;

    return 0;
}
