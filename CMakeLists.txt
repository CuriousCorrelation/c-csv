CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_C_STANDARD 99)

project(c-csv)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(c-csv
  src/strtokoc.c
  src/reader.c
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if(C_CSV_TEST)
  include(CTest)
  enable_testing()
  add_subdirectory(c-csv-test)
endif()
