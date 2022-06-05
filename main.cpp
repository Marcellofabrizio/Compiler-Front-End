#include <iostream>
#include <fstream>
#include "./parser.cpp"

using namespace std;

int main(int argc, char const *argv[])
{

    Parser *parser = new Parser("./test.c");
    parser->readLine();

    return 0;
}
