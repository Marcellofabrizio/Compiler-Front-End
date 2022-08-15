#include <iostream>
#include "./include/lexic.h"
#include "./include/syntactic.h"
#include "./include/logger.h"
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

    Lexic* lexic = new Lexic(inFilePath);
    lexic->analyze();

    Logger logger;
    Semantic *semantic = new Semantic(logger);
    Syntactic *syntactic = new Syntactic(lexic->results, semantic);
    if (syntactic->translationUnit() > 0) {
        logger.log("Análise sintática realizada com sucesso");
        semantic->checkOverridingDeclarations();
    }
    else {
        logger.error("Erro durante análise sintática");
    }

    return 0;
}
