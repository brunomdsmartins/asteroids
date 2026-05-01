#include <raylib.h>
#include <stdbool.h>

#include "config.h"
#include "settings_menu.h"

#define SETTINGS_ITEMS 4

void Settings_Init(Settings *s) {
  s->selected = 0;
  s->difficulty = DIFFICULTY_NORMAL;
  s->layout = WASD;
  s->invincibility_after_dying = 1;
  s->back = false;
}

void Settings_Update(Settings *s) {
  if (IsKeyPressed(KEY_DOWN)) {
    s->selected = (s->selected + 1) % SETTINGS_ITEMS;
  }

  if (IsKeyPressed(KEY_UP)) {
    s->selected = (s->selected - 1 + SETTINGS_ITEMS) % SETTINGS_ITEMS;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    switch (s->selected) {
    case 0:
      if (s->difficulty == DIFFICULTY_HARDCORE) {
        s->difficulty = DIFFICULTY_EASY;
      } else {
        s->difficulty++;
      }
      break;
    case 1:
      if (s->layout == VIM) {
        s->layout = WASD;
      } else {
        s->layout++;
      }
      break;
    case 2:
      s->invincibility_after_dying = 1 - s->invincibility_after_dying;
      break;
    case 3:
      s->back = true;
      break;
    default:
      break;
    }
  }
}

GameDifficulty Settings_GetDifficulty(Settings *s) { return s->difficulty; }

KeyboardLayout Settings_GetLayout(Settings *s) { return s->layout; }

bool Settings_GoBack(Settings *s) {
  bool result = s->back;
  s->back = false;
  return result;
}

void Settings_Draw(Settings *s) {
  const char *items[SETTINGS_ITEMS] = {"Difficulty", "Keyboard Layout",
                                       "Invincibility After Dying", "Back"};

  float initial_y = SCREEN_HEIGHT * 0.4f;
  float font_size = 32.0f;

  for (int i = 0; i < SETTINGS_ITEMS; i++) {
    float text_width = (float)MeasureText(items[i], (int)font_size);

    float padding = font_size * 0.5f;

    float rect_width = text_width + (padding * 2.0f);
    float rect_height = font_size + (padding * 2.0f);

    float rect_x = (SCREEN_WIDTH * 0.5f) - (rect_width * 0.5f);
    float rect_y = initial_y + (i * (rect_height + 20.0f));

    Color rect_color = (i == s->selected) ? WHITE : BLACK;
    Color text_color = (i == s->selected) ? BLACK : WHITE;

    DrawRectangle(rect_x, rect_y, rect_width, rect_height, rect_color);

    DrawRectangleLines(rect_x, rect_y, rect_width, rect_height, text_color);

    float text_x = rect_x + (rect_width - text_width) * 0.5f;
    float text_y = rect_y + (rect_height - font_size) * 0.5f;

    DrawText(items[i], text_x, text_y, (int)font_size, text_color);
  }
}
