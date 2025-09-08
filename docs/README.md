MENU Library Documentation
==========================

Overview
--------
This repository provides a lightweight hierarchical menu system for embedded applications. It models menus as a doubly-linked tree where each entry may have a parent, an optional first child, and circular next/prev siblings. A handler function renders the current menu state (e.g., to an LCD).

Key features
- Hierarchical menu tree with parent/child and circular sibling navigation
- Pluggable render callbacks via `handler` functions
- Simple key-based navigation (`KEY_UP`, `KEY_DN`, `KEY_ENTER`, `KEY_MENU`)
- Minimal footprint suitable for MCUs

Getting started
1) Include `menu.h` from your project.
2) Ensure your `main.h` (or equivalent) defines/declares:
   - `uint8_t` and related stdint types
   - Key codes: `KEY_UP`, `KEY_DN`, `KEY_ENTER`, `KEY_MENU`
   - Rendering APIs used by your handlers (the sample uses `LCD_Clear()` and `LCD_Puts()`)
3) Initialize menu items and set `current_menu` by calling your own builder or use the sample `init_menu_items()`.
4) Call `navigate_menu(key)` upon key events; call `display_current_menu()` after state changes to render.

Where to look
- API reference: see `docs/API.md`
- Usage examples: see `docs/EXAMPLES.md`
- Integration notes: see `docs/INTEGRATION.md`
- Changelog: see `docs/CHANGELOG.md`

License
This codebase did not include a license file. Add one to match your distribution needs.
