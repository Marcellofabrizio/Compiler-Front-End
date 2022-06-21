#include <iostream>
#include <fstream>
#include "./parser.cpp"

using namespace std;

int main(int argc, char const *argv[])
{

    Parser *parser = new Parser("./test.c");
    parser->analyze();

    for (auto const &v : parser->results)
        cout << v.value << " " << v.types << "\n";

    return 0;
}
