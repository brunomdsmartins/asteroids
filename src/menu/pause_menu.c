#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "config.h"
#include "pause_menu.h"

#define PAUSE_ITEMS 3

void Pause_Init(Pause *p, KeyboardLayout l) {
  p->selected = 0;
  p->resume = false;
  p->exit = false;
  p->layout = l;
}

void Pause_Update(Pause *p, Settings *s) {
  if (IsKeyPressed(KEY_DOWN)) {
    p->selected = (p->selected + 1) % PAUSE_ITEMS;
  }

  if (IsKeyPressed(KEY_UP)) {
    p->selected = (p->selected - 1 + PAUSE_ITEMS) % PAUSE_ITEMS;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    switch (p->selected) {
    case 0:
      p->resume = true;
      break;
    case 1:
      if (s->layout == VIM) {
        s->layout = WASD;
      } else {
        s->layout++;
      }
      break;
    case 2:
      p->exit = true;
      break;
    default:
      break;
    }
  }
}

KeyboardLayout Pause_GetLayout(Pause *p) { return p->layout; }

bool Pause_Resume(Pause *p) {
  bool result = p->resume;
  p->resume = false;
  return result;
}

bool Pause_Exit(Pause *p) {
  bool result = p->exit;
  p->exit = false; // Unnecessary?
  return result;
}

void Pause_Draw(Pause *p, Settings *s) {
  float initial_y = SCREEN_HEIGHT * 0.4f;
  float font_size = 32.0f;

  for (int i = 0; i < PAUSE_ITEMS; i++) {
    char buffer[128];

    switch (i) {
    case 0:
      snprintf(buffer, sizeof(buffer), "Resume");
      break;
    case 1:
      snprintf(buffer, sizeof(buffer), "Layout: %s", GetLayoutText(s->layout));
      break;
    case 2:
      snprintf(buffer, sizeof(buffer), "Exit");
      break;
    default:
      break;
    }

    float text_width = (float)MeasureText(buffer, (int)font_size);

    float padding = font_size * 0.5f;

    float rect_width = text_width + (padding * 2.0f);
    float rect_height = font_size + (padding * 2.0f);

    float rect_x = (SCREEN_WIDTH * 0.5f) - (rect_width * 0.5f);
    float rect_y = initial_y + (i * (rect_height + 20.0f));

    Color rect_color = (i == p->selected) ? WHITE : BLACK;
    Color text_color = (i == p->selected) ? BLACK : WHITE;

    DrawRectangle(rect_x, rect_y, rect_width, rect_height, rect_color);

    DrawRectangleLines(rect_x, rect_y, rect_width, rect_height, text_color);

    float text_x = rect_x + (rect_width - text_width) * 0.5f;
    float text_y = rect_y + (rect_height - font_size) * 0.5f;

    DrawText(buffer, text_x, text_y, (int)font_size, text_color);
  }
}
