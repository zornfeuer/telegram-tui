#ifndef TUI_H
#define TUI_H

#include <ncurses.h>

// Окна
extern WINDOW* chat_win;
extern WINDOW* msg_win;
extern WINDOW* input_win;
extern WINDOW* auth_win;

// Функции
void auth_tui();
void init_tui();
void cleanup_tui();
void update_chat_list(const char* chats);
void update_message_list(const char* messages);

#endif // TUI_H
