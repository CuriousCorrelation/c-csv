CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_C_STANDARD 99)

project(c-csv)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(c-csv-lib
  src/reader.c
)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(c-csv-lib
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
  )

target_link_libraries(
  ${PROJECT_NAME}
  c-csv-lib
  )
