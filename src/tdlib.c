#include "tdlib.h"
#include "tui.h"
#include <td/telegram/td_json_client.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // Для memset
#include <stdio.h>    // Для snprintf
#include <stdlib.h>

// Глобальные переменные
int client_id;
const double WAIT_TIMEOUT = 10.0;
pthread_mutex_t update_mutex = PTHREAD_MUTEX_INITIALIZER;
char update_buffer[1024] = {0};
bool new_update = false;

const char* set_tdlib_parameters = 
  "{"
  "\"@type\":\"setTdlibParameters\","
  "\"database_directory\":\"tdlib\","
  "\"use_message_database\":true,"
  "\"use_secret_chats\":false,"
  "\"api_id\": 25445698,"
  "\"api_hash\":\"d9c8879546d9396821219258ea4dfb9b\","
  "\"system_language_code\":\"en\","
  "\"device_model\":\"Linux\","
  "\"application_version\":\"1.0\","
  "\"enable_storage_optimizer\":true"
  "}";

void handle_update(const char* update) {
  pthread_mutex_lock(&update_mutex);
  if (strstr(update, "authorizationStateWaitTdlibParameters")) {
    td_send(client_id, set_tdlib_parameters);
  }
  if (strstr(update, "authorizationStateWaitPhoneNumber")) {
    wchar_t phone_number[256] = {0};
    int position = ask_tui("Введите номер телефона", phone_number);
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"setAuthenticationPhoneNumber\","
        "\"phone_number\":\"%ls\"}", phone_number);
    td_send(client_id, request);
    endwin();
  }
  if (strstr(update, "authorizationStateWaitCode")) {
    wchar_t code[256] = {0};
    int position = ask_tui("Введите аутенетификационный код", code);
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"checkAuthenticationCode\","
        "\"code\":\"%ls\"}", code);
    td_send(client_id, request);
    endwin();
  }
  if (strstr(update, "authorizationStateWaitPassword")) {
    wchar_t password[256] = {0};
    int position = ask_tui("Введите пароль", password);
    char request[256];
    snprintf(request, sizeof(request),
        "{\"@type\":\"checkAuthenticationPassword\","
        "\"password\":\"%ls\"}", password);
    td_send(client_id, request);
    endwin();
  }
  if (strstr(update, "authorizationStateReady")) {
    td_send(client_id, "{\"@type\": \"loadChats\", \"limit\": 100}");
  }
  if (strstr(update, "authorizationStateWaitEncryptionKey")) {
    td_send(client_id, "{\"@type\": \"setDatabaseEncryptionKey\", \"new_encryption_key_\": \"\"}");
  }
  if (strstr(update, "updateNewChat")) {
    FILE* file = fopen("output.txt", "w");
    fprintf(file, update);
    fclose(file);
  }
  pthread_mutex_unlock(&update_mutex);
}

// Поток для обработки обновлений TDLib
void* tg_update_thread(void* arg) {
  td_execute("{\"@type\":\"setLogVerbosityLevel\", \"new_verbosity_level\":0}"); // Disable logging
  
  client_id = td_create_client_id();

  td_send(client_id, "{'@type': 'getOption', 'name': 'version', '@extra': 1.01234}");
  while (1) {
    const char *result = td_receive(WAIT_TIMEOUT);
    if (result) {
      handle_update(result);
    }
  }
  return NULL;
}
