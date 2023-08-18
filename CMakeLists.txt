cmake_minimum_required(VERSION 3.15)
project(6502)

set(DIRETORIES 
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/CPU
  ${CMAKE_SOURCE_DIR}/src/MEM
)

set(LIBRARY_PATH 
${CMAKE_SOURCE_DIR}/src/CPU/CPU.c
${CMAKE_SOURCE_DIR}/src/MEM/MEM.c
)

include_directories(${DIRETORIES})

list(GET LIBRARY_PATH 1 MEM_SOURCE)
add_library(mem STATIC ${MEM_SOURCE})

list(GET LIBRARY_PATH 0 CPU_SOURCE)
add_library(cpu STATIC ${CPU_SOURCE})

set ( MAIN_FILES
  "${CMAKE_SOURCE_DIR}/main.c"
  "${CMAKE_SOURCE_DIR}/tests/main_test.c"
)

list(GET MAIN_FILES 0 MAIN)
list(GET MAIN_FILES 1 MAIN_TEST)
add_executable(${PROJECT_NAME} ${MAIN})
target_link_libraries(${PROJECT_NAME} cpu mem)

add_subdirectory(tests)