cmake_minimum_required(VERSION 3.22)

project(av23tr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

if (CMAKE_HOST_SYSTEM MATCHES Linux)
   if (NOT EXISTS "$ENV{HOME}/.local/share/fonts/MaterialIcons.ttf")
      file(COPY "desktop/client/res/MaterialIcons.ttf" DESTINATION "$ENV{HOME}/.local/share/fonts/")
      execute_process(COMMAND fc-cache -f -v ~/.local/share/fonts) 
   endif()
endif()

add_executable(client desktop/client/main.cpp desktop/client/src/canvas.cpp desktop/client/src/comservice.cpp desktop/client/src/tcpservice.cpp desktop/client/src/window.cpp)

target_include_directories(client PUBLIC desktop/client/include)
target_link_libraries(client PUBLIC Qt6::Core Qt6::Widgets)

add_executable(server desktop/server/main.cpp desktop/server/src/comservice.cpp desktop/server/src/tcpservice.cpp desktop/server/src/window.cpp)
target_include_directories(server PUBLIC desktop/server/include)
target_link_libraries(server PUBLIC Qt6::Core Qt6::Widgets)

INCLUDE_DIRECTORIES(shared)

if(CAN=ON)
   add_custom_target(esp32_client_upload ALL
   COMMAND gnome-terminal -- bash -c "pio run -t upload -e esp32-evb --upload-port /dev/ttyUSB0"
   COMMAND gnome-terminal -- bash -c "pio device monitor --port /dev/ttyUSB0"
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/esp32/client
   )

   add_custom_target(esp32_server_upload ALL
   COMMAND gnome-terminal -- bash -c "pio run -t upload -e esp32-evb --upload-port /dev/ttyUSB1"
   COMMAND gnome-terminal -- bash -c "pio device monitor --port /dev/ttyUSB1"
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/esp32/server
   )
endif()