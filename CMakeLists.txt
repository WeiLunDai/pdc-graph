
cmake_minimum_required(VERSION 2.6)

project("c++ graph display by gtkmm" CXX)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GVC libgvc)
pkg_check_modules(GTEST gtest)

include_directories(
    include
    test/include
    ${GTKMM_INCLUDE_DIRS}
    ${GVC_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(main hello_main.cc)

target_link_libraries(main 
    graphD)
