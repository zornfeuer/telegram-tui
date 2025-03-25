#define _XOPEN_SOURCE_EXTENDED  // Важно!
#define NCURSES_WIDECHAR 1      // Активация wide-режима

#include "tui.h"
#include <wctype.h>
#include <ncurses.h>

WINDOW* ask_win;

int ask_tui(const char *output, wchar_t *buffer) {
  ask_win = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);

  box(ask_win, 0, 0);
  wattron(ask_win, A_BOLD);
  mvwprintw(ask_win, 5, 7, output);
  wattroff(ask_win, A_BOLD);
  mvwprintw(ask_win, 8, 7, "Ввод: ");
  
  wrefresh(ask_win);
  refresh();
 
  int input_pos = 0;

  while (1) {
    wint_t wch;
    int status = get_wch(&wch);
    if (wch == L'\n') {
      buffer[input_pos] = L'\0';
      return input_pos;
    } else if (wch == 127) {
      if (input_pos) {
        buffer[input_pos] = L'\0';
        mvwprintw(ask_win, 8, 12 + input_pos, " ");
        input_pos--;
      }
    } else {
      buffer[input_pos++] = wch;
      mvwprintw(ask_win, 8, 13, "%ls", buffer);
    }
    wrefresh(ask_win);
    refresh();
  }
}
