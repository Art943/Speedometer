cmake_minimum_required(VERSION 3.22)

project(av23tr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

if(CMAKE_HOST_SYSTEM MATCHES Linux)
   execute_process(COMMAND if [ ! -f ~/local/share/fonts/Materialicons.ttf ]; then if [ ! -d ~/local/share/fonts/ ]; then mkdir -p ~/local/share/fonts/; fi; then cp ./desktop/client/res/font.ttf ~/local/share/fonts/Materialicons.ttf; fi)
endif()

add_executable(client desktop/client/main.cpp)
add_executable(server desktop/server/main.cpp)
target_link_libraries(client PUBLIC Qt6::Core Qt6::Widgets)
target_link_libraries(server PUBLIC Qt6::Core Qt6::Widgets)
INCLUDE_DIRECTORIES(desktop/client/include)
INCLUDE_DIRECTORIES(desktop/server/include)
INCLUDE_DIRECTORIES(shared)