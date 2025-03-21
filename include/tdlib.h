#ifndef TDLIB_H
#define TDLIB_H

#include <td/telegram/td_json_client.h>
#include <pthread.h>
#include <stdbool.h>

// Глобальные переменные
extern void* client;
extern pthread_mutex_t update_mutex;
extern char update_buffer[1024];
extern bool new_update;

// Функции
void* tg_update_thread(void* arg);
void td_send_request(const char* request);
void send_phone_number(const char* phone_number);
void send_code(const char* code);
void send_password(const char* password);  // Добавлена новая функция

#endif // TDLIB_H
