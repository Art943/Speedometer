cmake_minimum_required(VERSION 3.22)

project(av23tr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)


find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia SerialPort)

if (CMAKE_HOST_SYSTEM MATCHES Linux)
   if (NOT EXISTS "$ENV{HOME}/.local/share/fonts/MaterialIcons.ttf")
      file(COPY "desktop/client/res/MaterialIcons.ttf" DESTINATION "$ENV{HOME}/.local/share/fonts/")
      execute_process(COMMAND fc-cache -f -v ~/.local/share/fonts) 
   endif()
endif()

set(COMM_PROTOCOL "TCP" CACHE STRING "Communication protocol to use (TCP or CAN)")

# CAN Communication
if(COMM_PROTOCOL STREQUAL "CAN")
    set(SERVER_SRC desktop/server/src/canservice.cpp)
    set(CLIENT_SRC desktop/client/src/canservice.cpp)
    set(SERVER_LIBS Qt6::SerialPort)
    set(CLIENT_LIBS Qt6::SerialPort)
    add_compile_definitions(COMM_CAN)

    # Custom targets for uploading to microcontrollers
    add_custom_target(upload_client
        COMMAND gnome-terminal -- sh -c "pio run --target upload --upload-port /dev/ttyUSB0"
        COMMENT "Uploading client to node1 (/dev/ttyUSB0)"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/esp32/client
    )

    add_custom_target(upload_server
        COMMAND gnome-terminal -- sh -c "pio run --target upload --upload-port /dev/ttyUSB1"
        COMMENT "Uploading server to node2 (/dev/ttyUSB1)"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/esp32/server
    )

# TCP Communication
else()
    set(SERVER_SRC desktop/server/src/tcpservice.cpp)
    set(CLIENT_SRC desktop/client/src/tcpservice.cpp)
    set(SERVER_LIBS "")
    set(CLIENT_LIBS "")
    add_compile_definitions(COMM_TCP)
endif()

# Server
add_executable(server 
    desktop/server/main.cpp 
    desktop/server/src/window.cpp 
    desktop/server/src/comservice.cpp
    ${SERVER_SRC})

target_include_directories(server PUBLIC 
    ${CMAKE_SOURCE_DIR}/desktop/server/include 
    ${CMAKE_SOURCE_DIR}/shared)

target_link_libraries(server PUBLIC Qt6::Core Qt6::Widgets Qt6::Multimedia ${SERVER_LIBS})

# Client
add_executable(client 
    desktop/client/main.cpp 
    desktop/client/src/canvas.cpp 
    desktop/client/src/window.cpp 
    desktop/client/src/comservice.cpp
    ${CLIENT_SRC})

target_include_directories(client PUBLIC 
    ${CMAKE_SOURCE_DIR}/desktop/client/include 
    ${CMAKE_SOURCE_DIR}/shared)

target_link_libraries(client PUBLIC Qt6::Core Qt6::Widgets Qt6::Multimedia ${CLIENT_LIBS})

# Custom targets
add_custom_target(using_tcp
    COMMAND ${CMAKE_COMMAND} -D COMM_PROTOCOL=TCP ..
    COMMAND ${CMAKE_COMMAND} --build .
    COMMENT "Setting protocol to TCP and building"
)

add_custom_target(using_can
    COMMAND ${CMAKE_COMMAND} -D COMM_PROTOCOL=CAN ..
    COMMAND ${CMAKE_COMMAND} --build .
    COMMENT "Setting protocol to CAN and building"
)
