cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CXX_STANDARD_REQUIRED 11)

project(ProgettoIntermedio)

add_library(Book Book.cpp)
add_library(ISBN ISBN.cpp)
add_library(Date Date.cpp)

add_executable(${PROJECT_NAME}
    Main.cpp
    Book.cpp
    ISBN.cpp
    Date.cpp
)

target_link_libraries(${PROJECT_NAME}
    Book ISBN Date
)