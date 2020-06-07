
project(rofi-nerd-fonts)
cmake_minimum_required(VERSION 3.0)

# base path
set(PRJ_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(PRJ_SOURCES       ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# modules
include("${PRJ_CMAKE_MODULES}/glob_sources.cmake")

# packages
find_package(PkgConfig)
pkg_check_modules(ROFI REQUIRED rofi)
include_directories(${ROFI_INCLUDE_DIRS})

# sources
set(SOURCES)
add_headers_only(SOURCES ${PRJ_SOURCES})
add_sources_only(SOURCES ${PRJ_SOURCES})

# target
add_library(rnf SHARED ${SOURCES})
target_link_libraries(rnf stdc++fs) 
install(TARGETS rnf LIBRARY DESTINATION /usr/lib/rofi)
if(NOT EXISTS /usr/lib/nerd-fonts-complete)
        install(DIRECTORY nerd-fonts-complete DESTINATION /usr/lib)
endif(NOT EXISTS /usr/lib/nerd-fonts-complete)
