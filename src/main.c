#define _XOPEN_SOURCE_EXTENDED  // Важно!
#define NCURSES_WIDECHAR 1      // Активация wide-режима

#include <locale.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // Для memset
#include "tdlib.h"

int main() {
  setlocale(LC_ALL, "");
  keypad(stdscr, TRUE);

  initscr();
  //start_color();
  cbreak();
  noecho();
  refresh();
  pthread_t tid;
  pthread_create(&tid, NULL, tg_update_thread, NULL);
  while (1) {}
  return 0;
}
