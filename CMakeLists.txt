cmake_minimum_required(VERSION 3.22)
project(operating_system_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(RESOURCES src/main.c
        src/utils.c
        include/utils.h
        include/ANSI_escapes.h
        src/commands.c
        include/commands.h
        src/aliases.c
        include/aliases.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

add_executable(operating_system_shell ${RESOURCES})
