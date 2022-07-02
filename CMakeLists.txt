project(SyntaticParser)

include_directories(include)

add_executable(SyntaticParser
  main.cpp
  src/syntatic.cpp
  lexic.cpp
  include/syntatic.h
)
