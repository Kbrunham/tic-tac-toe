# Copilot Instructions for Tic-Tac-Toe

## Project Overview
C++17 tic-tac-toe solver using bitwise operations for game state representation. Demonstrates modern CMake, Google Test integration, and GitHub Actions CI.

## Architecture

### Core Components
- **`GAME_ENV`** (`game_env.h/cpp`): Top-level game orchestrator managing player state and board lifecycle
- **`GAME_BOARD`** (`game_board.h/cpp`): Board state manager using `std::bitset<18>` for move tracking (3×3 grid with 3-bit row padding for efficient bitwise win detection)
- **`GAME_MOVE`** (`game_move.h/cpp`): Move representation with (x,y) coordinates and score for AI evaluation
- **`GAME_BOARD_UTILS`** namespace (`game_board_utils.cpp`): Bitwise operation helpers for win detection and game state evaluation

### Key Design Decisions
**Bitwise Board Representation**: Board uses 18-bit bitset (6 bits per row: 3 game + 3 padding). Padding enables efficient column/diagonal win checks via single shift-and-mask operations. See `game_x_y_to_bitset_index()` for coordinate mapping.

**Move Evaluation**: `get_best_move()` generates all valid moves then evaluates via `evaluate_move()` (currently stub—extend here for AI logic like minimax).

**Player Tracking**: Two separate bitsets in `m_player_moves` map track PLAYER_1 and PLAYER_2 moves independently. Combined via `get_combined_moves()` for board-full detection.

## Build System

### Primary Commands (Makefile)
```bash
make prepare-tools    # Install Python venv + download/build Boost 1.86
make test            # Default target: build and run tests via CMake/CTest
make style-check-clang   # Verify code formatting (clang-format)
make style-format-clang  # Auto-format code
make dev-clean       # Git clean (preserves .vscode)
make dev-update      # Update git submodules
```

### CMake Build
Uses custom `project_add_test()` macro from `extern/cmake_helpers/bcommon.cmake` to create test targets. Each test links against shared source list `MAIN_TARGET_SOURCES`.

**Dependencies** (git submodules in `extern/`):
- Backward-cpp: stack trace generation
- cxxopts: CLI argument parsing  
- plog: logging with `PLOG_INFO`, `PLOG_DEBUG`
- GoogleTest: unit testing framework
- Boost 1.86: headers-only (required but minimally used)

## Testing

### Test Structure
- Tests in `test/test_game_board.cpp` focus on `GAME_BOARD_UTILS` bitwise operations
- Test naming: `TEST(GameBoardUtilsTest, <scenario>)` for board utilities
- Run via `ctest` or directly execute `build/main_test1`

### Common Test Patterns
```cpp
GAME_MOVES_BITSET moves;
moves.set(game_x_y_to_bitset_index(x, y));  // Set board position
ASSERT_TRUE(is_player_won(moves));           // Check win condition
```

## Code Conventions

### Header Organization
Standard library → External libraries → Project headers → Own header:
```cpp
#include <memory>           // std
#include <plog/Log.h>       // extern
#include "game.h"           // project
#include "game_board.h"     // own header
```

### Naming
- Classes: `SCREAMING_SNAKE_CASE` (e.g., `GAME_BOARD`, `GAME_PLAYER`)
- Member variables: `m_` prefix (e.g., `m_current_player`, `m_player_moves`)
- Constants: `SCREAMING_SNAKE_CASE` (e.g., `BOARD_SIZE_X`)
- Functions: `snake_case` (e.g., `get_best_move`, `is_column_win`)

### Error Handling
Use `CMN_ASSERT(condition)` macro (defined in `cmn.h`) for runtime invariant checks. Prints file/line and aborts on failure.

## Development Workflow

1. **Setup**: `make dev-update && make prepare-tools` (one-time: ~5min for Boost build)
2. **Edit code**: Ensure formatting with `make style-format-clang` before commit
3. **Test locally**: `make test` runs full CMake build + CTest suite
4. **CI validation**: GitHub Actions runs `build-test.yml` (Ubuntu, CMake) and `style-checks.yml` on PR

### Adding Features
- **New move logic**: Extend `GAME_BOARD::evaluate_move()` (currently no-op)
- **Win conditions**: Add helpers to `GAME_BOARD_UTILS` namespace with corresponding unit tests
- **New source files**: Update `MAIN_TARGET_SOURCES` in `CMakeLists.txt` (shared by main + tests)

## Key Files Reference
- `src/game.h`: Core constants (`BOARD_SIZE_X=3`, `GAME_PLAYER` enum)
- `main.cpp`: Game loop demonstrating player alternation and win detection
- `extern/cmake_helpers/bcommon.cmake`: Defines `project_add_test()` macro
- `.github/workflows/`: CI pipeline for builds and style enforcement
