#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

typedef enum {
  DIFFICULTY_EASY,
  DIFFICULTY_NORMAL,
  DIFFICULTY_HARD,
  DIFFICULTY_HARDCORE
} GameDifficulty;

typedef enum { WASD, ARROWS, VIM } KeyboardLayout;

typedef struct {
  int selected;
  bool invincibility_after_dying;
  KeyboardLayout layout;
  GameDifficulty difficulty;
  bool back;
} Settings;

void Settings_Init(Settings *s);
void Settings_Update(Settings *s);
GameDifficulty Settings_GetDifficulty(Settings *s);
KeyboardLayout Settings_GetLayout(Settings *s);
const char *GetLayoutText(KeyboardLayout l);
bool Settings_GoBack(Settings *s);
void Settings_Draw(Settings *s);

#endif
