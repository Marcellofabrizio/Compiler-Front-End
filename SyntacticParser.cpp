#include <iostream>
#include "./include/lexic.h"
#include "./include/syntactic.h"

#include "SyntacticParser.h"

using namespace std;

int main(int argc, char const* argv[])
{

    Lexic* parser = new Lexic("/home/marcello/CLionProjects/SyntacticParser/test.txt");
    parser->analyze();

    Syntactic* syntactic = new Syntactic(parser->results);
    if (syntactic->translationUnit() > 0) {
        cout << "Análise sintática realizada com sucesso" << endl;
    }
    else {
        cout << "Erro durante análise sintática" << endl;
    }

    return 0;
}
