cmake_minimum_required(VERSION 3.10)
project(telegram_tui)

set(CMAKE_C_STANDARD 11)

# for clangd support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ncurses
find_library(NCURSES_LIBRARY ncurses)
find_path(NCURSES_INCLUDE_DIR ncurses.h)

# tdlib
include_directories("./td/tdlib/include")
link_directories("./td/tdlib/lib")

# cJSON
include_directories("./cJSON/include")

if (NCURSES_LIBRARY AND NCURSES_INCLUDE_DIR)
    message(STATUS "Found ncurses: ${NCURSES_LIBRARY}")
    include_directories(${NCURSES_INCLUDE_DIR})
else()
    message(FATAL_ERROR "ncurses not found!")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME}
    src/main.c
    src/tui.c
    src/tdlib.c
)

target_link_libraries(${PROJECT_NAME} ${NCURSES_LIBRARY} tdjson)
