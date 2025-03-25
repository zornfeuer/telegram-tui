#ifndef TUI_H
#define TUI_H

#include <wchar.h>
#include <ncurses.h>

// Окна
extern WINDOW* chat_win;
extern WINDOW* msg_win;
extern WINDOW* input_win;
extern WINDOW* auth_win;

// Функции
int ask_tui(const char *output, wchar_t *buffer);

#endif // TUI_H
