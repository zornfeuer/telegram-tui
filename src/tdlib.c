#include "tdlib.h"
#include <td/telegram/td_json_client.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // Для memset
#include <stdio.h>    // Для snprintf

// Глобальные переменные
void* client = NULL;
pthread_mutex_t update_mutex = PTHREAD_MUTEX_INITIALIZER;
char update_buffer[1024] = {0};
bool new_update = false;

// Функция для обработки обновлений
void handle_update(const char* update) {
    if (strstr(update, "authorizationStateWaitPhoneNumber")) {
        pthread_mutex_lock(&update_mutex);
        snprintf(update_buffer, sizeof(update_buffer), "Введите номер телефона: ");
        new_update = true;
        pthread_mutex_unlock(&update_mutex);
    } else if (strstr(update, "authorizationStateWaitCode")) {
        pthread_mutex_lock(&update_mutex);
        snprintf(update_buffer, sizeof(update_buffer), "Введите код подтверждения: ");
        new_update = true;
        pthread_mutex_unlock(&update_mutex);
    } else if (strstr(update, "authorizationStateWaitPassword")) {
        pthread_mutex_lock(&update_mutex);
        snprintf(update_buffer, sizeof(update_buffer), "Введите пароль: ");
        new_update = true;
        pthread_mutex_unlock(&update_mutex);
    } else if (strstr(update, "authorizationStateReady")) {
        pthread_mutex_lock(&update_mutex);
        snprintf(update_buffer, sizeof(update_buffer), "Аутентификация завершена!");
        new_update = true;
        pthread_mutex_unlock(&update_mutex);
    } else if (strstr(update, "updateNewMessage")) {
        pthread_mutex_lock(&update_mutex);
        snprintf(update_buffer, sizeof(update_buffer), "New message: %s\n", update);
        new_update = true;
        pthread_mutex_unlock(&update_mutex);
    }
}

// Поток для обработки обновлений TDLib
void* tg_update_thread(void* arg) {
    // Отключаем логирование в терминал
    const char* disable_logs_request = 
        "{\"@type\":\"setLogVerbosityLevel\",\"new_verbosity_level\":0}";
    client = td_json_client_create();
    td_json_client_send(client, disable_logs_request);

    // Настройка параметров TDLib
    const char* set_tdlib_parameters = 
        "{"
        "\"@type\":\"setTdlibParameters\","
        "\"parameters\":{"
            "\"database_directory\":\"tdlib\","
            "\"use_message_database\":false,"  // Отключаем базу данных сообщений
            "\"use_secret_chats\":false,"     // Отключаем секретные чаты
            "\"api_id\": 25445698,"         // Замените на ваш API ID
            "\"api_hash\":\"d9c8879546d9396821219258ea4dfb9b\"," // Замените на ваш API Hash
            "\"system_language_code\":\"en\","
            "\"device_model\":\"Console\","
            "\"application_version\":\"1.0\","
            "\"enable_storage_optimizer\":true"
        "}"
        "}";
    td_send_request(set_tdlib_parameters);

    while (1) {
        const char* update = td_json_client_receive(client, 1);
        if (update) {
            // Обработка обновлений
            handle_update(update);
        }
        usleep(100000);  // Спим 100 мс
    }
    return NULL;
}

// Отправка запроса в TDLib
void td_send_request(const char* request) {
    if (client) {
        td_json_client_send(client, request);
    }
}

// Отправка номера телефона
void send_phone_number(const char* phone_number) {
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"setAuthenticationPhoneNumber\","
        "\"phone_number\":\"%s\"}", phone_number);
    td_send_request(request);
}

// Отправка кода подтверждения
void send_code(const char* code) {
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"%s\"}", code);
    td_send_request(request);
}

// Отправка пароля
void send_password(const char* password) {
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"checkAuthenticationPassword\","
        "\"password\":\"%s\"}", password);
    td_send_request(request);
}
