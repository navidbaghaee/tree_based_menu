#include "menu.h"

menu_item_t *current_menu;
menu_item_t *main_menu1;
menu_item_t *main_menu2;
menu_item_t *main_menu3;
menu_item_t *main_menu1_sub1;
menu_item_t *main_menu1_sub2;
menu_item_t *main_menu1_sub3;
menu_item_t *main_menu2_sub1;
menu_item_t *main_menu2_sub2;
menu_item_t *main_menu2_sub3;
menu_item_t *main_menu1_sub1_sub1;
menu_item_t *main_menu1_sub1_sub2;
menu_item_t *main_menu1_sub1_sub3;

void menu_item_create(menu_item_t **me, menu_item_t *parent, menu_item_t *child, void (*handler)()) {
    *me = (menu_item_t *)malloc(sizeof(menu_item_t));
    if (*me == NULL)
        return;
    memset(*me, 0, sizeof(menu_item_t));
    (*me)->menu_item_parent = parent;
    (*me)->menu_item_child = child;
    (*me)->handler = handler;
    
    if (parent && parent->menu_item_child == NULL) {
        parent->menu_item_child = *me;
    }
    if (child && child->menu_item_parent == NULL) {
        child->menu_item_parent = *me;
    }
}

void main_menu1_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"main_menu1");
}
void main_menu1_sub1_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 1 sub1");
}
void main_menu1_sub2_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 1 sub 2");
}
void main_menu1_sub3_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 1 sub 3");
}
void main_menu2_sub1_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 2 sub1");
}
void main_menu2_sub2_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 2 sub 2");
}
void main_menu2_sub3_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"Main 2 sub 3");
}
void main_menu1_sub1_sub1_handler(void)
{
	LCD_Clear();
	LCD_Puts(0,0,"sub 1 sub 1");
}
void main_menu1_sub1_sub2_handler(void)
{
	LCD_Clear();
	LCD_Puts(0,0,"sub 1 sub 2");
}
void main_menu1_sub1_sub3_handler(void)
{
	LCD_Clear();
	LCD_Puts(0,0,"sub 1 sub 3");
}
void main_menu2_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"main_menu2");
}

void main_menu3_handler(){
	LCD_Clear();
	LCD_Puts(0,0,"main_menu3");
}

void menu_set_relationships(menu_item_t **menu_items, int count) {
    for (int i = 0; i < count; i++) {
        if (menu_items[i]) {
            menu_items[i]->next = menu_items[(i + 1) % count];
            menu_items[i]->prev = menu_items[(i - 1 + count) % count];
        }
    }
}



void init_menu_items(void)
{
	//create main menu items
	menu_item_create(&main_menu1,NULL,main_menu1_sub1,main_menu1_handler);
	menu_item_create(&main_menu2,NULL,NULL,main_menu2_handler);
	menu_item_create(&main_menu3,NULL,NULL,main_menu3_handler);
	menu_item_t *main_menus[] = {main_menu1,main_menu2, main_menu3};
  menu_set_relationships(main_menus, 3);
	
	//create main 1 sub items
	menu_item_create(&main_menu1_sub1,main_menu1,main_menu1_sub1_sub1,main_menu1_sub1_handler);
	menu_item_create(&main_menu1_sub2,main_menu1,NULL,main_menu1_sub2_handler);	
	menu_item_create(&main_menu1_sub3,main_menu1,NULL,main_menu1_sub3_handler);
	menu_item_t *main1_sub_menus[] = {main_menu1_sub1, main_menu1_sub2, main_menu1_sub3};
  menu_set_relationships(main1_sub_menus, 3);
	
	//create main 2 sub items
	menu_item_create(&main_menu2_sub1,main_menu2,NULL,main_menu2_sub1_handler);
	menu_item_create(&main_menu2_sub2,main_menu2,NULL,main_menu2_sub2_handler);	
	menu_item_create(&main_menu2_sub3,main_menu2,NULL,main_menu2_sub3_handler);
	menu_item_t *main2_sub_menus[] = {main_menu2_sub1, main_menu2_sub2, main_menu2_sub3};
  menu_set_relationships(main2_sub_menus, 3);
	
	//create main1 sub1 sub items
	menu_item_create(&main_menu1_sub1_sub1,main_menu1_sub1,NULL,main_menu1_sub1_sub1_handler);
	menu_item_create(&main_menu1_sub1_sub2,main_menu1_sub1,NULL,main_menu1_sub1_sub2_handler);	
	menu_item_create(&main_menu1_sub1_sub3,main_menu1_sub1,NULL,main_menu1_sub1_sub3_handler);
	menu_item_t *main1_sub1_sub_menus[] = {main_menu1_sub1_sub1, main_menu1_sub1_sub2, main_menu1_sub1_sub3};
  menu_set_relationships(main1_sub1_sub_menus, 3);
	
		
	current_menu = main_menu1;
}

void display_wrong_input(void)
{
	LCD_Clear();
	LCD_Puts(0,0,"WRONG IN");
}

void display_current_menu(void){
	if(current_menu && current_menu->handler)
		current_menu->handler();
}

void navigate_menu(uint8_t key)
{
	switch(key)
	{
		case KEY_UP:
			current_menu = current_menu->next;
			display_current_menu();
			break;
		
		case KEY_DN:
			current_menu = current_menu->prev;
			display_current_menu();
			break;
		
		case KEY_ENTER:
				if (current_menu->menu_item_child) {
						current_menu = current_menu->menu_item_child;
						display_current_menu();
				}
				else
					 display_wrong_input();
				break;

		case KEY_MENU:
				if (current_menu->menu_item_parent) {
						current_menu = current_menu->menu_item_parent;
						display_current_menu();
				}
				else
					 display_current_menu();
			  break;
	}
}

