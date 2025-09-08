Examples
========

Quick demo using the built-in sample tree
-----------------------------------------
```c
#include "main.h"
#include "MENU.h"

int main(void) {
    // Your platform init… clocks, GPIO, LCD, keys, etc.

    init_menu_items();            // Build demo menu tree and set current_menu
    display_current_menu();       // Render initial view

    for (;;) {
        uint8_t key = read_key_nonblocking(); // Implement for your board
        if (key != 0U) {
            navigate_menu(key);
        }
        // Other application work…
    }
}
```

Building your own menu tree
---------------------------
```c
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "MENU.h"

static menu_item_t *root;
static menu_item_t *settings;
static menu_item_t *about;
static menu_item_t *settings_sound;
static menu_item_t *settings_display;

static void root_handler(void) {
    LCD_Clear();
    LCD_Puts(0, 0, "Root");
}
static void settings_handler(void) {
    LCD_Clear();
    LCD_Puts(0, 0, "Settings");
}
static void about_handler(void) {
    LCD_Clear();
    LCD_Puts(0, 0, "About");
}
static void settings_sound_handler(void) {
    LCD_Clear();
    LCD_Puts(0, 0, "Sound");
}
static void settings_display_handler(void) {
    LCD_Clear();
    LCD_Puts(0, 0, "Display");
}

void build_menu(void) {
    // Create nodes and set parent/first-child links
    menu_item_create(&root, NULL, NULL, root_handler);
    menu_item_create(&settings, root, NULL, settings_handler);
    menu_item_create(&about,   root, NULL, about_handler);
    menu_item_create(&settings_sound,   settings, NULL, settings_sound_handler);
    menu_item_create(&settings_display, settings, NULL, settings_display_handler);

    // Wire siblings (circular at each level)
    // Level 0: root has two children: settings <-> about
    settings->next = about;  about->prev = settings;
    about->next = settings;  settings->prev = about;

    // Level 1 (under settings): sound <-> display
    settings_sound->next = settings_display;  settings_display->prev = settings_sound;
    settings_display->next = settings_sound;  settings_sound->prev = settings_display;

    // Set the application current menu to root's first child for initial view
    // (The provided implementation sets current_menu internally inside init routines.)
    // If you expose a setter, you can choose your desired starting node.
}

int main(void) {
    // Platform init…
    build_menu();
    display_current_menu();
    for (;;) {
        const uint8_t key = read_key_nonblocking();
        if (key != 0U) {
            navigate_menu(key);
        }
    }
}
```

Typical key mapping
-------------------
- `KEY_UP`: Next sibling
- `KEY_DN`: Previous sibling
- `KEY_ENTER`: Enter first child (if present)
- `KEY_MENU`: Go to parent (if present)
