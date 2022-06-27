#include <iostream>
#include <fstream>
#include "./parser.cpp"
#include "./syntatic.cpp"

using namespace std;

int main(int argc, char const *argv[])
{

    Parser *parser = new Parser("./test.c");
    parser->analyze();

    Syntatic *syntatic = new Syntatic(parser->results);
    cout << syntatic->externalDeclaration() << endl;

    return 0;
}
