#include <locale.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // Для memset
#include "tui.h"
#include "tdlib.h"

int main() {
    // Устанавливаем локаль
    setlocale(LC_ALL, "");

    // Инициализация интерфейса
    init_tui();

    // Запуск потока для TDLib
    pthread_t tid;
    pthread_create(&tid, NULL, tg_update_thread, NULL);

    // Главный цикл
    char input[256] = {0};  // Буфер для ввода
    int input_pos = 0;      // Позиция ввода
    bool is_phone_number_entered = false;  // Флаг для ввода номера телефона
    bool is_code_entered = false;          // Флаг для ввода кода подтверждения
    bool is_password_entered = false;      // Флаг для ввода пароля
    while (1) {
        int ch = getch();
        if (ch == 'q') break;

        // Обработка ввода в строке ввода
        if (ch == '\n') {
            if (!is_phone_number_entered) {
                // Отправка номера телефона
                send_phone_number(input);
                is_phone_number_entered = true;
            } else if (!is_code_entered) {
                // Отправка кода подтверждения
                send_code(input);
                is_code_entered = true;
            } else if (!is_password_entered) {
                // Отправка пароля
                send_password(input);
                is_password_entered = true;
            }

            // Очистка строки ввода
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "Ввод: ");
            wrefresh(input_win);
            input_pos = 0;
            memset(input, 0, sizeof(input));
        } else if (ch == 127 || ch == KEY_BACKSPACE) {  // Backspace
            if (input_pos > 0) {
                input_pos--;
                input[input_pos] = '\0';
                mvwprintw(input_win, 1, 7 + input_pos, " ");
                wrefresh(input_win);
            }
        } else if (input_pos < sizeof(input) - 1) {
            // Добавление символа в буфер
            input[input_pos++] = ch;
            input[input_pos] = '\0';

            // Отображение введенного текста
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "Ввод: ");
            mvwprintw(input_win, 1, 7, input);
            wrefresh(input_win);
        }

        // Проверка новых обновлений
        pthread_mutex_lock(&update_mutex);
        if (new_update) {
            // Обновление окна сообщений
            update_message_list(update_buffer);

            // Сброс флага
            new_update = false;
        }
        pthread_mutex_unlock(&update_mutex);

        // Обновление окон
        wrefresh(chat_win);
        wrefresh(msg_win);
        wrefresh(input_win);
    }

    // Завершение работы
    cleanup_tui();
    return 0;
}
