#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef enum {
  ACTION_NONE,
  ACTION_PLAY,
  ACTION_SETTINGS,
  ACTION_EXIT
} MenuAction;

typedef struct {
  int selected;
  MenuAction action;
} Menu;

void Menu_Init(Menu *m);
void Menu_Update(Menu *m);
MenuAction Menu_GetAction(Menu *m);
void Menu_Draw(Menu *m);

#endif
