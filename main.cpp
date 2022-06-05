#include <iostream>
#include <fstream>
#include "./parser.cpp"

using namespace std;

int main(int argc, char const *argv[])
{

    Parser *parser = new Parser("./test.c");
    
    parser->readCharacter();
    cout << parser->currentChar << endl;

    return 0;
}
