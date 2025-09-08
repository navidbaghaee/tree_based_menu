API Reference
=============

Header: `MENU.h`

Types
-----
```c
typedef struct menu_struct{
    struct menu_struct *menu_item_parent;
    struct menu_struct *menu_item_child;
    struct menu_struct *next;
    struct menu_struct *prev;
    void (*handler)();
} menu_item_t;
```

- `menu_item_parent`: Pointer to the parent menu item. `NULL` if this is a root-level item.
- `menu_item_child`: Pointer to the first child item. `NULL` if there are no children.
- `next` / `prev`: Sibling links forming a circular list among items at the same level.
- `handler`: Callback invoked by `display_current_menu()` to render the current menu state. Signature: `void handler(void);` (declared as `void (*)()` in the code).

Global state
------------
The implementation maintains an internal `current_menu` pointer (not exposed in the header) that tracks the active item. `init_menu_items()` sets it to the initial menu.

Functions
---------
```c
void menu_item_create(menu_item_t **me,
                      menu_item_t *parent,
                      menu_item_t *child,
                      void (*handler)());
```
Creates and initializes a new `menu_item_t` on the heap and assigns it to `*me`.

- Memory: Uses `malloc` and `memset`. Returns immediately if allocation fails, leaving `*me` unchanged.
- Relationships: Assigns `menu_item_parent` and `menu_item_child`. If `parent->menu_item_child` is `NULL`, it is set to this new item. If `child->menu_item_parent` is `NULL`, it is set to this new item.
- Siblings: `next` and `prev` are not set by this call; connect siblings manually.

```c
void init_menu_items(void);
```
Builds a sample menu tree and sets the internal `current_menu` to the first main menu. Use as a reference or for demo; production code typically builds its own tree.

```c
void display_current_menu(void);
```
Invokes the `handler` of the current menu item (if present). Intended to render the UI. In the sample, handlers call `LCD_Clear()` and `LCD_Puts()`.

```c
void navigate_menu(uint8_t key);
```
Processes a navigation key and updates the active `current_menu`:

- `KEY_UP`: Move to `current_menu->next` (sibling; circular list).
- `KEY_DN`: Move to `current_menu->prev` (sibling; circular list).
- `KEY_ENTER`: If `menu_item_child` exists, descend to it; otherwise calls `display_wrong_input()` (internal) to indicate invalid action.
- `KEY_MENU`: If a parent exists, ascend to it; otherwise re-display the current item.

Notes and constraints
---------------------
- Dependencies: `MENU.h` includes `main.h` which must provide key code defines, `uint8_t`, and rendering function declarations used by handlers.
- Memory management: There is no provided destructor; applications typically build menus once and retain for the device lifetime. If dynamic menus are needed, implement deallocation for each `menu_item_t` you allocate.
- Thread safety: The implementation is not thread-safe. Access and mutate menu state from a single task or protect with synchronization.
- Handlers: Must be fast and non-blocking. They should only render state; long-running work should be done elsewhere.
