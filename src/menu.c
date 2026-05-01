#include <raylib.h>

#include "config.h"
#include "menu.h"

#define MENU_ITEMS 3

void Menu_Init(Menu *m) {
  m->selected = 0;
  m->action = (MenuAction)ACTION_NONE;
}

void Menu_Update(Menu *m) {
  if (IsKeyPressed(KEY_DOWN)) {
    m->selected = (m->selected + 1) % MENU_ITEMS;
  }

  if (IsKeyPressed(KEY_UP)) {
    m->selected = (m->selected - 1 + MENU_ITEMS) % MENU_ITEMS;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    switch (m->selected) {
    case 0:
      m->action = ACTION_PLAY;
      break;
    case 1:
      m->action = ACTION_SETTINGS;
      break;
    case 2:
      m->action = ACTION_EXIT;
      break;
    }
  }
}

MenuAction Menu_GetAction(Menu *m) {
  MenuAction result = m->action;
  m->action = ACTION_NONE;
  return result;
}

void Menu_Draw(Menu *m) {
  const char *items[MENU_ITEMS] = {"Play", "Settings", "Exit"};

  float initial_y = SCREEN_HEIGHT * 0.4f;
  float font_size = 32.0f;

  for (int i = 0; i < MENU_ITEMS; i++) {
    float text_width = (float)MeasureText(items[i], (int)font_size);

    float padding = font_size * 0.5f;

    float rect_width = text_width + (padding * 2.0f);
    float rect_height = font_size + (padding * 2.0f);

    float rect_x = (SCREEN_WIDTH * 0.5f) - (rect_width * 0.5f);
    float rect_y = initial_y + (i * (rect_height + 20.0f));

    Color rect_color = (i == m->selected) ? WHITE : BLACK;
    Color text_color = (i == m->selected) ? BLACK : WHITE;

    DrawRectangle(rect_x, rect_y, rect_width, rect_height, rect_color);

    DrawRectangleLines(rect_x, rect_y, rect_width, rect_height, text_color);

    float text_x = rect_x + (rect_width - text_width) * 0.5f;
    float text_y = rect_y + (rect_height - font_size) * 0.5f;

    DrawText(items[i], text_x, text_y, (int)font_size, text_color);
  }
}
