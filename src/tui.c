#include "tui.h"
#include <locale.h>
#include <ncurses.h>
#include <string.h>  // Для memset

// Окна
WINDOW* chat_win;
WINDOW* msg_win;
WINDOW* input_win;

void init_tui() {
    // Устанавливаем локаль
    setlocale(LC_ALL, "");

    // Инициализация ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Создание окон
    chat_win = newwin(LINES - 2, COLS / 3, 0, 0);       // Окно чатов
    msg_win = newwin(LINES - 2, 2 * COLS / 3, 0, COLS / 3);  // Окно сообщений
    input_win = newwin(2, COLS, LINES - 2, 0);          // Строка ввода

    // Рамки вокруг окон
    box(chat_win, 0, 0);
    box(msg_win, 0, 0);
    box(input_win, 0, 0);

    // Заголовки окон
    mvwprintw(chat_win, 1, 1, "Чаты");
    mvwprintw(msg_win, 1, 1, "Сообщения");
    mvwprintw(input_win, 1, 1, "Ввод: ");

    // Обновление окон
    wrefresh(chat_win);
    wrefresh(msg_win);
    wrefresh(input_win);

    // Обновление основного экрана
    refresh();

    // Отладочное сообщение
    printw("Окна инициализированы\n");
    refresh();
}

// Завершение работы
void cleanup_tui() {
    delwin(chat_win);
    delwin(msg_win);
    delwin(input_win);
    endwin();
}

// Обновление списка чатов
void update_chat_list(const char* chats) {
    // Очистка окна чатов
    werase(chat_win);
    box(chat_win, 0, 0);
    mvwprintw(chat_win, 1, 1, "Чаты");

    // Пример списка чатов
    mvwprintw(chat_win, 2, 1, "1. Чат 1");
    mvwprintw(chat_win, 3, 1, "2. Чат 2");
    mvwprintw(chat_win, 4, 1, "3. Чат 3");

    // Обновление окна
    wrefresh(chat_win);
}

void update_message_list(const char* messages) {
    // Очистка окна сообщений
    werase(msg_win);
    box(msg_win, 0, 0);
    mvwprintw(msg_win, 1, 1, "Сообщения");

    // Вывод сообщений
    mvwprintw(msg_win, 2, 1, "%s", messages);
    wrefresh(msg_win);
}
