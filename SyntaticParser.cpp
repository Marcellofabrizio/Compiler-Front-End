#include <iostream>
#include "./include/lexic.h"
#include "./include/syntatic.h"

#include "SyntaticParser.h"

using namespace std;

int main(int argc, char const* argv[])
{

    Lexic* parser = new Lexic("/home/marcello/CLionProjects/SyntaticParser/test.txt");
    parser->analyze();

    Syntatic* syntatic = new Syntatic(parser->results);
    if (syntatic->translationUnit() > 0) {
        cout << "Análise sintática realizada com sucesso" << endl;
    }
    else {
        cout << "Erro durante análise sintática" << endl;
    }

    return 0;
}
