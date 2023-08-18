include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(cunit/CUnit)

add_executable(test main_test.c)

target_link_libraries(test cpu mem cunit)