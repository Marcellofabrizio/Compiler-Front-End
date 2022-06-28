project(SyntaticParser)

include_directories(include)

add_executable(SyntaticParser
  main.cpp
  parser.cpp
  src/syntatic.cpp
  include/syntatic.h
)
