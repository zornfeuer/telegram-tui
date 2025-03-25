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

#endif // TDLIB_H
