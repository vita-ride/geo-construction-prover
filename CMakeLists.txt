cmake_minimum_required(VERSION 3.14)

project(geo-construction-prover LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

add_executable(prover.exe main.cpp
    formula.h formula.cpp
    common.h common.cpp
    theory.h theory.cpp
)

include(GNUInstallDirs)
install(TARGETS prover.exe
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
