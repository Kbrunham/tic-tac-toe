# TODO

Tracked `TODO` comments in this repository (excluding `extern/` submodules).

**Maintenance:** Update this file whenever `TODO` comments are added, resolved, or removed in project source.

## Open

### Support human and bot players

- **Location:** `main.cpp:63`
- **Comment:** `TODO: Test if the player is a bot or not. For now assume box.`
- **Context:** The game loop always calls `get_best_move()` for the current player. Add logic to distinguish bot vs human players and prompt for human input when appropriate.

### Clean up `main.h` boilerplate

- **Location:** `main.h:5`
- **Comment:** `TODO: Reference additional headers your program requires here.`
- **Context:** Leftover template stub. Remove the TODO and any unused includes once `main.h` is finalized (currently only includes `<iostream>`).
