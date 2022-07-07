# CMakeList.txt: projeto de CMake para SyntaticParser, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

project ("SyntaticParser")

include_directories(./include/)

add_library(Parser "include/lexic.h" "include/syntatic.h" "include/token.hpp" "src/lexic.cpp" "src/syntatic.cpp")

add_executable (SyntaticParser "SyntaticParser.cpp" "SyntaticParser.h" SyntaticParser.h)

target_link_libraries(SyntaticParser PUBLIC Parser)