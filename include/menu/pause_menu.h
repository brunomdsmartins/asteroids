#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "settings_menu.h"

typedef struct {
  int selected;
  bool resume;
  KeyboardLayout layout;
  bool exit;
} Pause;

void Pause_Init(Pause *p, KeyboardLayout l);
void Pause_Update(Pause *p, Settings *s);
KeyboardLayout Pause_GetLayout(Pause *p);
const char *GetLayoutText(KeyboardLayout l);
bool Pause_Resume(Pause *p);
bool Pause_Exit(Pause *p);
void Pause_Draw(Pause *p, Settings *s);

#endif
