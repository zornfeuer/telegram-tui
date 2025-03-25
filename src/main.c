#include <locale.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>  // Для memset
#include "tui.h"
#include "tdlib.h"

int main() {
    auth_tui(); 
    auth_tui();
    while (1) {
      int ch = getch();
      if (ch == 'q') break;
    }
    return 0;
}
