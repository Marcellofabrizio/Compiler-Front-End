#include <iostream>
#include <fstream>
#include "./include/lexic.h"
#include "./include/syntatic.h"

using namespace std;

int main(int argc, char const *argv[])
{

    Lexic *parser = new Lexic("./test.c");
    parser->analyze();

    Syntatic *syntatic = new Syntatic(parser->results);
    if(syntatic->externalDeclaration() > 0) {
        cout << "Análise sintática realizada com sucesso" << endl;
    } else {
        cout << "Erro durante análise sintática" << endl;
    }

    return 0;
}
