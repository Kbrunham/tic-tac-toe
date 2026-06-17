# Tic Tac Toe

Example Tic Tac Toe solver based on cpp-devenv template and using GitHub Actions.

A dev container configuration is available in `.devcontainer/` (Ubuntu 24.04 C++). After opening the repo in the container, follow the build steps below.

## Project overview

C++17 command-line tic-tac-toe game and move solver.

- **`GAME_BOARD`** — board state and rules; tracks each player's moves in bitsets and exposes `make_move()`, `get_best_move()`, and win/draw detection.
- **`GAME_MOVE`** — a single board position (x, y).
- **`GAME_ENV`** — game session state: current player and turn switching.
- **`main.cpp`** — CLI entry point; runs a game loop that currently plays bot-vs-bot by calling `get_best_move()` each turn (see [TODO.md](TODO.md)).
- **`test/test_game_board.cpp`** — GoogleTest unit tests for board utilities and game logic.

## Build System

- **Overview:** The repository uses a thin `Makefile` to prepare tooling and dependencies, and hands off actual compilation and testing to CMake. You can either drive everything with the Make targets or run CMake directly.

### Quick Start
- Get going fast with the common local flow:

```bash
make dev-update
make prepare-tools
cmake -S . -B work/build -G Ninja
cmake --build work/build
ctest --test-dir work/build --output-on-failure
make style-check-clang
./work/build/main
```

### Using Make (recommended)
- **Submodules:** initialize git submodules (required on first clone).

```bash
make dev-update
```

- **Prepare tools:** sets up a Python venv, installs required Python packages, and builds a minimal local Boost.

```bash
make prepare-tools
```

- **Configure CMake:** generates the build system under `work/build/`.

```bash
cmake -S . -B work/build -G Ninja
```

- **Build:** compiles the project via the CMake-generated build files.

```bash
cmake --build work/build
```

- **Test:** runs tests via CTest in the CMake build tree.

```bash
ctest --test-dir work/build --output-on-failure
```

- **Style checks:** run clang-format in check mode or format mode (clang-format is provided by the venv step).

```bash
make style-check-clang
make style-format-clang
```

- **Clean:** removes the venv and `work/` artifacts. Use `dev-clean` for a deeper git-clean while preserving VS Code settings.

```bash
make clean
make dev-clean
```

### Using CMake directly
- **Configure:** `cmake -S . -B work/build -G Ninja`
- **Build:** `cmake --build work/build`
- **Test:** `ctest --test-dir work/build --output-on-failure`
- **Run:** `./work/build/main`

### Notes
- **Boost:** `make boost` (via `make prepare-tools`) builds minimal Boost 1.86 into `boost/`. CMake locates Boost via `BOOST_ROOT`, which defaults to `./boost` in `CMakeLists.txt`. CI sets `BOOST_ROOT` explicitly; the Makefile exports `BOOST_ROOTDIR` for Make-driven workflows. If you have a system Boost 1.86 install, skip `make boost` and point `BOOST_ROOT` at it.
- **Artifacts:** All CMake outputs are placed under `work/build/`. Executables like the game (`main`) and test runner (`main_test1`) appear in that tree.
- **Help:** See available Make targets via `make help`.

## CI/CD

- **Platform:** GitHub Actions with Ubuntu 24.04 runners.
- **Workflows:**
	- **Build & Test:** [build-test.yml](.github/workflows/build-test.yml)
		- Triggers: push to `main`, pull requests (open/reopen/synchronize/ready_for_review), and `merge_group` checks.
		- Steps: checkout (with submodules), Python setup, install CMake/Ninja, create venv (`make venv`), cache/build Boost (`make boost` if cache miss), CMake configure (`-G Ninja`), build, and run `ctest`.
		- Status: posts commit status via `myrotvorets/set-commit-status-action` using context `build-test-status`.
		- Caching: caches `boost/` keyed by `${{ runner.os }}-boost-${{ env.BOOST_VERSION }}`.
	- **Style Checks:** [style-checks.yml](.github/workflows/style-checks.yml)
		- Triggers: push to `main` and pull requests (open/reopen/synchronize/ready_for_review).
		- Steps: checkout (with submodules), Python setup, venv (`make venv`), run `make style-check-clang`.
		- Status: posts commit status via `myrotvorets/set-commit-status-action` using context `style-check-status`.

- **Conventions:** Both workflows enforce single-run per ref via `concurrency` to cancel in-progress duplicates. They use the repository-local `boost/` directory with `BOOST_ROOT` set so builds are reproducible.

- **Local parity:** The local commands in the Build System section mirror CI steps: configure, build, test, and style checks. If local `make style-check-clang` fails due to `clang-format` availability, re-create the venv (`rm -rf venv && make venv`) to ensure `requirements.txt` is applied.

## Related docs

- [AGENTS.md](AGENTS.md) — agent and contributor operating instructions (conventions, troubleshooting).
- [TODO.md](TODO.md) — tracked TODO items in the codebase.
- [LICENSE](LICENSE) — MIT License.

