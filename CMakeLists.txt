project(SyntaticParser)

include_directories(include)

add_executable(SyntaticParser
  main.cpp
  src/syntatic.cpp
  parser.cpp
  include/syntatic.h
)
