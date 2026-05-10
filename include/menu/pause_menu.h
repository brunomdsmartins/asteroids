#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "settings_menu.h"

typedef struct {
  int selected;
  bool resume;
  KeyboardLayout layout;
} Pause;

void Pause_Init(Pause *s, KeyboardLayout l);
void Pause_Update(Pause *s);
KeyboardLayout Pause_GetLayout(Pause *s);
const char *GetLayoutText(KeyboardLayout l);
bool Pause_Resume(Pause *s);
void Pause_Draw(Pause *s);

#endif
