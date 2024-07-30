cmake_minimum_required(VERSION 3.14)

project(geo-construction-prover LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prover.exe main.cpp)

include(GNUInstallDirs)
install(TARGETS prover.exe
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
