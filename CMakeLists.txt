cmake_minimum_required(VERSION 3.10)
project(telegram_tui)

set(CMAKE_C_STANDARD 11)

# Генерация compile_commands.json для clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Поиск ncurses
find_library(NCURSES_LIBRARY ncurses)
find_path(NCURSES_INCLUDE_DIR ncurses.h)

# Поиск tdlib
include_directories("./td/tdlib/include")
link_directories("./td/tdlib/lib")

if (NCURSES_LIBRARY AND NCURSES_INCLUDE_DIR)
    message(STATUS "Found ncurses: ${NCURSES_LIBRARY}")
    include_directories(${NCURSES_INCLUDE_DIR})
else()
    message(FATAL_ERROR "ncurses not found!")
endif()

# Добавляем папку include в пути поиска заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/include)

# Исполняемый файл
add_executable(${PROJECT_NAME}
    src/main.c
    src/tui.c
    src/tdlib.c
)

# Подключение ncurses
target_link_libraries(${PROJECT_NAME} ${NCURSES_LIBRARY} tdjson)
