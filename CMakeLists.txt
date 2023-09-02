cmake_minimum_required(VERSION 3.15)
project(TheBall VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
find_package(box2d CONFIG REQUIRED)

file(GLOB source_files "src/*.cpp" "src/ui/*.cpp" "src/world/*.cpp" "src/entity/*.cpp" "src/animation/*.cpp")

add_executable(TheBall ${source_files})

target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-audio sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE box2d::box2d)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})