#include <iostream>
#include "./include/lexic.h"
#include "./include/syntactic.h"

#include "SyntacticParser.h"

using namespace std;

int main(int argc, char const* argv[])
{
    if (argc < 2) {
        cout << "Arquivo de entrada não encontrado" << endl;
        cout << "Forneça o caminho para um arquivo de entrada" << endl;
        return 0;
    }

    string inFilePath = argv[1];

    Lexic* parser = new Lexic(inFilePath);
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
