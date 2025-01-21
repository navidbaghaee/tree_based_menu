#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"


typedef struct menu_struct{
 struct menu_struct *menu_item_parent;
	 struct menu_struct *menu_item_child;
 struct menu_struct *next;
 struct menu_struct *prev;
 void (*handler)();	
}menu_item_t;
	
void menu_item_create(menu_item_t **me,menu_item_t *parent,menu_item_t *child,void (*handler)());
void init_menu_items(void);
void display_current_menu(void);
void navigate_menu(uint8_t key);
	














#endif

