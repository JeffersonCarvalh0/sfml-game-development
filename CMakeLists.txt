cmake_minimum_required(VERSION 3.7.2)
project(game)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g")

# Add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(HEADER_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "include/*.h")

# Main executable
add_executable(main ${SOURCE_FILES})
target_include_directories(main PRIVATE ${HEADER_DIRECTORY} ${SRC_DIRECTORY} ${SFML_INCLUDE_DIR})
target_link_libraries(main ${SFML_LIBRARIES})
