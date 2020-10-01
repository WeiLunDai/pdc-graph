
include_directories(include)

add_subdirectory(include)
add_subdirectory(src)

add_executable(main_test main_test.cc)

target_link_libraries(main_test
    graphD
    test)
