Integration Notes
=================

Prerequisites
-------------
- C toolchain for your target
- Standard headers: `stdint.h`, `stdlib.h`, `string.h`
- Your `main.h` (referenced by `MENU.h`) should provide:
  - Key codes: `#define KEY_UP ...`, `#define KEY_DN ...`, `#define KEY_ENTER ...`, `#define KEY_MENU ...`
  - Typedefs or includes for `uint8_t`
  - Declarations for your rendering API used by handlers; the sample uses:
    - `void LCD_Clear(void);`
    - `void LCD_Puts(int x, int y, const char *text);`

Files
-----
- `MENU.h`: Public type and function declarations
- `MENU.c`: Implementation, plus demo handlers used by `init_menu_items()`

Porting rendering
-----------------
The demo handlers call `LCD_Clear()` and `LCD_Puts()`. Replace these with your rendering functions inside your own handlers. The menu core does not depend on any particular display; only your handlers do.

Memory and lifetime
-------------------
- `menu_item_create` allocates with `malloc`. The library does not provide a destroy function. For static menus, allocate at startup and retain for device lifetime.
- If building dynamic menus, implement your own free routine to traverse and `free()` nodes.

Concurrency
-----------
- The library maintains a single `current_menu` pointer. Access it from one task or guard with a mutex if accessed concurrently.

Error handling
--------------
- If allocation fails, `menu_item_create` leaves `*me` unchanged. Check for `NULL` before wiring siblings.
- `navigate_menu` assumes `current_menu` is valid and that sibling links (circular) are consistent. Ensure your wiring is complete.

Testing tips
------------
- Stub LCD functions to log output on hosts without displays.
- Drive `navigate_menu` with synthetic key sequences to verify traversal and wrap-around.
