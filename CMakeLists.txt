project(SyntaticParser)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(SyntaticParser
  main.cpp
  src/syntatic.cpp
  src/lexic.cpp
  include/lexic.h
  include/syntatic.h
)
