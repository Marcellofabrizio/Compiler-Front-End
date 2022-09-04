# CMakeList.txt: projeto de CMake para SyntacticParser, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("SyntacticParser")

include_directories(./include/)

add_library(Parser "include/lexic.h" "include/syntactic.h" "include/token.hpp" "src/lexic.cpp" "src/syntactic.cpp" include/syntactic2.h src/syntactic2.cpp)

add_executable (SyntacticParser "SyntacticParser.cpp" "SyntacticParser.h" SyntacticParser.h)

target_link_libraries(SyntacticParser PUBLIC Parser)